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

using namespace std;


int main() {
    
    ifstream inputFile("input.txt");
    vector<long long> seeds;
    
    string line;
    
    vector<vector<vector<long long>>> map;
    bool isBlock = false;
    vector<vector<long long>> currBlock;
    
    while (getline(inputFile, line)) {
        if (seeds.empty()) {
            string seedString = line.substr(7, line.length() - 7);
            istringstream iss(seedString);
            long long num;
            
            while (iss >> num) {
                seeds.push_back(num);
            }
            
            continue;
        }
        
        if (line.empty()) {
            if (!isBlock) {
                continue;
            }
            else {
                isBlock = false;
                map.push_back(currBlock);
                currBlock.clear();
            }
        }
        
        if (isBlock) {
            vector<long long> level;
            istringstream iss(line);
            long long num;
            
            while (iss >> num) {
                level.push_back(num);
            }
            currBlock.push_back(level);
        }
        
        if (isalpha(line[0])) {
            isBlock = true;
            continue;
        }
        
    }
    
    map.push_back(currBlock);

    long long currLowest = numeric_limits<long long>::max();
    

    for (long long seed : seeds) {
        long long currValue = seed;
        for (vector<vector<long long>> block : map) {
            for (vector<long long> level : block) {
                long long start = level[1];
                long long range = level[2] - 1;
                long long dest = level[0];
                
                if (start <= currValue && currValue <= start + range) {
                    long long diff = currValue - start;
                    currValue = diff + dest;
                    break;
                }
            }
            
        }
        if (currValue < currLowest) {
            currLowest = currValue;
        }
    }

    cout << currLowest << endl;
    return 0;
}