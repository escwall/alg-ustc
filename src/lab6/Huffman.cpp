#include<iostream>
#include<unordered_map>
#include<queue>
#include<fstream>
#include<utility>
#include<cmath>

using namespace std;

using Node = struct Node {
    char c;
    int cnt;
    string code;
    Node* left;
    Node* right;

    Node(char _c, int _cnt, string _code, Node* _left, Node* _right) :
    c(_c), cnt(_cnt), code(_code), left(_left), right(_right) {

    }
    Node() : c(' '), cnt(0), left(nullptr), right(nullptr) {}
    // friend bool operator < (const Node& n1, const Node n2) {
    //     return n1.cnt > n2.cnt;
    // }
};

struct myCompare
{
    bool operator () (Node* n1, Node* n2) {
        return n1->cnt > n2->cnt;
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
        char c = ' ';
        fin >> c;
        insert_char(dict, c);
    }
    return dict;
}

Node* merge_node(Node* n1, Node* n2) {
    Node* root = new Node(' ', n1->cnt+n2->cnt, "", n1, n2);
    return root;
}

Node* create_HuffmanTree(priority_queue<Node*, vector<Node*>, myCompare > min_q, int size) {
    Node* root = nullptr;
    while(min_q.size() > 1) {
        Node* min1, *min2;
        min1 = min_q.top();
        min_q.pop();
        min2 = min_q.top();
        min_q.pop();
        // cout << min1->c << ":" << min1->cnt << ", " << min2->c << ":" << min2->cnt << endl;
        root = merge_node(min1, min2);
        min_q.push(root);
    }
    return root;
}

void firstR(Node* root, string code, ofstream& fout, int& sum) {
    if(!root) return;
    
    if(root->c != ' ') {
        fout << root->c << " " << root->cnt << " " << code << endl;
        root->code = code;
        sum += root->cnt * code.length();
    }
    firstR(root->left, code + "0", fout, sum);
    firstR(root->right, code + "1", fout, sum);
}

double log2(int n) {
    double a = 2;
    return log(n)/log(a);
}

int main() {
    string data_path = "./orignal.txt";
    string save_path = "./table.txt";
    auto dict = create_dict(data_path);
    int alpha = 0;
    // cout << dict.size() << endl;
    priority_queue<Node*, vector<Node*>, myCompare > min_q;
    for(auto it = dict.begin(); it != dict.end(); it++) {
        // cout << it->first <<": " << it->second << endl; 
        alpha += it->second;
        min_q.push(new Node(it->first, it->second, "", nullptr, nullptr));
    }
    // while (!min_q.empty())
    // {
    //     auto e = min_q.top();
    //     cout << e->c << " " << e->cnt << endl;
    //     min_q.pop();
    // }
    
    Node* root = create_HuffmanTree(min_q, min_q.size());
    ofstream fout;
    fout.open(save_path);
    int sum = 0;
    int size = min_q.size();
    firstR(root, "", fout, sum);
    double bit = ceil(log2(size));
    double zip_rate = (double)(sum * 100.0 / bit / alpha);
    cout << "压缩率为：" << zip_rate << "%" << endl;
    return 0;
}