#include<iostream>
using namespace std;

enum color
{
	RED,
	BLACK
};
template<typename K,typename V>
struct BRTreeNode
{
	K _key;
	V _value;
	BRTreeNode<K, V> *_left;
	BRTreeNode<K, V> *_right;
	BRTreeNode<K, V> *_parent;
	int _color;

	BRTreeNode(const K& key, const V& value)
		:_key(key)
		, _value(value)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
		, _color(RED)
	{}
};

template<typename K,typename V>
class BRTree
{
	typedef BRTreeNode<K, V> Node;
public:
	BRTree()
		:_root(NULL)
	{}
	bool Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			_root->_color = BLACK;
			return true;
		}
		Node* parent = NULL;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}
		cur = new Node(key, value);
		if (parent->_key < key)
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_left = cur;
			cur->_parent = parent;
		}

		while (cur != _root && parent->_color == RED)
		{
			Node* grandfather = parent->_parent;
			Node* uncle = NULL;
	    	if (grandfather->_left == parent)
				uncle = grandfather->_right;
			else
				uncle = grandfather->_left;

			if (uncle && uncle->_color == RED)//情况1：u存在且为红
				{
					parent->_color = BLACK;
					uncle->_color = BLACK;
					grandfather->_color = RED;
			}
			else//情况二：叔叔不存在/叔叔存在为黑
			{
				if (grandfather->_left == parent)//父亲在左
				{
					if (parent->_left == cur)//儿子在左
					{
						_RotateR(grandfather);
						parent->_color = BLACK;
						grandfather->_color = RED;
					}
					else//儿子在右
					{
						_RotateL(parent);
						_RotateR(grandfather);
						cur->_color = BLACK;
						grandfather->_color = RED;
					}
				}
				else //父亲在右
				{
					if (parent->_right == cur)//儿子在右
					{
						_RotateL(grandfather);
						parent->_color = BLACK;
						grandfather->_color = RED;
					}
					else//儿子在左
					{
						_RotateR(parent);
						_RotateL(grandfather);
						cur->_color = BLACK;
						grandfather->_color = RED;
					}
				}
			}
			cur = grandfather;
			parent = cur->_parent;
		}
		_root->_color = BLACK;
		return true;
	}

	void _RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;
		subL->_right = parent;
		Node* ppNode = parent->_parent;
		parent->_parent = subL;

		if (ppNode==NULL)
		{
			_root = subL;
			subL->_parent = NULL;
		}
		else if (ppNode->_left == parent)
		{
			ppNode->_left = subL;
			subL->_parent = ppNode;
		}
		else
		{
			ppNode->_right = subL;
			subL->_parent = ppNode;
		}
	}

	void _RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;

		subR->_left = parent;
		Node* ppNode = parent->_parent;
		parent->_parent = subR;

		if (ppNode == NULL)
		{
			_root = subR;
			subR->_parent = NULL;
		}
		else if (ppNode->_left == parent)
		{
			ppNode->_left = subR;
			subR->_parent = ppNode;
		}
		else
		{
			ppNode->_right = subR;
			subR->_parent = ppNode;
		}
	}
	void InOrder()
	{
		_InOrder(_root);
	}

	bool IsBalance()
	{
		if (_root && _root->_color == RED)
		{
			cout << "error:根节点不为黑";
			return false;
		}
		int K = 0;
		int count = 0;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_color == BLACK)
				++K;
			cur = cur->_left;
		}
		return _IsBalance(_root,K,count);
	}
protected:
		void _InOrder(Node* root)
		{
			if (root == NULL)
			{
				return;
			}

			_InOrder(root->_left);
			cout << root->_key << " ";
			_InOrder(root->_right);
		}

		bool _IsBalance(Node* root,int K,int count)
		{
			if (root == NULL)
			{
				return true;
			}

			if (root->_color == RED && root->_parent->_color == RED)
			{
				cout << "error:连续的红节点" << ":";
				cout << root->_key << endl;
				return false;
			}
			if (root->_color == BLACK)
			{
				++count;
			}
			if (root->_left == NULL && root->_right == NULL)
			{
				if (count != K)
				{
					cout << "黑节点数量不相等" << endl;
					return false;
				}
				else
				    return true;
			}
			return _IsBalance(root->_left, K,count) && _IsBalance(root->_right,K,count);
		}
protected:
	Node* _root;
};

void test()
{
	BRTree<int, int> t;
	//int arr1[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	int arr[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]);++i)
	{
		t.Insert(arr[i], i);
	}
	t.InOrder();
	cout << endl;
	cout << "IsBalance?" << t.IsBalance() << endl;
}
int main()
{
	test();
	getchar();
	return 0;
}
