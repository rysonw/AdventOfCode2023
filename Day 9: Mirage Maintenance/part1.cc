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
        
        for (int i = currSeq.size() - 1; i >= 0; --i) {
            if (i == currSeq.size() - 1) {
                currSeq[i].push_back(0);
                continue;
            }
        
            int lastNum = currSeq[i].back();
            currSeq[i].push_back(lastNum + currSeq[i + 1].back());
            
        }
        
        sum += currSeq[0].back();


    }
    
    cout << sum << endl;
    
    return 0;
}