#include<iostream>
using namespace std;

template<typename K ,typename V >
struct AVLTreeNode
{
	K _key;
	V _value;
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;
	int _bf;

	AVLTreeNode(const K& key, const V& value)
		:_key(key)
		, _value(value)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
		, _bf(0)
	{}
};

template<typename K,typename V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree()
		:_root(NULL)
	{}

	~AVLTree()
	{}

	bool Insert(const K& key, const V& value)
	{
		
		if (_root == NULL)
		{
			_root = new Node(key, value);
			return true;
		}
		Node *parent = NULL;
		Node *cur = _root;
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
		Node* tmp;
		if (parent->_key < key)
		{
			tmp = new Node(key, value);
			parent->_right = tmp;
			tmp->_parent = parent;
		}
		else 
		{
			tmp = new Node(key, value);
			parent->_left = tmp;
			tmp->_parent = parent;
		}	
		cur = tmp;
		parent = cur->_parent;
		while (parent)
		{
			if (parent->_left == cur)
				parent->_bf--;
			else
				parent->_bf++;

			if (parent->_bf == 0)
			{
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				cur = parent;
				parent = cur->_parent;
			}
			else
			{
				if (parent->_bf == 2)
				{
					if (cur->_bf == 1)
					{
						_RotateL(parent);
					}
					else
					{
						_RotateRL(parent);
					}
				}
				else
				{
					if (cur->_bf == 1)
					{
						_RotateLR(parent);
					}
					else
					{
						_RotateR(parent);
					}
				}
				break;
			}
		}
	}

	void InOrder()
	{
		_InOrder(_root);
	}

	bool Balance()
	{
		return _Balance(_root);
	}
protected:

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
		subR->_parent = ppNode;

		if (ppNode == NULL)
		{
			_root = subR;
		}
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subR;
			}
			else
			{
				ppNode->_right = subR;
			}
		}
		parent->_bf = subR->_bf = 0;
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
		subL->_parent = ppNode;

		if (ppNode == NULL)
		{
			_root = subL;
		}
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subL;
			}
			else
			{
				ppNode->_right = subL;
			}
		}
		parent->_bf = subL->_bf = 0;
	}
	void _RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;
		_RotateR(parent->_right);
		_RotateL(parent);

		if (bf == -1)
		{
			parent->_bf = 0;
			subR->_bf = 1;
		}
		else if (bf == 1)
		{
			parent->_bf = -1;
			subR->_bf = 0;
		}
		else
		{
			parent->_bf = subR->_bf = 0;
		}
		subRL = 0;
	}
	void _RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;

		_RotateL(parent->_left);
		_RotateR(parent);

		if (bf == 1)
		{
			parent->_bf = 0;
			subL->_bf = -1;
		}
		else if (bf == -1)
		{
			subL->_bf = 0;
			parent->_bf = 1;
		}
		else
		{
			subL->_bf = parent->_bf = 0;
		}
		subLR->_bf = 0;
	}

    void _InOrder(Node* root)
	{
		if (root == NULL)
		{
			return ;
		}

		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);

	}

	int _Height(Node* root)
	{
		if (root == NULL)
		{
			return 0;
		}
		int left = _Height(root->_left);
		int right = _Height(root->_right);

		return left > right ? left + 1 : right + 1;		
	}
	bool _Balance(Node* root)
	{
		if (root == NULL)
		{
			return true;
		}

		int left = _Height(root->_left);
		int right = _Height(root->_right);

		if (right - left != root->_bf || abs(left - right) > 1)
		{
			cout << "平衡因子异常" << " ";
			cout << root->_key << endl;
			return false;
		}
		return _Balance(root->_left) && _Balance(root->_right);
	}

protected:
	Node *_root;
};

void test()
{
	int arr[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	int arr1[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	AVLTree<int, int> t;
	for (int i = 0; i < sizeof(arr1) / sizeof(arr[0]); ++i)
	{
		t.Insert(arr1[i], i);
	}
	t.InOrder();
	cout << endl;
	cout<<"Balance?"<<t.Balance()<<endl;
}
