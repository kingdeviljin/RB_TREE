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
//�ǵݹ�汾�Ķ�����������Һ���
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
		if (k != x->key)//���û�ҵ��˴�����ֵ����ô������¼���游�͸����ֵ�� 
		{
			p2 = p1;
			p1 = x;
		}
	}
	return x;
}
void LEFT_ROTATE(struct Tree*T, struct Tree*x)
{//����ת������������٢ڢ���������ת����ġ� 
	struct Tree*p1=nil,*p2=nil;
	struct Tree*y = x->right;//����y��㡣      
	x->right=y->left;//���д����Լ������if�ṹ�����ǡ�y�����ӳ�Ϊx���Һ��ӡ����� 
	ITERATIVE_TREE_SEARCH(root, x->key, p1, p2);
	if (p1 == nil)//���д����Լ������if-else�ṹ���Ĺ����ǡ�y��Ϊ�������µĸ������� 
	{
		root = y;
	}
	else if (x == p1->left)
	{
		p1->left = y;
	}
	else p1->right = y;
	y->left = x;//���д����Լ�����һ�ж�����ˡ�x��Ϊy�����ӡ����� 51
}
void RIGHT_ROTATE(struct Tree*T, struct Tree*x)
{//����ת 
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
		ITERATIVE_TREE_SEARCH(root, z->key, p1, p2);//p1�Ǹ���� p2���游��� 
		if (p1->color != RED)
		{
			break;
		}
		if (p1 == p2->left)
		{
			struct Tree*y = p2->right;//���� 
			if (y->color == RED)//���һ������Ϊ��ɫ           
			{//��p1,y,p2��ɫ�Ա�������5�����ҽ����z�ĸ�����z���Ǻ�ɫ�������               
				p1->color = BLACK;
				y->color = BLACK;
				p2->color = RED;
				z = p2;//��z���游��㵱���½��z������һ��ѭ�� 89           
			}
			else
			{
				if (z == p1->right)//����������z�Ƿ���һ���Һ���������Ϊ��ɫ��ǰ����p1��㲻��Ҷ�ӽ�� 93                
				{//ʹ��һ�����������2ת��Ϊ���3 
					z = p1;
					LEFT_ROTATE(T, z);//���ڽ���if�����֪��ת��㲻������Ҷ�ӽ�㣬�����Ͳ����ж�z�Ƿ���Ҷ�ӽ���ˡ� 
					ITERATIVE_TREE_SEARCH(root, z->key, p1, p2);//p1=z->parent,p2=z->parent->parent 
				}
				p1->color = BLACK;//���������z��һ������������Ϊ��ɫ���ı�z�ĸ����游�����ɫ����һ���������Ա�������5�� 
				p2->color = RED;
				if (p2 != nil) RIGHT_ROTATE(T, p2);//����p2������Ҷ�ӽ�㣬������û�����һ��if�ж�
			}
		}
		else//����else��֧����������104       
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
	root->color = BLACK;//�����������Ϊ��ɫ��
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
//�������
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

