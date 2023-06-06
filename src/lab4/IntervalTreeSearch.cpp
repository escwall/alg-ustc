#include <iostream>
#include <string>
#include <windows.h>
#include<fstream>
using namespace std;

struct Node //树结点
{
	int low;//低端点 
	int high;//高端点 
	int max;//以当前结点为根的子树中所有区间端点的最大值
	string color;//颜色 
	Node *pParent;//父结点 
	Node *pLeft;//左孩子 
	Node *pRight;//右孩子 
};
 
class IntervalTree //区间树类
{
public:
	IntervalTree();
	~IntervalTree();
	void LeftRotate(Node* px);//左旋
	void RightRotate(Node* px);//右旋
	void Insert(Node* pz);//插入
	void InsertFixUp(Node* pz);//插入调整
	void InorderTreeWalk( Node* px );//中序遍历
	Node* GetRoot(){ return this->pT_root; }
	Node* GetNil(){ return this->pT_nil; }
	Node* IntervalSearch( Node* i );//区间树查找 
private:
	Node* pT_nil;
	Node* pT_root;
};
 
IntervalTree::IntervalTree()
{//构造一棵区间树 
	pT_nil = new Node; 
	pT_nil->color = "Black";//颜色设为BLACK 
	pT_nil->max = 0;
	pT_root = pT_nil;
}
IntervalTree::~IntervalTree()
{
	if( pT_nil != NULL )
		delete pT_nil;
}
 
void IntervalTree::LeftRotate(Node *px)
{//左旋 
	Node* py = px->pRight;//用py记录px的右孩子 
	px->pRight = py->pLeft;//px的右孩子是py的左孩子 
	if( py->pLeft != pT_nil )
		py->pLeft->pParent = px;
	py->pParent = px->pParent;//py的父结点为px的父结点 
	if(px->pParent == pT_nil )//下面判断py为父结点的哪个孩子 
		pT_root = py;//根 
	else if( px == px->pParent->pLeft )
		px->pParent->pLeft = py;//左 
	else px->pParent->pRight = py;//右 
	py->pLeft = px;
	px->pParent = py;
	py->max = max( py->high,max(py->pLeft->max,py->pRight->max) );
	px->max = max( px->high,max(px->pLeft->max,px->pRight->max) );
}
void IntervalTree::RightRotate(Node *py)
{//右旋 
	Node* px = py->pLeft;
	py->pLeft = px->pRight;
	px->pRight->pParent = py;
	px->pParent = py->pParent;
	if(py->pParent == pT_nil )
		pT_root = px;
	else if( py == py->pParent->pLeft )
		py->pParent->pLeft = px;
	else py->pParent->pRight = px;
	px->pRight = py;
	py->pParent = px;
	px->max = py->max;
	py->max = max( py->high,max(py->pLeft->max,py->pRight->max) );
	px->max = max( px->high,max(px->pLeft->max,px->pRight->max) );
}
 
void IntervalTree::Insert( Node* pz)
{//插入 
	pz->max = pz->high;
	Node* py = pT_nil;
	Node *px  = pT_root;
	while( px != pT_nil )
	{
		px->max = max( pz->high,px->max );
		py = px;//用py记录px 
		if( pz->low < px->low )
			px = px->pLeft;
		else
			px = px->pRight;
	}
	pz->pParent = py;
	if( py == pT_nil )
		pT_root = pz;
	else if( pz->low < py->low )
		py->pLeft = pz;
	else
		py->pRight = pz;
	pz->pLeft = pT_nil;
	pz->pRight = pT_nil;
	pz->color = "Red";
	InsertFixUp( pz );
}
 
void IntervalTree::InsertFixUp(Node* pz)
{//插入修正 
	Node* py = NULL;
	while( "Red" == pz->pParent->color )
	{
		if(pz->pParent == pz->pParent->pParent->pLeft )
		{
			py = pz->pParent->pParent->pRight;
			if( py->color == "Red" )
			{
				pz->pParent->color = "Black";
				py->color = "Black";
				pz->pParent->pParent->color = "Red";
				pz = pz->pParent->pParent;
			}
			else
			{
				if( pz == pz->pParent->pRight )
				{
					pz = pz->pParent;
					LeftRotate( pz );
				}
				pz->pParent->color = "Black";
				pz->pParent->pParent->color = "Red";
				RightRotate( pz->pParent->pParent );
			}
		}
		else if(pz->pParent == pz->pParent->pParent->pRight )
		{
			py = pz->pParent->pParent->pLeft;
			if( py->color == "Red" )
			{
				pz->pParent->color = "Black";
				py->color = "Black";
				pz->pParent->pParent->color = "Red";
				pz = pz->pParent->pParent;
			}
			else
			{
				if( pz == pz->pParent->pLeft )
				{
					pz = pz->pParent;
					RightRotate( pz );
				}
				pz->pParent->color = "Black";
				pz->pParent->pParent->color = "Red";
				LeftRotate( pz->pParent->pParent );
			}
		}
	}
	pT_root->color = "Black";
}
void IntervalTree::InorderTreeWalk( Node* px )
{//中序遍历 
	if( px != pT_nil )
	{
		InorderTreeWalk( px->pLeft );
		cout << px->low << " " << px->high << " " << px->color << endl;
		InorderTreeWalk( px->pRight );
	}
}
Node* IntervalTree::IntervalSearch( Node* i)
{//区间树查找 
	Node* x = pT_root; //查找与i重叠的区间x的过程从以x为根的树根开始  
	while( x != pT_nil && ( x->high < i->low || i->high < x->low ) )
	{//当x指向pT.nil或找到重叠区间时过程结束 
		if( x->pLeft != pT_nil && x->pLeft->max >= i->low )
			x = x->pLeft;//去左区间查找 
		else
			x = x->pRight;//去右区间查找 
	}
	return x;
}
int main()
{
	IntervalTree IntervalTree;
    Node* e = new Node();
    fstream fin;
    fin.open("./insert.txt");
    int size;
    fin >> size;
    while(!fin.eof()) {
        Node* e = new Node();
        fin >> e->low >> e->high;
        IntervalTree.Insert(e);
    }
	cout << endl;
 
	bool bquit = true;
	Node temp;
	cout << "区间树中序遍历结果为：" << endl;
	IntervalTree.InorderTreeWalk(IntervalTree.GetRoot());
	while(bquit)
	{
		cout << "输入低端点和高端点: ";
		cin >> temp.low >> temp.high;
		Node* p = IntervalTree.IntervalSearch(&temp);
		if(p != IntervalTree.GetNil() )
			cout << "[" << p->low  << ',' << p->high << "]" << endl;
		else
			cout << "无重叠区间" << endl;
	}
	
	return 0;
}