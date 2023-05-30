#include<iostream>
#include<fstream>
#include<string>
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;


void printTrace(const string& s1, const string& s2, const vector<vector<string>>& trace, int row, int col) {
    if(trace[row][col] == "") {
        return;
    }
    else if(trace[row][col] == "↖") {
        printTrace(s1, s2, trace, row-1, col-1);
        cout << s1[row-1];
    }
    else if(trace[row][col] == "↑") {
        printTrace(s1, s2, trace, row-1, col);
    }
    else {
        printTrace(s1, s2, trace, row, col-1);
    }
}

int main() {
    fstream fin;
    fin.open("./data.txt");
    string str1, str2;
    fin >> str1 >> str2;
    int len1, len2;
    len1 = str1.length(), len2 = str2.length();
    if(len1 > len2) {
        swap(len1, len2);
        swap(str1, str2);
    }
    vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));
    vector<vector<string>> trace(len1 + 1, vector<string>(len2 + 1));
    for(int i = 1; i <= len1; ++i) {
        for(int j = 1; j <=len2; ++j) {
            if(str1[i-1] == str2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
                trace[i][j] = "↖";
            }
            else if(dp[i-1][j] >= dp[i][j-1]) {
                dp[i][j] = dp[i-1][j];
                trace[i][j] = "↑";
            }
            else {
                dp[i][j] = dp[i][j-1];
                trace[i][j] = "←";
            }
        }
    }
    cout << "str1=" << str1 << ", str2=" << str2 << endl; 
    if(dp[len1][len2]){
        cout << "公共子序列为：";
        printTrace(str1, str2, trace, len1, len2);
        cout << ", ";
    } 
    cout << "公共子序列长度为：" << dp[len1][len2] << endl;
    return 0;
}