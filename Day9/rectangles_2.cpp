
/*

Clearly going to have to come up with a better method than this 
as it took just under 11 hours. 
Perhaps I will come back to it!

*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <vector>
#include <string>

using namespace std;

struct Coords {
    int x, y;
};

long long calculateRect(vector<vector<char>>&, Coords, Coords);

int main() {

    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "Failed to open file";
        return 1;
    }

    auto start_time = chrono::high_resolution_clock::now();

    string line;

    vector<Coords> coords;

    int x = 0;
    int y = 0;

    while (getline(file, line)) {
        stringstream ss(line);
        string value;

        Coords p;
        getline(ss, value, ',');
        p.x = stoi(value);
        if (p.x > x) x = p.x;

        getline(ss, value, ',');
        p.y = stoi(value);
        if (p.y > y) y = p.y;

        coords.push_back(p);
    }

    cout << "X: " << x << " Y: " << y << endl;

    vector<vector<char>> grid;
    for (int i = 0; i < y+1; i++) {
        vector<char> row;
        for (int j = 0; j < x+1; j++) {
            row.push_back('.');
        }
        grid.push_back(row);
    }

    cout << "Created grid!" << endl;
    auto time = chrono::high_resolution_clock::now();
    auto d = chrono::duration_cast<chrono::milliseconds>(time - start_time);
    cout << "Time: " << d.count() << " ms\n";

    for (auto& c : coords) {
        grid[c.y][c.x] = '#';
    }

    cout << "Added red tiles" << endl;
    auto t = chrono::high_resolution_clock::now();
    d = chrono::duration_cast<chrono::milliseconds>(t - time);
    time = t;
    cout << "Time: " << d.count() << " ms\n";

    bool between_red = false;
    for (int i = 0; i < grid[0].size(); i++) {
        for (int j = 0; j < grid.size(); j++) {
            if (grid[j][i] == '#') {
                between_red = !between_red;
            }
            else if (between_red) {
                grid[j][i] = 'X';
            }
        }
    }

    cout << "Added vertical green tiles" << endl;
    t = chrono::high_resolution_clock::now();
    d = chrono::duration_cast<chrono::milliseconds>(t - time);
    time = t;
    cout << "Time: " << d.count() << " ms\n";

    for (int i = 0; i < grid.size(); i++) {
        int start = -1;
        int end = 0;
        for (int j = 0; j < grid[i].size(); j++) {
            if ((grid[i][j] == '#' || grid[i][j] == 'X') && start == -1) {
                start = j;
            }
            else if (grid[i][j] == '#' || grid[i][j] == 'X') {
                end = j;
            }
        }
        if (start != -1) {
            for (int r = start; r < end+1; r++) {
                if (grid[i][r] == '.') grid[i][r] = 'X';
            }
        }
    }

    cout << "Added all green tiles" << endl;
    t = chrono::high_resolution_clock::now();
    d = chrono::duration_cast<chrono::milliseconds>(t - time);
    time = t;
    cout << "Time: " << d.count() << " ms\n";

    // for (int i = 0; i < grid.size(); i++) {
    //     for (int j = 0; j < grid[i].size(); j++) {
    //         cout << grid[i][j];
    //     }
    //     cout << endl;
    // }

    long long largest = 0;

    int total = 0;
    int average = 0;
    for (int i = 0; i < coords.size(); i++) {
        for (int j = i+1; j < coords.size(); j++) {
            long long size = calculateRect(grid, coords[i], coords[j]);
            if (largest < size) {
                largest = size;
            }
        }
        cout << "Finished line " << i << " of " << coords.size() << endl;
        t = chrono::high_resolution_clock::now();
        d = chrono::duration_cast<chrono::milliseconds>(t - time);
        total += d.count();
        average = total / i+1;
        time = t;
        cout << "Time: " << d.count() << " ms\n";
        cout << "Average time per line: " << average << endl;
        cout << "Predicted remaining time is " << average * (coords.size() - i) << "ms" << endl;
    }

    cout << "The largest possible size is: " << largest << endl;

    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    cout << "Time: " << duration.count() << " ms\n";

    file.close();

    return 0;

}

long long calculateRect(vector<vector<char>>& grid, Coords one, Coords two) {

    int start_x = min(one.x, two.x);
    int start_y = min(one.y, two.y);
    long long x = abs(one.x - two.x) + 1;
    long long y = abs(one.y - two.y) + 1;

    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (grid[start_y+i][start_x+j] == '.') return 0;
        }
    }

    return x * y;
    
}