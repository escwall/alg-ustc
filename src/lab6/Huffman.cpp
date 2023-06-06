#include<iostream>
#include<unordered_map>
#include<queue>
#include<fstream>
#include<utility>

using namespace std;

using Node = struct Node {
    char c;
    int cnt;
    Node* left;
    Node* right;

    Node(char _c, int _cnt, Node* _left, Node* _right) :
    c(_c), cnt(_cnt), left(_left), right(_right) {

    }
    friend bool operator < (Node n1, Node n2) {
        return n1.cnt > n2.cnt;
    }
};

void insert_char(unordered_map<char,int>& dict, char c) {
    if(c == ' ' || c == '\n') return;
    auto it = dict.find(c);
    if(it == dict.end()) {
        dict.insert(pair<char,int>(c, 1));
    }
    else {
        it->second++;
    }
}

unordered_map<char,int> create_dict(const string& path) {
    ifstream fin;
    fin.open(path);
    unordered_map<char,int> dict;
    while(!fin.eof()) {
        char c;
        fin >> c;
        insert_char(dict, c);
    }
    return dict;
}

int main() {
    string data_path = "./orignal.txt";
    auto dict = create_dict(data_path);
    // cout << dict.size() << endl;
    priority_queue<Node> min_q;
    for(auto it = dict.begin(); it != dict.end(); it++) {
        // cout << it->first <<": " << it->second << endl; 
        min_q.emplace(Node(it->first, it->second, nullptr, nullptr));
    }

    return 0;
}