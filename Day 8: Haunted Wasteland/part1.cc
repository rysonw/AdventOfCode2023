#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <sstream>
#include <vector>
#include <utility>
#include <cmath>
#include <climits>
#include <algorithm>

using namespace std;


int main() {
    
    unordered_map<string, vector<string>> pointMap;
    
    fstream inputFile("input.txt");
    string instructions = "";
    string line;
    
    while (getline(inputFile, line)) {
        if (line.empty()) {
            continue;
        }
        if (line[3] != ' ') {
            instructions += line;
            continue;
        }
        
        pointMap[line.substr(0, 3)] = {line.substr(7, 3), line.substr(12, 3)};
    }
    
    // for (const auto& pair : pointMap) {
    //     cout << "Key: " << pair.first << " , Left: " << pair.second[0] << endl;
    // }
    
    vector<string> startLocations;
    
    for (const auto& pair : pointMap) {
        if (pair.first.back() == 'A') {
            startLocations.push_back(pair.first);
        }
    }
    
    // for (string s : startLocations) {
    //     cout << s << endl;
    // }
    
    int steps = 0;
    int index = 0;
    bool isEndZ = false;
    
    while (!isEndZ) {
        isEndZ = true;
        for (int i = 0; i < startLocations.size(); ++i) {
            string prevLocation = startLocations[i];
            
            cout << startLocations[i] << endl;
            
            if (index == instructions.length()) {
                index = 0;
            }
            
            string currLocation;
            
            if (instructions[index] == 'L') {
                currLocation = pointMap[prevLocation][0];
                startLocations[i] = currLocation;
            }
            else {
                currLocation = pointMap[prevLocation][1];
                startLocations[i] = currLocation;
            }
            
            if (currLocation.back() != 'Z') {
                isEndZ = false;
            }
            
        }
        index++;
        steps++;
    }
    
    cout << steps << endl;
    return 0;
}