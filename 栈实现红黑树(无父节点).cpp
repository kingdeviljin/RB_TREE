#include <iostream>
using namespace std;
enum {
	BLACK = 0,
	RED = 1
};
#define Nil -1
#define LEN sizeof(Tree)
struct Tree
{
	struct Tree*left;
	struct Tree*right;
	int key;
	int color;
};
struct Tree *root = NULL;
struct Tree *nil = NULL;
//非递归版本的二叉查找树查找函数
struct Tree*ITERATIVE_TREE_SEARCH(struct Tree*x, int k, struct Tree*&p1, struct Tree*&p2)
{
	while (x != nil&&k != x->key)
	{
		p1 = x;
		if (k < x->key)
		{
			x = x->left;
		}
		else x = x->right;
		if (k != x->key)//如果没找到了待查找值，那么继续记录其祖父和父结点值。 
		{
			p2 = p1;
			p1 = x;
		}
	}
	return x;
}
void LEFT_ROTATE(struct Tree*T, struct Tree*x)
{//左旋转：分三个步骤①②③来叙述旋转代码的。 
	struct Tree*p1=nil,*p2=nil;
	struct Tree*y = x->right;//设置y结点。      
	x->right=y->left;//本行代码以及下面的if结构表达的是“y的左孩子成为x的右孩子”。① 
	ITERATIVE_TREE_SEARCH(root, x->key, p1, p2);
	if (p1 == nil)//本行代码以及下面的if-else结构表达的过程是“y成为该子树新的根”。② 
	{
		root = y;
	}
	else if (x == p1->left)
	{
		p1->left = y;
	}
	else p1->right = y;
	y->left = x;//本行代码以及下面一行都表达了“x成为y的左孩子”。③ 51
}
void RIGHT_ROTATE(struct Tree*T, struct Tree*x)
{//右旋转 
	struct Tree*p1=nil,*p2=nil;
	struct Tree*y = x->left;
	x->left = y->right;
	ITERATIVE_TREE_SEARCH(root, x->key, p1, p2);
	if (p1 == nil)
	{
		root = y;
	}
	else if (x == p1->right)
	{
		p1->right = y;
	}
	else p1->left = y;
	y->right = x;
}
void RB_INSERT_INSERT_FIXUP(struct Tree*T, struct Tree*z)
{
	struct Tree*p1 = nil, *p2 = nil;
	ITERATIVE_TREE_SEARCH(root, z->key, p1, p2);//p1 = z->parent, p2 = z->parent->parent;
	while (1)
	{
		ITERATIVE_TREE_SEARCH(root, z->key, p1, p2);//p1是父结点 p2是祖父结点 
		if (p1->color != RED)
		{
			break;
		}
		if (p1 == p2->left)
		{
			struct Tree*y = p2->right;//叔结点 
			if (y->color == RED)//情况一：叔结点为红色           
			{//给p1,y,p2着色以保持性质5。并且解决了z的父结点和z都是红色结点问题               
				p1->color = BLACK;
				y->color = BLACK;
				p2->color = RED;
				z = p2;//把z的祖父结点当成新结点z进入下一次循环 89           
			}
			else
			{
				if (z == p1->right)//情况二：检查z是否是一个右孩子且叔结点为黑色，前提是p1结点不是叶子结点 93                
				{//使用一个左旋让情况2转变为情况3 
					z = p1;
					LEFT_ROTATE(T, z);//由于进入if语句后可知旋转结点不可能是叶子结点，这样就不用判断z是否是叶子结点了。 
					ITERATIVE_TREE_SEARCH(root, z->key, p1, p2);//p1=z->parent,p2=z->parent->parent 
				}
				p1->color = BLACK;//情况三：是z是一个左孩子且叔结点为黑色，改变z的父和祖父结点颜色并做一次右旋，以保持性质5。 
				p2->color = RED;
				if (p2 != nil) RIGHT_ROTATE(T, p2);//由于p2可能是叶子结点，所以最好还是用一个if判断
			}
		}
		else//下面else分支类似于上面104       
		{
			struct Tree*y = p2->left;
			if (y->color == RED)
			{
				p1->color = BLACK;
				y->color = BLACK;
				p2->color = RED;
				z = p2;
			}
			else
			{
				if (z == p1->left)
				{
					z = p1;
					RIGHT_ROTATE(T, z);
					ITERATIVE_TREE_SEARCH(root, z->key, p1, p2);
				}
				p1->color = BLACK;
				p2->color = RED;
				if (p2 != nil) LEFT_ROTATE(T, p2);
			}
		}
	}
	root->color = BLACK;//最后给根结点着为黑色。
}
void RB_INSERT(struct Tree*T, struct Tree*z)
{
	struct Tree*y = nil;
	struct Tree*x = root;
	while (x != nil)
	{
		y = x;
		if (z->key < x->key)
		{
			x = x->left;
		}
		else x = x->right;
	}
	if (y == nil)
	{
		root = z;
	}
	else if (z->key < y->key)
	{
		y->left = z;
	}
	else y->right = z;
	z->left = nil;
	z->right = nil;
	z->color = RED;
	RB_INSERT_INSERT_FIXUP(T, z);
}
//中序遍历
void InOderTraverse(struct Tree *p)
{
	if (p != nil)
	{
		InOderTraverse(p->left);
		cout << p->key << "" << p->color << "" << endl;
		InOderTraverse(p->right);
	}
}
void main()
{
	nil = new Tree[LEN];
	nil->key = Nil; nil->color = BLACK;
	root = nil;
	int i = 0;
	struct Tree*ROOT = new Tree[LEN];
	cin >> ROOT->key;
	RB_INSERT(nil, ROOT);
	root = ROOT;
	while (i != 12)
	{
		struct Tree*z = new Tree[LEN];
		cin >> z->key;
		RB_INSERT(root, z);
		i++;
	}
	InOderTraverse(root);
}

