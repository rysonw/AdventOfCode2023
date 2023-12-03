#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int main() {
    fstream inputFile("input.txt");
    unordered_set<char> numChars = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
    int totalSum = 0;
    
    string line;
    while (getline(inputFile, line)) {
        int firstNum = 0;
        int lastNum = 0;
        
        // Find first num
        for (char c : line) {
            if (numChars.find(c) != numChars.end()) {
                firstNum = (c - '0') * 10;
                break;
            }
        }
        
        // Find second num
        for (int i = line.length() - 1; i >= 0; --i) {
            if (numChars.find(line[i]) != numChars.end()) {
                lastNum = line[i] - '0';
                break;
            }
        }
        
        cout << firstNum+lastNum<< endl;
        
        totalSum = totalSum + firstNum + lastNum;
    }
    
    cout << totalSum << endl;

    return 0;

}