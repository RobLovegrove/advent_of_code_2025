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

long long calculateRect(Coords, Coords);

int main() {

    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "Failed to open file";
        return 1;
    }

    auto start_time = chrono::high_resolution_clock::now();

    string line;

    vector<Coords> coords;

    while (getline(file, line)) {
        stringstream ss(line);
        string value;

        Coords p;
        getline(ss, value, ',');
        p.x = stoi(value);

        getline(ss, value, ',');
        p.y = stoi(value);

        coords.push_back(p);
    }

    long long largest = 0;
    for (int i = 0; i < coords.size(); i++) {
        for (int j = i+1; j < coords.size(); j++) {
            long long size = calculateRect(coords[i], coords[j]);
            if (largest < size) {
                largest = size;
            }
        }
    }

    cout << "The largest possible size is: " << largest << endl;

    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    cout << "Time: " << duration.count() << " ms\n";

    file.close();

    return 0;

}

long long calculateRect(Coords one, Coords two) {

    long long x = abs(one.x - two.x) + 1;
    long long y = abs(one.y - two.y) + 1;

    return x * y;
    
}