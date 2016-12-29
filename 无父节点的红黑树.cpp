#include <iostream>
using namespace std;
enum {
	BLACK = 0,
	RED = 1
};                                       
const int NIL = -1;
struct NODE
{
	NODE *left;
	NODE *right;
	int val;
	int color;
};
const int LEN = sizeof(NODE);
struct NODE *root;
struct NODE *nil;
void ITERATIVE_TREE_SEARCH(struct NODE *x, int val, struct NODE*&p1, struct NODE*&p2)
{
	//可能存在root结点判断bug
	while (val != x->val)
	{
		p2 = p1;
		p1 = x;
		if (val<x->val)
		{
			x = x->left;
		}
		else
		{
			x = x->right;
		}
	}
};

void LEFT_ROTATION(struct NODE *ROOT, struct NODE *x)
{
	struct NODE *p1 = nil, *p2 = nil;
	struct NODE *y = x->right;
	x->right = y->left;
	ROOT = root;
	ITERATIVE_TREE_SEARCH(ROOT, x->val, p1, p2);
	if (p1 == nil)//解决root bug
	{
		root = y;
	}
	else if (x == p1->left)
	{
		p1->left = y;
	}
	else
	{
		p1->right = y;
	}
	y->left = x;
}

void RIGHT_ROTATION(struct NODE *ROOT, struct NODE *x)
{
	struct NODE *p1 = nil, *p2 = nil;
	struct NODE *y = x->left;
	x->left = y->right;
	ROOT = root;
	ITERATIVE_TREE_SEARCH(ROOT, x->val, p1, p2);
	if (p1 == nil)
	{
		root = y;
	}
	else if (x == p1->left)
	{
		p1->left = y;
	}
	else
	{
		p1->right = y;
	}
	y->right = x;
}
void RB_INSERT_FIXUP(struct NODE *Root, struct NODE *z)
{
	struct NODE*p1 = nil, *p2 = nil, *y = nil;
	Root = root;
	ITERATIVE_TREE_SEARCH(Root, z->val, p1, p2);
	while (p1->color == RED)
	{
		ITERATIVE_TREE_SEARCH(Root, z->val, p1, p2);
		if (p1 == p2->left)
		{
			y = p2->right;
			if (y->color == RED)
			{
				p1->color = BLACK;
				p2->color = RED;
				y->color = BLACK;
				z = p2;
			}
			else
			{
				if (z == p1->right)
				{
					z = p1;
					LEFT_ROTATION(Root, z);
					ITERATIVE_TREE_SEARCH(Root, z->val, p1, p2);
				}
				p1->color = BLACK;
				p2->color = RED;
				RIGHT_ROTATION(Root, p2);
			}
		}
		else
		{
			y = p2->left;
			if (y->color == RED)
			{
				p1->color = BLACK;
				p2->color = RED;
				y->color = BLACK;
				z = p2;
			}
			else
			{
				if (z == p1->left)
				{
					z = p1;
					RIGHT_ROTATION(Root, z);
					ITERATIVE_TREE_SEARCH(Root, z->val, p1, p2);
				}
				p1->color = BLACK;
				p2->color = RED;
				LEFT_ROTATION(Root, p2);
			}
		}
	}
	root->color = BLACK;
};
void RB_INSERT(struct NODE *Root, struct NODE *new_node)
{
	NODE *x = root, *y = nil;
	Root = root;
	while (x != nil)
	{
		y = x;
		if (x->val>new_node->val)
		{
			x = x->left;
		}
		else
		{
			x = x->right;
		}
	}
	if (y == nil)
	{
		root = new_node;
	}
	else if (new_node->val<y->val)
	{
		y->left = new_node;
	}
	else
	{
		y->right = new_node;
	}
	new_node->left = nil;
	new_node->right = nil;
	new_node->color = RED;
	RB_INSERT_FIXUP(Root, new_node);
}

void InOderTraverse(struct NODE *p)
{
	if (p != nil)
	{
		InOderTraverse(p->left);
		cout <<"value: " <<p->val << " color:" << p->color << endl;
		InOderTraverse(p->right);
	}
}

int main()
{
	NODE *ROOT = new NODE;
	nil = new NODE;
	nil->left = nil;
	nil->right = nil;
	nil->val = 0;
	nil->color = BLACK;
	ROOT = nil;
	root = ROOT;
	//	root->parent = nil;
	int arr[6] = { 41,38,31,12,19,8 };
	for (int i = 0; i < 6; ++i)
	{
		NODE *z = new NODE;
		z->val = arr[i];
		RB_INSERT(ROOT, z);
		InOderTraverse(root);
		cout << "-----------------------" << endl;
	}
	system("pause");
	return 0;
}