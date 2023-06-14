#include<iostream>
#include<fstream>
#include<string>
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;


void printTrace(const string& s1, const string& s2, const vector<vector<string>>& trace, int row, int col) { //递归打印LCS
    if(trace[row][col] == "") {
        return;
    }
    else if(trace[row][col] == "↖") { //该元素是LCS的一部分，之后再往左上角走
        printTrace(s1, s2, trace, row-1, col-1);
        cout << s1[row-1];
    }
    else if(trace[row][col] == "↑") { //往上走
        printTrace(s1, s2, trace, row-1, col);
    }
    else { //往左走
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
    if(len1 > len2) { //保证str1一定是长度较短的那一个
        swap(len1, len2);
        swap(str1, str2);
    }
    vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0)); //LCS长度记录数组
    vector<vector<string>> trace(len1 + 1, vector<string>(len2 + 1)); //LCS位置信息记录数组
    for(int i = 1; i <= len1; ++i) {
        for(int j = 1; j <=len2; ++j) {
            if(str1[i-1] == str2[j-1]) { //当前的元素是两个序列的公共元素
                dp[i][j] = dp[i-1][j-1] + 1;
                trace[i][j] = "↖";
            }
            else if(dp[i-1][j] >= dp[i][j-1]) { //当前的元素不是两个序列的公共元素，挑选从上方和左方来的较大的那个公共子序列
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