#include<iostream>
#include<fstream>
#include<string>
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;

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

    vector<vector<int>> dp(3, vector<int>(len1 + 1, 0)); //滚动数组思想
    int i = 0;
    while(i < len2) {
        dp[1] = dp[2]; //TODO：模2
        for(int j = 1; j <=len1; ++j) {
            if(str1[j-1] == str2[i]) {
                dp[2][j] = dp[1][j-1] + 1;
            }
            else if(dp[1][j] >= dp[2][j-1]) {
                dp[2][j] = dp[1][j];
            }
            else {
                dp[2][j] = dp[2][j-1];
            }
        }
        i++;
    }
    
    cout << "str1=" << str1 << ", str2=" << str2 << endl; 
    
    cout << "公共子序列长度为：" << dp[2][len1] << endl;
    return 0;
}