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

void insertInMap(unordered_map<string, vector<vector<string>>>& handMap, unordered_map<char, int>& cardCount, const string& hand, const string& bet) {
    if (cardCount.find('J') != cardCount.end()) {
        char currHighestChar = 'z';
        for (const auto& pair : cardCount) {
            
            if ((pair.first != 'J' && currHighestChar == 'z') || (pair.first != 'J' && pair.second > cardCount[currHighestChar])) {
                currHighestChar = pair.first;
            }
        }
        

        cardCount[currHighestChar] += cardCount['J'];
        cardCount.erase('J');
    }
    
    string category;
    
    if (cardCount.size() == 1 || hand == "JJJJJ") {
            category = "FiOAK";
        }
        
    else if (cardCount.size() == 2) {
        for (const auto& pair : cardCount) {
            if (pair.second == 4 || pair.second == 1) {
                category = "FoOAK";
                break;
            }
            else {
                category = "FHouse";
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
                category = "2Pair";
                break;
            }
            else {
                category = "ThOAK";
                break;
            }
        }
    }
    
    else if (cardCount.size() == 4) {
        category = "1Pair";

    }
    
    else {
        category = "HighCard";
    }
    
    
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
    
    unordered_set<string> hands;
    
    while (getline(inputFile, line)) {
        string hand = line.substr(0, 5);
        hands.insert(hand);
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
        
        insertInMap(handMap, cardCount, hand, bet);
    }
    
    unordered_map<char, int> cardRanking = {
        {'J', 1},
        {'2', 2},
        {'3', 3},
        {'4', 4},
        {'5', 5},
        {'6', 6},
        {'7', 7},
        {'8', 8},
        {'9', 9},
        {'T', 10},
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
            //cout << "  Hand: " << pair[0] << ", Bet: " << pair[1] << ", Rank: " << rank << "\n";
            hands.erase(pair[0]);
            totalWinnings += rank * stoi(pair[1]);
            rank--;
        }
    }
    
    for (string s : hands) {
        cout << s << endl;
    }
    
    cout << totalWinnings << endl;
    
    return 0;
}