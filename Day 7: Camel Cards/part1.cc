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

void insertInMap(unordered_map<string, vector<vector<string>>>& handMap, const string& category, const string& hand, const string& bet) {
    if (handMap.find(category) == handMap.end()) {
        handMap[category] = {{hand, bet}};
    } else {
        handMap[category].push_back({hand, bet});
    }
}


int main() {

    // 1st Pass: Hashmap: Key is Hand Type -> Vector of Hands
    // 2nd Pass: Go through each vector and sort based on strength
    
    unordered_map<string, vector<vector<string>>> handMap;
    
    fstream inputFile("input.txt");
    int total = 0;
    string line;
    
    
    while (getline(inputFile, line)) {
        string hand = line.substr(0, 5);
        string bet = line.substr(6);
        unordered_map<char, int> cardCount;
        for (char c : hand) {
            if (cardCount.find(c) == cardCount.end()) {
                cardCount[c] = 1;
            }
            else {
                cardCount[c]++;
            }
        }
        
        if (cardCount.size() == 1) {
            insertInMap(handMap, "FiOAK", hand, bet);
        }
        
        else if (cardCount.size() == 2) {
            for (const auto& pair : cardCount) {
                if (pair.second == 4 || pair.second == 1) {
                    insertInMap(handMap, "FoOAK", hand, bet);
                    break;
                }
                else {
                    insertInMap(handMap, "FHouse", hand, bet);
                    break;
                }
            }
        }
        
        else if (cardCount.size() == 3) {
            for (const auto& pair : cardCount) {
                if (pair.second == 1) {
                    continue;
                }
                else if (pair.second == 2) {
                    insertInMap(handMap, "2Pair", hand, bet);
                    break;
                }
                else {
                    insertInMap(handMap, "ThOAK", hand, bet);
                    break;
                }
            }
        }
        
        else if (cardCount.size() == 4) {
            insertInMap(handMap, "1Pair", hand, bet);

        }
        
        else {
            insertInMap(handMap, "HighCard", hand, bet);
     
        }
    }
    
    unordered_map<char, int> cardRanking = {
        {'2', 2},
        {'3', 3},
        {'4', 4},
        {'5', 5},
        {'6', 6},
        {'7', 7},
        {'8', 8},
        {'9', 9},
        {'T', 10},
        {'J', 11},
        {'Q', 12},
        {'K', 13},
        {'A', 14}
    };  
    
    // Sorting
    for (auto& pair : handMap) {
        vector<vector<string>>& cardArray = pair.second;
        sort(cardArray.begin(), cardArray.end(), [&cardRanking](const vector<string>& pair1, const vector<string>& pair2) {
            int i = 0;
            while (i < pair1[0].size() && i < pair2[0].size() && pair1[0][i] == pair2[0][i]) {
                i++;
            }
            if (i < pair1[0].size() && i < pair2[0].size()) {
                return cardRanking[pair1[0][i]] > cardRanking[pair2[0][i]];
            }
            return pair1[0].size() > pair2[0].size(); 
        });
    }
    
    
    int totalWinnings = 0;
    int rank = 1000;
    vector<string> winningOrder = {"FiOAK", "FoOAK", "FHouse", "ThOAK", "2Pair", "1Pair", "HighCard"};
    
    for (int i = 0; i < winningOrder.size(); ++i) {
        string key =  winningOrder[i];
        vector<vector<string>> currArray = handMap[key];
        for (const auto& pair : currArray) {
            cout << "  Hand: " << pair[0] << ", Bet: " << pair[1] << ", Rank: " << rank << "\n";
            totalWinnings += rank * stoi(pair[1]);
            rank--;
        }
    }
    
    
    cout << totalWinnings << endl;
    
    return 0;
}
