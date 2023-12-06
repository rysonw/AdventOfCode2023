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
    
    //Add winning numbs to hashset
    //Brute Force the indexes
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
        
        sum += pow(2, (runningTotal - 1));
        
    }

    cout << sum << endl;
    return 0;
}