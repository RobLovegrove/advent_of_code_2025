#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>

using namespace std;

bool is_valid_id(string, long long&);

int main() {

    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "Failed to open file";
        return 1;
    }

    long long total = 0;

    auto start_time = chrono::high_resolution_clock::now();

    string line;
    getline(file, line);   

    stringstream ss(line);
    string range;

    while (getline(ss, range, ',')) {
        size_t dashPos = range.find('-');

        if (dashPos == string::npos) continue;

        long long start = stoll(range.substr(0, dashPos));
        long long end   = stoll(range.substr(dashPos + 1));

        cout << start << " -> " << end << endl;

        for (long long i = start; i <= end; i++) {
            if (!is_valid_id(to_string(i), i)) {
                cout << "Invalid Id is: " << i << endl;
                total += i;
            }
        }
    }

    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    cout << "Time: " << duration.count() << " ms\n";

    cout << "The total is: " << total << endl;
    file.close();
    return 0;
}


bool is_valid_id(string id, long long& number) {

    // if (id.length() % 2 != 0) return true;

    // int half = id.length()/2;
    // for(int i = 0; i < half; i++) {
    //     if (id[i] != id[i+half]) return true;
    // }

    int half = id.length()/2;
    for (int i = 1; i <= half; i++) {
        string base = id.substr(0, i);
        //cout << "The base is: " << base << endl;
        bool is_valid = false;
        for (int j = 0 + i; j < id.length(); j = j+i) {
            string substring = id.substr(j, i);
            //cout << "The substring is: " << substring << endl;
            if (base != substring) is_valid = true;
        }
        if (is_valid == false) return false;
    }

    return true;
}