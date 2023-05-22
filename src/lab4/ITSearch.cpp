#include<iostream>
#include<fstream>
#include<string>
#include<queue>

using namespace std;

enum COLOR {RED, BLACK};

using interval = struct interval {
    int low;
    int high;
    interval(int _low, int _high) : low(_low), high(_high) {}
    interval() {
        low = high = 0;
    }
};

using TNode = struct TNode
{
    interval key;
    int max;
    COLOR color;
    TNode* parent;
    TNode* left;
    TNode* right;

    TNode(interval _key) : 
    key(_key), max(_key.high), color(RED), parent(nullptr), left(nullptr), right(nullptr) {} //构造函数初始化参数

    TNode(const TNode* node) {
        key = node->key;
        max = node->max;
        color = node->color;
        parent = node->parent;
        left = node->left;
        right = node->right;
    }

};

class IntervalTree {
private:
    TNode* root;

    void leftRotation(TNode* x) {
        TNode* y = x->right;
        x->right = y->left;
        if(y->left != nullptr) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if(x->parent == nullptr) {
            root = y;
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
                        
                        // } 
                    }
                    else {
                        if(z == z->parent->right) {
                            z = z->parent;
                            leftRotation(z);
                            
                            
                        }
                        z->parent->color = BLACK;
                        z->parent->parent->color = RED;
                        rightRotation(z->parent->parent);
                        
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
                        
                        // }
                    }
                    else {
                        if(z == z->parent->left) {
                            z = z->parent;
                            rightRotation(z);
                        
                        }
                        z->parent->color = BLACK;
                        z->parent->parent->color = RED;
                        leftRotation(z->parent->parent);
                        
                    }
                }
            }
        }
        if(root->color == RED) {
            root->color = BLACK;
            
        }
        // if(!flag)
        //     cout << "case0 ";
    }

    bool overleap(TNode* n1, TNode* n2) {
        if(n1->key.low > n2->max || n1->max < n2->key.low) 
            return false;
        else return true;
    }

    ~IntervalTree() {
        delete root;
        root = nullptr;
        
    }

public:
    IntervalTree() : root(nullptr) {
        
    }

    void insert(interval key) {
        TNode* z = new TNode(key); //待插入的新结点, 左右孩子以及颜色均已在构造函数初始化
        TNode* y = nullptr; //为待插入结点记录其父结点
        TNode* x = root; //寻找插入位置

        while(x != nullptr) {
            y = x;
            if(z->key.high < x->key.low)
                x = x->left;
            else 
                x = x->right;
        }
        z->parent = y;
        if(y == nullptr) {
            root = z;
        }
        else if(z->key.high < y->key.low)
            y->left = z;
        else 
            y->right = z;
        insertFixup(z);
    }

    TNode* search(TNode* i) {
        auto x = root;
        while(x != nullptr && !overleap(x, i)) {
            if(x->left->max < i->key.low) {
                x = x->right;
            }
            else {
                x = x->left;
            }
        }
        return x;
    }
};

int main() {
    ifstream fin;
    fin.open("./insert.txt");
    if(!fin.is_open()) {
        cout << "Can't open input file!" << endl;
    }
    else {
        IntervalTree* it = new IntervalTree();
        int size;
        fin >> size;
        while(!fin.eof()) {
            int low, high;
            fin >> low >> high;
            it->insert(interval(low, high));
        }
        int low, high;
        cout << "请输入待查找区间: [low, high]" << endl;
        cin >> low >> high;
        auto target = it->search(new TNode(interval(low, high)));
        if(target == nullptr) {
            cout << "无重叠区间" << endl;
        }
        else {
            cout << "重叠区间为[" << target->key.low << ", " << target->key.high << "]" << endl;
        }
    }
    return 0;
}