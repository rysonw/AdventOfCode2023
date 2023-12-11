#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <unordered_map>

int main() {
    
    //40828492
    //233101111101487
    
    long long thisTime = 40828492;
    long long distance = 233101111101487;
    
    int currWins = 0;
    for (int i = 1; i < thisTime; ++i) {
        if (i * (thisTime - i) > distance) {
            currWins++;
        }
    }

    cout << currWins << endl;
    return 0;
}