#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class TrieNode {
public:
    bool endOfWord;
    unordered_map<char, TrieNode*> children;
    string word;
    
    TrieNode() : endOfWord(false) {}
    
    ~TrieNode() {
        for (auto& child : children) {
            delete child.second;
        }
    }
};

class Trie {
private:
    TrieNode* root;
    
public:
    Trie() : root(new TrieNode()) {}
    
    ~Trie() {
        delete root;
    }
    
    void insert(const string& word) {
        TrieNode* current = root;
        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = new TrieNode();
            }
            current = current->children[c];
        }
        current->endOfWord = true;
        current->word = word;
    }
    
    string search(const string& word) {
        TrieNode* current = root;
        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                return "";
            }
            current = current->children[c];
            if (current->endOfWord) {
                return current->word;
            }
        }
        return "";
    }
};

unordered_map<string, int> stringToNumber = {
    {"zero", 0}, {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4},
    {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}
};

int convertToNumber(const string& s) {
    if (isdigit(s[0])) {
        return s[0] - '0';
    }
    if (stringToNumber.find(s) != stringToNumber.end()) {
        return stringToNumber[s];
    }
    return -1;
}

int main() {
    ifstream inputFile("input.txt");

    unordered_set<char> numChars = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int totalSum = 0;

    Trie* prefixTree = new Trie();
    for (const auto& pair : stringToNumber) {
        prefixTree->insert(pair.first);
    }

    string line;
    while (getline(inputFile, line)) {
        string currSubstring;
        int firstNum = -1;
        int lastNum = -1;

        // Find first num
        for (int i = 0; i < line.length(); ++i) {
            char c = line[i];
            if (numChars.find(c) != numChars.end()) {
                firstNum = c - '0';
                break;
            }
            currSubstring.push_back(c);
            string wordFound = prefixTree->search(currSubstring);
            if (!wordFound.empty()) {
                firstNum = convertToNumber(wordFound);
                break;
            }
        }

        currSubstring.clear();

        // Find last num
        for (int i = line.length() - 1; i >= 0; --i) {
            char c = line[i];
            currSubstring = c + currSubstring;
            if (numChars.find(c) != numChars.end()) {
                lastNum = c - '0';
                break;
            }
            string wordFound = prefixTree->search(currSubstring);
            if (!wordFound.empty()) {
                lastNum = convertToNumber(wordFound);
                break;
            }
        }

        if (firstNum != -1 && lastNum != -1) {
            cout << "Adding: " << firstNum << " + " << lastNum << " for line: " << line << endl;
            totalSum += ((firstNum * 10) + lastNum);
        }
    }

    delete prefixTree;
    cout << "Total Sum: " << totalSum << endl;

    return 0;
}