#include<iostream>
#include<vector>

using namespace std;

int main() {
    vector<int> mm;
    while(!cin.eof()) {
        int e;
        cin >> e;
        mm.emplace_back(e);
    }
    int size = mm.size();
    vector<vector<int>> dp(size, vector<int>(size, 0)), s(dp);
    for(int i = 2; i <= size; ++i) {
        for(int j = 0; j < size - i + 1; ++j) {
            int m = j + i - 1;
            dp[j][m] = INT_MAX;
            for(int k = j; k < m; ++k) {
                int cost = dp[j][k] + dp[k+1][m] + mm[j] * mm[k] * mm[m];
                if(cost < dp[j][m]) {
                    dp[j][m] = cost;
                    s[j][m] = k;
                }
            }
        }
    }
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
    cout << "--------------------" << endl;
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            cout << s[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}