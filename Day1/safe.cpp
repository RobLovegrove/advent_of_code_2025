#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int rotate_dial(char direction, int position, int distance, int& answer);

int main() {

    ifstream file("input.txt");

    int position = 50;
    int zero_count = 0;

    if (!file.is_open()) {
        cerr << "Failed to open file";
        return 1;
    }

    string line;
    while (getline(file, line)) {
        char direction = line[0];
        int value = stoi(line.substr(1));

        position = rotate_dial(direction, position, value, zero_count);
    }


    cout << "\nThere were " << zero_count << " zeroes!" << endl;

    file.close();
    return 0;
}

int rotate_dial(char direction, int position, int distance, int& answer) {
    if (direction == 'R') {
        for (int i = 0; i < distance; i++) {
            position++;
            if (position % 100 == 0) answer++;
        }
    }
    else {
        for (int i = 0; i < distance; i++) {
            position--;
            if (position % 100 == 0) answer++;
        }
    }
    return position;

}