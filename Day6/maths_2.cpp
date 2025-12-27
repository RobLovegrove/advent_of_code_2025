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

    vector<vector<char>> grid;
    long long result = 0;
    vector<vector<string>> equations;

    string line;
    while (getline(file, line)) {
        reverse(line.begin(), line.end());
        vector<char> chars;
        for (char c : line) {
            chars.push_back(c);
        }
        grid.push_back(chars);
    }

    vector<string> equation;
    string op = "";
    for (int i = 0; i < grid[0].size(); i++) {
        string num;
        for (int j = 0; j < grid.size(); j++) {
            if (grid[j][i] == '*') {
                op = '*';
            }
            else if (grid[j][i] == '+') { 
                op += '+'; }
            else {
                num.push_back(grid[j][i]);
            }
        }
        bool new_num = true;
        for (char c : num) {
            if (c != ' ') {
                new_num = false;
            }
        }
        if (new_num == true) {
            equation.push_back(op);
            op = "";
            equations.push_back(equation);
            equation.clear();
        }
        else equation.push_back(num);
    }

    equation.push_back(op);
    equations.push_back(equation);
    equation.clear();

    for (vector<string> equation : equations) {
        long long prod = 1;
        long long sum = 0;
        for (string num : equation) {
            if (num == "+") result += sum;
            else if (num == "*") result += prod;
            else {
                long long number = stoll(num);
                prod *= number;
                sum += number;
            }
        }
    }

    cout << "The total sum is: " << result << endl;


    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    cout << "Time: " << duration.count() << " ms\n";

    file.close();

    return 0;
}