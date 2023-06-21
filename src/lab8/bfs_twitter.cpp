#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<queue>
#include<chrono>
#include<unordered_map>
#include<set>

#define v_num 81306
#define e_num 1768149

class vertex {
    public:
    int val;
    int idx;
    vertex* next;
    bool is_visited = false;

    vertex(int x) : val(x), idx(-1), next(nullptr) {}
    vertex() : val(-1), idx(-1), next(nullptr) {}
};

using namespace std;

int main() {
    ifstream fin;
    fin.open("./twitter_small.txt");
    vector<vertex*> adj_table(v_num, new vertex());
    unordered_map<int, int> m;
    int idx = 0;
    int edge = 0;
    while (!fin.eof()) {
        int in, out;
        fin >> in >> out;
        edge++;
        auto base = m.find(in);
        if(base == m.end()) { //下标映射表中未找到入结点
            m.insert(pair<int, int>(in, idx)); //映射表中插入入结点及其下标索引pair
            auto& head = adj_table[idx];
            head->val = in;
            head->idx = idx;
            vertex* node = new vertex(out);
            node->next = head->next;
            head->next = node; //头插法添加边
            idx++;
        }
        else { //找到入结点，在其链表头插入边
            int i = base->second;
            auto& head = adj_table[i];
            vertex* node = new vertex(out);
            node->next = head->next;
            head->next = node; //头插法添加边
        }
    }

    auto begin = chrono::system_clock::now();
    queue<int> q;
    q.push(0);
    int cnt = 0;
    while(!q.empty()) {
        auto head = adj_table[q.front()];
        head->is_visited = true;
        head = head->next;
        while(head) {
            if(head->next && head->next->idx != -1 && head->next->is_visited == false) {
                q.push(head->idx);
                head->next->is_visited = true;
            }
            head = head->next;
        }
        q.pop();
        cnt++;
        cout << cnt << endl;
    }
    auto end = chrono::system_clock::now();
    cout << "共访问" << cnt << "个结点" << endl;
    cout << "耗时" << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "ms" << endl;
    return 0;
}