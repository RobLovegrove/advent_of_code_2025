#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <deque>
#include <string>
#include <sstream>

using namespace std;

int main() {

    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "Failed to open file";
        return 1;
    }

    auto start_time = chrono::high_resolution_clock::now();

    int splits = 0;
    int width = 0;
    vector<char> beams;
    vector<char> new_beams;
    vector<char> empty;
    bool split_occured = false;
    string line;
    while (getline(file, line)) {
        if (width == 0) {
            width = line.size();
            beams.resize(width);
            new_beams.resize(width);
            empty.resize(width);
            for (int i = 0; i < width; i++) {
                beams[i] = '.';
                new_beams[i] = '.';
                empty[i] = '.';
            }
        }
        if (split_occured) {
            split_occured = false;
            beams = new_beams;
            new_beams = empty;
        }

        for (int i = 0; i < width; i++) {
            if (line[i] == 'S') {
                beams[i] = '|';
            }
            if (line[i] == '^' && beams[i] == '|') {
                new_beams[i] = '.';
                new_beams[i-1] = '|';
                new_beams[i+1] = '|';
                splits++;
                split_occured = true;
            }
            if (beams[i] == '|' && line[i] != '^') {
                new_beams[i] = '|';
            }
        }

        for (char c : beams) {
            cout << c;
        }
        cout << endl;
    }
    cout << "The total number of splits is: " << splits << endl;

    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    cout << "Time: " << duration.count() << " ms\n";

    file.close();

    return 0;
}