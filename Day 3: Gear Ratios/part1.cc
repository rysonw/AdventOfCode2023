#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <sstream>
#include <vector>

using namespace std;

vector<string> buildMatrix(string file) {
    ifstream inputFile(file);
    vector<string> matrix;
    
    string line;
    
    while(getline(inputFile, line)) {
        matrix.push_back(line);
    }
    
    return matrix;
}

bool isSpecialChar(const char c, const unordered_set<char>& numChars) {
    return numChars.find(c) == numChars.end() && c != '.';
}

int main() {
    vector<string> matrix = buildMatrix("input.txt");
    
    unordered_set<char> numChars = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    vector<vector<int>> indexes = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, -1}, {1, 1}, {-1, -1}, {-1, 1}};
    int sum = 0;
    bool foundSpecialChar;
    
    vector<int> lineNums;
    
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].length(); ++j) {
            if (numChars.find(matrix[i][j]) != numChars.end()) {
                foundSpecialChar = false;
                int k = j;
                
                while (numChars.find(matrix[i][k]) != numChars.end()) {
                    // Check all 8 surrounding characters

                    for (const auto& pair : indexes) {
                        int ni = i + pair[0];
                        int nj = k + pair[1];
                        
                        if (ni >= 0 && ni < matrix.size() && nj >= 0 && nj < matrix[ni].length() && isSpecialChar(matrix[ni][nj], numChars)) {
                            foundSpecialChar = true;
                        }
                    }
                    
                    int count = 0;
                    while (j + count < matrix[i].length() && numChars.find(matrix[i][j + count]) != numChars.end()) {
                        count++;
                    }

                    if (foundSpecialChar == true) {
                        int num = stoi(matrix[i].substr(j, count));
                        lineNums.push_back(num);
                        sum += num;
                        j += count;
                        break;
                    }
                    else {
                        k++;
                    }
                    
                }
                
            }
        }
        //Debugging
        for (const auto& n : lineNums) {
            cout << n << endl;
        }
    }

    cout << sum << endl;
    return 0;
}
