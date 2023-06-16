#include<iostream>
#include<unordered_map>
#include<queue>
#include<fstream>
#include<utility>
#include<cmath>
#include<iomanip>

using namespace std;

using Node = struct Node { //哈夫曼树结点数据结构
    char c; //字符
    int cnt; //出现频数
    string code; //哈夫曼编码
    Node* left;
    Node* right;

    Node(char _c, int _cnt, string _code, Node* _left, Node* _right) :
    c(_c), cnt(_cnt), code(_code), left(_left), right(_right) {

    }
    Node() : c(' '), cnt(0), left(nullptr), right(nullptr) {

    }
};

struct myCompare //构造小顶堆的比较辅助函数
{
    bool operator () (Node* n1, Node* n2) {
        return n1->cnt > n2->cnt;
    }
};


void insert_char(unordered_map<char,int>& dict, char c) { //向字符哈希表dict中插入字符c
    if(c == ' ' || c == '\n') return;
    auto it = dict.find(c);
    if(it == dict.end()) { //哈希表dict中未出现过c
        dict.insert(pair<char,int>(c, 1));
    }
    else { //哈希表dict中出现过c，频数加一
        it->second++;
    }
}

unordered_map<char,int> create_dict(const string& path) { //为数据源创建字符哈希表dict
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

Node* merge_node(Node* n1, Node* n2) { //将两个哈夫曼树结点合并
    Node* root = new Node(' ', n1->cnt+n2->cnt, "", n1, n2);
    return root;
}

Node* create_HuffmanTree(priority_queue<Node*, vector<Node*>, myCompare > min_q, int size) { //构建哈夫曼树
    Node* root = nullptr;
    while(min_q.size() > 1) { //循环直至小顶堆中只剩根结点
        Node* min1, *min2;
        min1 = min_q.top(); //获取当前哈希表中频数最小的结点
        min_q.pop();
        min2 = min_q.top(); //获取哈希表中频数第二小的结点
        min_q.pop();
        root = merge_node(min1, min2); //合并最小以及第二小的结点，将合并后的父结点添加到小顶堆中
        min_q.push(root);
    }
    return root;
}

void firstR(Node* root, string code, ofstream& fout, int& sum) { //先序遍历并为每个结点构建哈夫曼编码
    if(!root) return;
    
    if(root->c != ' ') {
        fout << root->c << " " << root->cnt << " " << code << endl;
        root->code = code;
        sum += root->cnt * code.length();
    }
    firstR(root->left, code + "0", fout, sum);
    firstR(root->right, code + "1", fout, sum);
}

double log2(int n) { //以2为底求对数
    double a = 2;
    return log(n)/log(a);
}

int main() {
    string data_path = "./orignal.txt";
    string save_path = "./table.txt";
    auto dict = create_dict(data_path); //创建字符哈希表
    int alpha = 0;
    priority_queue<Node*, vector<Node*>, myCompare > min_q; //小顶堆
    for(auto it = dict.begin(); it != dict.end(); it++) {
        alpha += it->second; //统计字符总频数
        min_q.push(new Node(it->first, it->second, "", nullptr, nullptr));
    }
    
    Node* root = create_HuffmanTree(min_q, min_q.size()); //构建哈夫曼树
    ofstream fout;
    fout.open(save_path);
    int sum = 0;
    int size = min_q.size();
    firstR(root, "", fout, sum);
    double bit = ceil(log2(size));
    double zip_rate = (double)(sum * 100.0 / bit / alpha); //计算压缩率
    cout << "压缩率为：" << setprecision(4) << zip_rate << "%" << endl;
    return 0;
}