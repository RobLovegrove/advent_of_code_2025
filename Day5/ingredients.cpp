#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <string>

using namespace std;

int main() {

    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "Failed to open file";
        return 1;
    }

    auto start_time = chrono::high_resolution_clock::now();

    bool ranges = true;

    int total_fresh = 0;

    vector<pair<long long, long long>> pairs;

    string line;
    while (getline(file, line)) {

        if (line == "") {
            ranges = false;
            continue;
        } 

        if (ranges == true) {
            size_t dashPos = line.find('-');

            if (dashPos == string::npos) continue;

            pair<long long, long long> p;
            p.first = stoll(line.substr(0, dashPos));
            p.second = stoll(line.substr(dashPos + 1));

            pairs.push_back(p);

        }
        else {
            long long ingredient = stoll(line);
            for (pair<long long, long long> pair : pairs) {
                if (pair.first <= ingredient && pair.second >= ingredient) {
                    total_fresh++;
                    break;
                }
            }
        }

    }

    cout << "There are " << total_fresh << " fresh ingredients" << endl;

    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    cout << "Time: " << duration.count() << " ms\n";

    file.close();

    return 0;
}