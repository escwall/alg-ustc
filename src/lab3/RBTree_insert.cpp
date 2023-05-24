#include<iostream>
#include<fstream>
#include<string>
#include<queue>

using namespace std;

enum COLOR {RED, BLACK};

using TNode = struct TNode //结点数据结构
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

class RBTree { //红黑树类
private:
    TNode* root; //红黑树根结点
    ofstream lnr, nlr, lot; //用于中序、先序、层序遍历的文件流

    void leftRotation(TNode* x) { //左旋
        TNode* y = x->right; //x的右孩子结点变为当前子树的根
        x->right = y->left; //x的右孩子变为y的左孩子
        if(y->left != nullptr) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if(x->parent == nullptr) { //x为根结点的情况
            root = y;
            _root = root;
        }
        else if(x == x->parent->left) {
            x->parent->left = y;
        }
        else 
            x->parent->right = y;
        y->left = x; //x变为y的左孩子
        x->parent = y;
    }

    void rightRotation(TNode* x) { //与左旋同理，左右相反即可
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

    void insertFixup(TNode* z) { //插入操作后维护红黑树性质
        while (z->parent != nullptr && z->parent->color == RED) { //z的父结点为红色，需要调整
            if(z->parent->parent)
            {    
                if(z->parent == z->parent->parent->left) { //父结点为祖父结点的左孩子
                    TNode* y = z->parent->parent->right;
                    if(y && y->color == RED) {  //叔叔结点为红色，将其和父结点都涂黑，祖父结点涂红，对应case1的情况
                        z->parent->color = BLACK;
                        y->color = BLACK;
                        z->parent->parent->color = RED;
                        z = z->parent->parent;
                        cout << "case1 ";
                    }
                    else {
                        if(z == z->parent->right) { //z为父结点的右孩子，对应形状为'<'
                            z = z->parent;
                            leftRotation(z); //将z的父结点左旋,调整形状为'/'
                            cout << "case2 ";
                        }
                        z->parent->color = BLACK;
                        z->parent->parent->color = RED;
                        rightRotation(z->parent->parent); //右旋祖父结点
                        cout << "case3 ";
                    }
                    
                }
                else { //父结点为祖父结点的右孩子，与上面逻辑类似，左右相反即可
                    TNode* y = z->parent->parent->left;
                    if(y && y->color == RED) {
                        z->parent->color = BLACK;
                        y->color = BLACK;
                        z->parent->parent->color = RED;
                        z = z->parent->parent;
                        cout << "case4 ";
                    }
                    else {
                        if(z == z->parent->left) { //z为父结点的左孩子，对应形状为'>' 
                            z = z->parent;
                            rightRotation(z); //将z的父结点右旋,调整形状为'\'
                            cout << "case5 "; 
                        }
                        z->parent->color = BLACK;
                        z->parent->parent->color = RED;
                        leftRotation(z->parent->parent); //左旋祖父结点
                        cout << "case6 ";
                    }
                }
            }
        }
        if(root->color == RED) { //如果根结点为红色，将根结点涂黑，对应case7的情况
            root->color = BLACK;
            cout << "case7 ";
        }
    }
    ~RBTree() { //析构函数
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

    void insert(int key) { //向红黑树中插入值为key的结点
        TNode* z = new TNode(key); //待插入的新结点, 左右孩子以及颜色均已在构造函数初始化
        TNode* y = nullptr; //为待插入结点记录其父结点
        TNode* x = root; //寻找插入位置

        while(x != nullptr) {
            y = x;
            if(z->key < x->key) //待插入结点值小于当前结点值，左子树找合适位置
                x = x->left;
            else //否则在右子树中找合适位置
                x = x->right;
        }
        z->parent = y;
        if(y == nullptr) { //插入位置为根结点情况
            root = z;
            _root = root;
        }
        else if(z->key < y->key)
            y->left = z;
        else 
            y->right = z;
        insertFixup(z); //插入新结点后维护红黑树
    }

    void LNR(const TNode* root) { //中序遍历
        if(root == nullptr) return;
        LNR(root->left);
        string color = (root->color == RED) ? "red" : "black";
        lnr << root->key << ", " << color << endl;
        LNR(root->right);
    }

    void NLR(const TNode* root) { //先序遍历
        if(root == nullptr) return;
        string color = (root->color == RED) ? "red" : "black";
        nlr << root->key << ", " << color << endl;
        NLR(root->left);
        NLR(root->right);
    }

    void LOT(const TNode* root) { //层序遍历
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