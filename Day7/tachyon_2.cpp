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

    vector<long long> timelines;
    vector<long long> new_timelines;
    vector<long long> empty;
    
    bool split_occured = false;
    int width = 0;

    string line;
    while (getline(file, line)) {
        if (width == 0) {
            width = line.size();
            timelines.resize(width);
            new_timelines.resize(width);
            empty.resize(width);
            for (int i = 0; i < width; i++) {
                timelines[i] = 0;
                new_timelines[i] = 0;
                empty[i] = 0;
            }
        }

        if (split_occured) {
            split_occured = false;
            timelines = new_timelines;
            new_timelines = empty;
        }

        for (int i = 0; i < width; i++) {
            if (line[i] == 'S') {
                timelines[i] = 1;
            }
            else if (line[i] == '^' && timelines[i] > 0) {
                new_timelines[i] = 0;
                new_timelines[i-1] += timelines[i];
                new_timelines[i+1] += timelines[i];
                split_occured = true;
            }
            else if (line[i] != '^' && split_occured) {
                new_timelines[i] += timelines[i];
            }
        }
    }

    long long total = 0;
    for (long long num : timelines) {
        total += num;
    }

    cout << "The total is " << total << endl;


    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    cout << "Time: " << duration.count() << " ms\n";

    file.close();

    return 0;
}


/* --- Apparently doing this recursively was a terrible idea --- */

// int COUNT = 0;
// void find_next_splitter(vector<vector<char>>& grid, long long& splits, int row, int col);
// void print_grid(vector<vector<char>>& grid);

// int main() {

//     ifstream file("input.txt");
//     if (!file.is_open()) {
//         cerr << "Failed to open file";
//         return 1;
//     }

//     auto start_time = chrono::high_resolution_clock::now();

//     long long splits = 0;

//     vector<vector<char>> grid;
//     string line;

//     while (getline(file, line)) {
//         vector<char> l;
//         for (char c : line) {
//             l.push_back(c);
//         }
//         grid.push_back(l);
//     }

//     int beam_row = 1;
//     int beam_col = 0;
//     for (int i = 0; i < grid[0].size(); i++) {
//         if (grid[0][i] == 'S') {
//             grid[1][i] = '|';
//             beam_col = i;
//         }
//     }

//     find_next_splitter(grid, splits, beam_row, beam_col);

//     // for (vector<char>& line : grid) {
//     //     for (char c : line) {
//     //         cout << c;
//     //     }
//     //     cout << endl;
//     // }

//     cout << "The total number of splits is: " << splits << endl;

//     auto end_time = chrono::high_resolution_clock::now();
//     auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
//     cout << "Time: " << duration.count() << " ms\n";

//     file.close();

//     return 0;
// }

// void find_next_splitter(vector<vector<char>>& grid, long long& splits, int row, int col) {
//     if (row >= grid[0].size()) { 
//         COUNT++;
//         if (COUNT % 10000 == 0) {
//             print_grid(grid);
//             cout << endl;
//             cout << "Split total is: " << splits << endl;
//         }
//         return; 
//     }

//     if (grid[row+1][col] == '^') {
//         splits++;
//         vector<vector<char>> grid_copy = grid;
//         find_next_splitter(grid, splits, row+1, col-1);
//         grid = grid_copy;
//         find_next_splitter(grid, splits, row+1, col+1);
//         grid = grid_copy;
//     }
//     else {
//         grid[row+1][col] = '|';
//         vector<vector<char>> grid_copy = grid;
//         find_next_splitter(grid, splits, row+1, col);
//         grid = grid_copy;
//     }
// }


// void print_grid(vector<vector<char>>& grid){    
//     for (vector<char>& line : grid) {
//         for (char c : line) {
//             cout << c;
//         }
//         cout << endl;
//     }
// }
