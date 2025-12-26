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
    long long total_fresh = 0;

    vector<pair<long long, long long>> pairs;

    string line;
    while (getline(file, line)) {

        if (line == "") {
            break;
        } 

        size_t dashPos = line.find('-');

        if (dashPos == string::npos) continue;

        pair<long long, long long> p;
        p.first = stoll(line.substr(0, dashPos));
        p.second = stoll(line.substr(dashPos + 1));

        for (pair<long long, long long>& pair : pairs) {
            if (p.first < pair.first && p.second > pair.second) {
                pair.first = 1;
                pair.second = 0;
            }
            else {
                if (p.first >= pair.first && p.first <= pair.second) {
                    p.first = pair.second + 1;
                }
                if (p.second >= pair.first && p.second <= pair.second) {
                    p.second = pair.first - 1;
                }
            }
        }
        if (p.first <= p.second) {
            pairs.push_back(p);
        }
    }

    for (pair<long long, long long> pair : pairs) {
        cout << pair.first << " -> " << pair.second << endl;
        total_fresh += pair.second + 1 - pair.first;
    }

    cout << "Total fresh possibilites is: " << total_fresh << endl;

    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    cout << "Time: " << duration.count() << " ms\n";

    file.close();

    return 0;
}