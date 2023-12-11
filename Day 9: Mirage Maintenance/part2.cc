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
    
    fstream inputFile("input.txt");
    int sum = 0;
    string line;
    
    while (getline(inputFile, line)) {
        vector<vector<int>> currSeq;
        bool isAllZero = false;
        vector<int> currLevel;
        
        istringstream iss(line);
        int num;
        
        while (iss >> num) {
            currLevel.push_back(num);
            if (num != 0) {
                isAllZero = false;
            }
        }
        
        currSeq.push_back(currLevel);
        
        
        
        while (!isAllZero) {
            vector<int> currLevel;
            vector<int> prevLevel = currSeq.back();
            isAllZero = true;
            int nextIndex;
            
            for (int i = 0; i <= prevLevel.size() - 2; ++i) {
                nextIndex = i + 1;
                int diff = prevLevel[nextIndex] - prevLevel[i];
                currLevel.push_back(diff);
                if (diff != 0) {
                    isAllZero = false;
                }
            }

            currSeq.push_back(currLevel);
        }
        
        int lastNum = 0;
        for (int i = currSeq.size() - 2; i >= 0; --i) {
            int newNum = currSeq[i][0] - lastNum;
            lastNum = newNum;
            
        }
        
        sum += lastNum;


    }
    
    cout << sum << endl;
    
    return 0;
}