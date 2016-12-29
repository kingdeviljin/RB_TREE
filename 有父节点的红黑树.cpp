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
	NODE *parent;
	int val;
	int color;
};
struct NODE *root;
struct NODE *nil;
//void ITERATIVE_TREE_SEARCH(struct NODE*x, int val, struct NODE*&p1, struct NODE*&p2)
//{
//	//¿ÉÄÜ´æÔÚroot½áµãÅÐ¶Ïbug
//	while (x != nil && val != x->val)
//	{
//		p2 = p1;
//		p1 = x;
//		if (val<x->val)
//		{
//			x = x->left;
//		}
//		else
//		{
//			x = x->right;
//		}
//	}
//};

void LEFT_ROTATION(struct NODE *ROOT, struct NODE *x)
{
//	struct NODE *p1 = nil, *p2 = nil;
	struct NODE *y = x->right;
	x->right = y->left;
	y->parent = x->parent;
//	ITERATIVE_TREE_SEARCH(root, x->val, p1, p2);
	if (x->parent == nil)//½â¾öroot bug
	{
		root = y;
	}
	else if (x == x->parent->left)
	{
		x->parent->left = y;
	}
	else
	{
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

void RIGHT_ROTATION(struct NODE *ROOT, struct NODE *x)
{
//	struct NODE *p1 = nil, *p2 = nil;
	struct NODE *y = x->left;
	x->left = y->right;
	y->parent = x->parent;
//	ITERATIVE_TREE_SEARCH(root, x->val, p1, p2);
	if (x->parent == nil)
	{
		root = y;
	}
	else if (x == x->parent->left)
	{
		x->parent->left = y;
	}
	else
	{
		x->parent->right = y;
	}
	y->right = x;
	x->parent = y;
}
void RB_INSERT_FIXUP(struct NODE *ROOT, struct NODE *z)
{
	struct NODE*p1 = nil, *p2 = nil, *y = nil;
//	ITERATIVE_TREE_SEARCH(root, z->val, p1, p2);
	while (z->parent->color == RED)
	{
//		ITERATIVE_TREE_SEARCH(root, z->val, p1, p2);
		if (z->parent == z->parent->parent->left)
		{
			y = z->parent->parent->right;
			if (y->color == RED)
			{
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				y->color = BLACK;
				z = z->parent->parent;
			}
			else
			{
				if (z == z->parent->right)
				{
					z = z->parent;
					LEFT_ROTATION(ROOT, z);
//					ITERATIVE_TREE_SEARCH(root, z->val, p1, p2);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
				RIGHT_ROTATION(ROOT, z);
			}
		}
		else
		{
			y = z->parent->parent->left;
			if (y->color == RED)
			{
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				y->color = BLACK;
				z = z->parent->parent;
			}
			else
			{
				if (z == z->parent->left)
				{
					z = z->parent;
					RIGHT_ROTATION(ROOT, z);
//					ITERATIVE_TREE_SEARCH(root, z->val, p1, p2);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				LEFT_ROTATION(ROOT, z->parent->parent);
			}
		}
	}
	root->color = BLACK;
};
void RB_INSERT(struct NODE *Root, struct NODE *new_node)
{
	NODE *x = root, *y = nil;
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
	new_node->parent = y;
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
		cout << "value: " << p->val << " color:" << p->color << endl;
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