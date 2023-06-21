#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<queue>
#include<chrono>

using namespace std;

int main() {
    ifstream fin;
    fin.open("./data.txt");
    int cnt = 0;
    string s;
    fin >> s;
    for(auto i : s) {
        if(i != ',') {
            cnt++;
        }
    }
    vector<vector<int>> adj(cnt, vector<int>(cnt, 0));
    vector<bool> is_visited(cnt, false);
    while(!fin.eof()) {
        string line;
        fin >> line;
        int from, to;
        from = line[0] - 'A';
        to = line[2] - 'A';
        adj[from][to] = 1;
        adj[to][from] = 1;
    }
    queue<int> q;
    auto begin = chrono::system_clock::now();
    q.push(0);
    int num = 0;
    while(!q.empty()) {
        int from = q.front();
        is_visited[from] = true;
        q.pop();
        cout << (char)(from + 'A');
        num++;
        if(cnt != num) cout << '-';
        for(int i = 0; i < cnt; ++i) {
            if(adj[from][i] == 1 && !is_visited[i]) {
                q.push(i);
                is_visited[i] = true;
            }
        }
    }
    auto end = chrono::system_clock::now();
    cout << "\n遍历结点总数为" << num << ", 共耗时" << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "ms" << endl;
    return 0;
}