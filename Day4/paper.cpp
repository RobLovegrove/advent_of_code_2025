#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <string>

using namespace std;

bool is_accessible(vector<vector<char>>& grid, int row, int col);
int remove_accessible_paper(vector<vector<char>>& grid);

int main() {

    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "Failed to open file";
        return 1;
    }

    auto start_time = chrono::high_resolution_clock::now();

    vector<vector<char>> grid;

    string line;
    while (getline(file, line)) {
        vector<char> chars(line.begin(), line.end());
        grid.push_back(chars);
    }

    int total = 0;
    int removed = 1;
    while (removed != 0) {
        removed = remove_accessible_paper(grid);
        total += removed;
    }

    cout << "The total is: " << total << endl;

    for (vector<char> line : grid) {
        for (char c : line) {
            cout << c;
        }
        cout << endl;
    }

    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    cout << "Time: " << duration.count() << " ms\n";

    file.close();

    return 0;
}

bool is_accessible(vector<vector<char>>& grid, int row, int col) {

    int count = 0;

    for (int r = -1; r < 2; r++) {
        for (int c = -1; c < 2; c++) {
            if (r == 0 && c == 0);
            else if (r + row < 0 || r + row >= grid.size());
            else if (c + col < 0 || c + col >= grid[row].size());
            else if (grid[row+r][col+c] == '@' || grid[row+r][col+c] == 'x') {
                count++;
                if (count > 3) return false;
            }
        }
    }

    if (count > 3) return false;
    grid[row][col] = '.';
    return true;
}

int remove_accessible_paper(vector<vector<char>>& grid) {

    int total = 0;
    for (int r = 0; r < grid.size(); r++) {
        for (int c = 0; c < grid[r].size(); c++) {
            if (grid[r][c] == '@') {
                if (is_accessible(grid, r, c)) total++;
            }    
        }
    }

    return total;
}