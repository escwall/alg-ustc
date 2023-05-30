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

    vector<int> dp(len1, 0);
    for(int i = 0; i < len1; ++i) {
        if(str1[i] == str2[0]) dp[i]++;
    }
    int i = 1;
    while(i < len2) {
        int leak = 0, left = 0;
        for(int j = 0; j < len1; ++j) {
            int temp = dp[j];
            if(str1[j] == str2[i]) {
                dp[j] = leak + 1;
            }
            else if(dp[j] < left) {
                dp[j] = left;
            }
            left = dp[j];
            leak = temp;
        }
        i++;
    }
    
    cout << "str1=" << str1 << ", str2=" << str2 << endl; 
    
    cout << "公共子序列长度为：" << dp[len1-1] << endl;
    return 0;
}