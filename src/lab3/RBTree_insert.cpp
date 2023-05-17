#include<iostream>
#include<fstream>
#include<string>
#include<queue>

using namespace std;

enum COLOR {RED, BLACK};

using TNode = struct TNode
{
    int key;
    COLOR color;
    TNode* parent;
    TNode* left;
    TNode* right;

    TNode(int _key) : 
    key(_key), color(RED), parent(nullptr), left(nullptr), right(nullptr) {} //构造函数初始化参数

    TNode(const TNode* node) {
        key = node->key;
        color = node->color;
        parent = node->parent;
        left = node->left;
        right = node->right;
    }
};

class RBTree {
private:
    TNode* root;
    ofstream lnr, nlr, lot;

    void leftRotation(TNode* x) {
        TNode* y = x->right;
        x->right = y->left;
        if(y->left != nullptr) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if(x->parent == nullptr) {
            root = y;
            _root = root;
        }
        else if(x == x->parent->left) {
            x->parent->left = y;
        }
        else 
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rightRotation(TNode* x) {
        TNode* y = x->left;
        x->left = y->right;
        if(y->right != nullptr) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if(x->parent == nullptr) {
            root = y;
            _root = root;
        }
        else if(x == x->parent->left) {
            x->parent->left = y;
        }
        else 
            x->parent->right = y;
        y->right = x;
        x->parent = y;
    }

    void insertFixup(TNode* z) {
        bool flag = false;
        while (z->parent != nullptr && z->parent->color == RED) {
            if(z->parent->parent)
            {    
                if(z->parent == z->parent->parent->left) {
                    TNode* y = z->parent->parent->right;
                    if(y && y->color == RED) {    
                        // if(y->color == RED) {
                        z->parent->color = BLACK;
                        y->color = BLACK;
                        z->parent->parent->color = RED;
                        z = z->parent->parent;
                        cout << "case1 ";
                        flag = true; 
                        // } 
                    }
                    else {
                        if(z == z->parent->right) {
                            z = z->parent;
                            leftRotation(z);
                            cout << "case2 ";
                            flag = true; 
                        }
                        z->parent->color = BLACK;
                        z->parent->parent->color = RED;
                        rightRotation(z->parent->parent);
                        cout << "case3 ";
                        flag = true; 
                    }
                    
                }
                else {
                    TNode* y = z->parent->parent->left;
                    if(y && y->color == RED) {
                        // if(y->color == RED) {
                        z->parent->color = BLACK;
                        y->color = BLACK;
                        z->parent->parent->color = RED;
                        z = z->parent->parent;
                        cout << "case4 ";
                        flag = true; 
                        // }
                    }
                    else {
                        if(z == z->parent->left) {
                            z = z->parent;
                            rightRotation(z);
                            cout << "case5 ";
                            flag = true; 
                        }
                        z->parent->color = BLACK;
                        z->parent->parent->color = RED;
                        leftRotation(z->parent->parent);
                        cout << "case6 ";
                        flag = true; 
                    }
                }
            }
        }
        if(root->color == RED) {
            root->color = BLACK;
            cout << "case7 ";
            flag = true; 
        }
        // if(!flag)
        //     cout << "case0 ";
    }
    ~RBTree() {
        lnr.clear();
        nlr.clear();
        lot.clear();
        lnr.close();
        nlr.close();
        lot.close();
        root = nullptr;
        _root = nullptr;
    }

public:
    const TNode* _root;
    RBTree() : root(nullptr) {
        lnr.open("./LNR.txt", ios_base::out);
        nlr.open("./NLR.txt", ios_base::out);
        lot.open("./LOT.txt", ios_base::out);
        _root = root;
    }

    void insert(int key) {
        TNode* z = new TNode(key); //待插入的新结点, 左右孩子以及颜色均已在构造函数初始化
        TNode* y = nullptr; //为待插入结点记录其父结点
        TNode* x = root; //寻找插入位置

        while(x != nullptr) {
            y = x;
            if(z->key < x->key)
                x = x->left;
            else 
                x = x->right;
        }
        z->parent = y;
        if(y == nullptr) {
            root = z;
            _root = root;
        }
        else if(z->key < y->key)
            y->left = z;
        else 
            y->right = z;
        insertFixup(z);
    }

    void LNR(const TNode* root) {
        if(root == nullptr) return;
        LNR(root->left);
        string color = (root->color == RED) ? "red" : "black";
        lnr << root->key << ", " << color << endl;
        LNR(root->right);
    }

    void NLR(const TNode* root) {
        if(root == nullptr) return;
        string color = (root->color == RED) ? "red" : "black";
        nlr << root->key << ", " << color << endl;
        NLR(root->left);
        NLR(root->right);
    }

    void LOT(const TNode* root) {
        queue<TNode*> q;
        TNode* r = new TNode(root);
        q.push(r);
        while(!q.empty()) {
            auto e = q.front();
            string color = (e->color == RED) ? "red" : "black";
            lot << e->key << ", " << color << endl;
            if(e->left)
                q.push(e->left);
            if(e->right)
                q.push(e->right);
            q.pop();
        }
    }
};


int main() {
    ifstream fin;
    fin.open("./insert.txt");
    if(!fin.is_open()) {
        cout << "Can't open input file!" << endl;
    }
    else {
        cout << "注: case7 对应将根结点涂黑的操作情况" << endl;
        int cnt;
        fin >> cnt;
        RBTree* RBT = new RBTree();
        for(int i = 0; i < cnt; ++i) {
            int key;
            fin >> key;
            RBT->insert(key);
        }
        RBT->LNR(RBT->_root);
        RBT->NLR(RBT->_root);
        RBT->LOT(RBT->_root);
    }
    
    return 0;
}