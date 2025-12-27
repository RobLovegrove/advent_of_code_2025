#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
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

    vector<pair<long long, long long>> pairs;
    long long result = 0;

    string line;
    while (getline(file, line)) {

        istringstream iss(line);
        string item;

        int count = 0;
        while (iss >> item) {
            if (count >= pairs.size()) {
                pairs.push_back({0, 1});
            }
            if (item == "+") {
                result += pairs[count].first;
            }
            else if (item == "*") {
                result += pairs[count].second;
            }
            else {
                pairs[count].first += stoll(item);
                pairs[count].second *= stoll(item);
            }
            count++;
        }
    }

    cout << "The total sum is: " << result << endl;


    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    cout << "Time: " << duration.count() << " ms\n";

    file.close();

    return 0;
}