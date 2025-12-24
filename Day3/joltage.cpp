#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <array>
#include <chrono>

using namespace std;

string recursive_joltage_finder(string bank, string joltage_string, int k, int index, int depth);

int main() {

    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "Failed to open file";
        return 1;
    }

    auto start_time = chrono::high_resolution_clock::now();

    long long joltage_total = 0;
    string joltage_str;
    joltage_str.resize(12);
    //array<int, 12> index{};

    string bank;
    while (getline(file, bank)) {
        cout << "Bank: " << bank << endl;

        string joltage_str;
        joltage_str.resize(12);
        joltage_str = recursive_joltage_finder(bank, joltage_str, 12, 0, 0);

        // joltage_str[0] = bank[0];

        // for (int i = 0; i < 2; i++) {
        //     for (int j = index[i]; j < bank.length()-(1-i); j++) {
        //         if (bank[j] > joltage_str[i]) {
        //             joltage_str[i] = bank[j];
        //             index[i] = j;
        //         }
        //     }
        //     index[i+1] = index[i] + 1;
        //     // joltage_str[i+1] = bank[index[i+1]];
        // }

        long long joltage = stoll(joltage_str);
        joltage_total += joltage;
        cout << "Joltage for this bank is: " << joltage << endl;
        cout << "Joltage Total is now: " << joltage_total << endl;

    }


    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    cout << "Time: " << duration.count() << " ms\n";

    file.close();
    return 0;
}

string recursive_joltage_finder(string bank, string joltage_string, int k, int index, int depth) {

    if (k == 0) return joltage_string;

    for (int i = index; i < bank.length() - k + 1; i++) {
        if (joltage_string[depth] < bank[i]) {
            joltage_string[depth] = bank[i];
            index = i;
        }
    }

    return joltage_string = recursive_joltage_finder(bank, joltage_string, k = k-1, index = index + 1, depth = depth + 1);
}