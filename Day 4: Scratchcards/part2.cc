#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <cmath>

using namespace std;

int main() {
    
    ifstream inputFile("input.txt");
    int sum = 0;
    string line;
    
    unordered_map<int, int> cardMap;
    
    for (int i = 1; i <= 214; ++i) {
        cardMap[i] = 1;
    }
    
    int currCardNum = 1;
    //Add winning nums to hashset
    while (getline(inputFile, line)) {
        int currIndex = 10; 
        unordered_set<string> winningNums;
        for (int i = 0; i <= 9; ++i) {
            winningNums.insert(line.substr(currIndex, 2));
            currIndex += 3;
        }
        
        currIndex = 42;
    
        int runningTotal = 0;
        for (int i = 0; i <= 24; ++i) {
            if (winningNums.find(line.substr(currIndex, 2)) != winningNums.end()) {
                runningTotal++;
            }
            currIndex += 3;
        }
        
        for (int i = 1; i <= cardMap[currCardNum]; ++i) {
            int temp = currCardNum + 1;
            for (int j = 1; j <= runningTotal; ++j) {
                cardMap[temp]++;
                temp++;
            }
        }
        
        currCardNum++;
    }
    
    for (const auto& n : cardMap) {
        sum += n.second;
    }

    cout << sum << endl;
    return 0;
}