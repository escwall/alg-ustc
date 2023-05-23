#include<iostream>
#include<vector>

using namespace std;

void print(const vector<vector<int>>& s, int i, int j) {
    if(i == j) {
        cout << "A" << i+1;
    }
    else {
        cout << "(";
        print(s, i, s[i][j]);
        print(s, s[i][j]+1, j);
        cout << ")";
    }
}

int main() {
    vector<int> p;
    int e;
    while(cin >> e) {
        p.emplace_back(e);
        if('\n' == cin.get())
            break;
    }
    int n = p.size() - 1;
    vector<vector<int>> dp(n, vector<int>(n)), s(dp);
    for(int len = 2; len <= n; ++len) {
        for(int i = 0; i < n - len + 1; ++i) {
            int k = i + len - 1;
            dp[i][k] = INT_MAX;
            for(int j = i; j < k; ++j) {
                int cost = dp[i][j] + dp[j+1][k] + p[i] * p[j+1] * p[k+1];
                if(cost < dp[i][k]) {
                    dp[i][k] = cost;
                    s[i][k] = j;
                }
            } 
        }
    }
    cout << "-------代价矩阵--------" << endl;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
    cout << "-------括号矩阵--------" << endl;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            cout << s[i][j] << " ";
        }
        cout << endl;
    }
    print(s, 0, 5);
    return 0;
}