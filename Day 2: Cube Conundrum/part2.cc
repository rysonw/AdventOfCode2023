#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <vector>
#include <limits>

using namespace std;

vector<string> split(const string& str, char delimiter) {
    vector<string> result;
    istringstream iss(str);
    string token;
    while (getline(iss, token, delimiter)) {
        result.push_back(token);
    }
    return result;
}

int main() {

    ifstream inputFile("input.txt");

    int lineNumber = 1;
    int sum = 0;

    string line;
    while(getline(inputFile, line)) {

        unordered_map<string, int> currHighest = {
            {"red", numeric_limits<int>::min()},
            {"green", numeric_limits<int>::min()},
            {"blue", numeric_limits<int>::min()}
        };
        
        if (lineNumber > 0 && lineNumber < 10) {
            line = line.substr(8, line.length() - 7);
        }
        else if (lineNumber >= 10 && lineNumber < 100) {
            line = line.substr(9, line.length() - 8);
        }
        else {
            line = line.substr(10, line.length() - 9);
        }

        vector<string> groups = split(line, ';');
        for (const string& group : groups) {
            // Split by comma
            vector<string> items = split(group, ',');

            for (string& item : items) {
                // Further split each item by space to separate numbers and colors
                istringstream itemStream(item);
                int number;
                string color;
                itemStream >> number >> color;

                if (number > currHighest[color]) {
                    currHighest[color] = number;
                }

            }
        }

        sum += (currHighest["red"] * currHighest["green"] * currHighest["blue"]);

        lineNumber++;
    }

    cout << sum << endl;
    return 0;
}