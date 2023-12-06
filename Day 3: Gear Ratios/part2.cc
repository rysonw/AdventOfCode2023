#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <sstream>
#include <vector>
#include <utility>

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


int main() {
    vector<string> matrix = buildMatrix("input.txt");
    
    unordered_set<char> numChars = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    vector<vector<int>> indexes = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, -1}, {1, 1}, {-1, -1}, {-1, 1}};
    int sum = 0;
    bool foundAsterisk;
    
    vector<int> lineNums;
    
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].length(); ++j) {
            if (numChars.find(matrix[i][j]) != numChars.end()) {
                foundAsterisk = false;
                int k = j;
                
                while (numChars.find(matrix[i][k]) != numChars.end()) {
                    // Check all 8 surrounding characters
                    int astX;
                    int astY;
                    
                    for (const auto& pair : indexes) {
                        int ni = i + pair[0];
                        int nj = k + pair[1];
                        
                        if (ni >= 0 && ni < matrix.size() && nj >= 0 && nj < matrix[ni].length() && matrix[ni][nj] == '*') {
                            foundAsterisk = true;
                            astX = ni;
                            astY = nj;
                        }
                    }
                    
                    int count = 0;
                    while (j + count < matrix[i].length() && numChars.find(matrix[i][j + count]) != numChars.end()) {
                        count++;
                    }

                    if (foundAsterisk) {
                        unordered_set<pair<int, int>> seenNums;
                        
                        // Add num first number
                        int xj = j;
                        
                        if (matrix[i][xj + 2] == '.') {
                            int length = 2;
                        }
                        else {
                            int length = 3;
                        }

                        while (length > 0) {
                            seenNum.insert({i, xj});
                            length--;
                        }

                        
                        bool validNum = true;
                        
                        for (const auto& pair : indexes) {
                            int ni = astX + pair[0];
                            int nj = astY + pair[1];
                            
                            if (ni >= 0 && ni < matrix.size() && nj >= 0 && nj < matrix[ni].length() && numChars.find(matrix[ni][nj]) != numChars.end()) {
                                pair<int, int> currCoords = {ni, nj};
                                if (seenNums.find(currCoords) == seenNums.end()) {
                                    validNum = false;
                                }
                                else {
                                    // Save number and add coords to hashset
                                    int start = nj;
                                    
                                    while (start >= 0 && start < matrix[ni].length() && matrix[ni][start] == numChars.find(matrix[ni][nj]) != numChars.end()) {
                                        start--;
                                    }
                                    
                                    if (matrix[ni][start + 2] == '.') {
                                        end = start + 1;
                                    }
                                    else {
                                        end = start + 2;
                                    }
                                    int num2 = stoi(matrix[i].substr(j, (end + 1) - start)); // CHECK
                                    
                                    while (start <= end) {
                                        seenNum.insert({i, start});
                                        start++;
                                    }
                                }
                            }
                        }
                        
                        
                        
                        if (validNum) {
                            int num1 = stoi(matrix[i].substr(j, count));
                            sum += num1 * num2;
                            j += count;
                            break;
                        }
                    }
                    else {
                        k++;
                    }
                    
                }
                
            }
        }
        for (const auto& n : lineNums) {
            cout << n << endl;
        }
        lineNums.clear();
    }

    cout << sum << endl;
    return 0;
}