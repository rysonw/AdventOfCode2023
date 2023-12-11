#include <sstream>
#include <vector>
#include <utility>
#include <cmath>
#include <climits>

using namespace std;


int main() {
    vector<vector<int>> races {{40 , 233}, {82, 1011}, {84, 1110}, {92, 1487}};
    
    int res = -1;
    
    for (vector<int> pair : races) {
        int currWins = 0;
        for (int i = 1; i < pair[0]; ++i) {
            if (i * (pair[0] - i) > pair[1]) {
                currWins++;
            }
        }
        if (res == -1) {
            res = currWins;
        }
        else {
            res *= currWins;
        }
    }

    cout << res << endl;
    return 0;
}