#include<iostream>
#include<stack>
using namespace std;

template <typename T>
struct BinaryTreeNode
{
          BinaryTreeNode<T >* _Left;
          BinaryTreeNode<T >* _Right;
          T _data;

          BinaryTreeNode( const T & x)
                   :_Left( NULL)
                   , _Right( NULL)
                   ,_data( x)
          {
          }
};

template <typename T>
class BinaryTree
{
          typedef BinaryTreeNode <T> Node;
public:
          BinaryTree()
                   :_root( NULL)
          {
          }
          BinaryTree( const T *a, size_t size, int invalid)
          {
                   int index = 0;
                   _root=_CreatBinaryTree( a, size ,invalid,index);
          }
          BinaryTree( const BinaryTree <T>& t)
          {
                   _root = _Copy( t._root);
          }

          BinaryTree& operator=(const BinaryTree< T>& t )
          {
                   if (this != &t)
                   {
                             _Destory(_root);
                             _root = _Copy( t._root);
                   }
                   return *this ;
          }

          ~BinaryTree()
          {
                   _Destory(_root);
                   _root = NULL;
          }

          void PreOrder()
          {
                    _PreOrder(_root);
                    cout << endl;
          }

          void InOrder()
          {
                    _InOrder(_root);
                    cout << endl;
          }

          void PostOrder()
          {
                    _PostOrder(_root);
                    cout << endl;
          }

          void LevelOrder()
          {
                   _LevelOrder(_root, level);
                   cout << endl;
          }

          void PreOrder_NonR()
          {
                   _PreOrder_NonR(_root);
                   cout << endl;
          }

          void InOrder_NonR()
          {
                   _InOrder_NonR(_root);
                   cout << endl;
          }

          void PostOrder_NonR()
          {
                   _PostOrder_NonR(_root);
                   cout << endl;
          }
          size_t Size()
          {
                   int size = 0;
                   _Size(_root,size);
                   return size;
          }

          size_t Depth()
          {
                   return _Depth(_root);
          }

          size_t LeafSize()
          {
                   return _LeafSize(_root);
          }

          size_t GetKLevel(int K)
          {
                   return _GetKLevel(_root, K );
          }
protected:
          Node* _root;

          Node* _CreatBinaryTree(const T* a, size_t size, const T& invalid, int& index )
          {
                   Node* root = NULL ;
                   if (index < size && a[index ] !=invalid)
                   {
                             root = new Node (a[index]);
                             root->_Left = _CreatBinaryTree( a, size , invalid, ++index);
                             root->_Right = _CreatBinaryTree( a, size , invalid, ++index);
                   }
                   return root;
          }

          Node* _Copy(Node * root)
          {
                   if (root == NULL)
                   {
                             return NULL ;
                   }
                   else
                   {
                             Node* newroot = new Node( root->_data);
                             newroot->_Left = _Copy( root->_Left);
                             newroot->_Right = _Copy( root->_Right);
                   }
                   return newroot;
          }

          void _Destory(Node * &root)
          {
                   if (root == NULL)
                   {
                             return;
                   }
                   if (root ->_Left == NULL&& root->_Right == NULL )
                   {
                             delete root ;
                             root = NULL ;
                             return;
                   }

                   _Destory( root->_Left);
                   _Destory( root->_Right);
                   delete root ;
          }

          void _PreOrder(Node * root)
          {
                   if (root == NULL)
                   {
                             return;
                   }
                   cout << root->_data << " " ;
                   _PreOrder( root->_Left);
                   _PreOrder( root->_Right);
                  
          }


          void _InOrder(Node * root)
          {
                   if (root == NULL)
                   {
                             return;
                   }
                   else
                   {
                             _InOrder( root->_Left);
                             cout << root->_data << " " ;
                             _InOrder( root->_Right);
                   }
          }
          void _PostOrder(Node * root)
          {
                   if (root == NULL)
                   {
                             return;
                   }
                   else
                   {
                             _PostOrder( root->_Left);
                             _PostOrder( root->_Right);
                             cout << root->_data << " " ;
                   }
          }
          void _LevelOrder(Node * root, int level )
          {
                   if (root == NULL)
                   {
                             return;
                   }
                   if (level == 1)
                   {
                             cout << root->_data << " " ;
                   }
                   else
                   {
                             _LevelOrder( root->_Left, level - 1);
                             _LevelOrder( root->_Right, level - 1);
                   }
          }

          void _PreOrder_NonR(Node * root)
          {
                   stack<Node *> s;
                   if (root != NULL)
                             s.push( root);
                   while (!s.empty())
                   {
                             Node* top = s.top();
                             s.pop();
                             cout << top->_data << " ";
                             if (top->_Right)
                             {
                                      s.push(top->_Right);
                             }
                             if (top->_Left)
                             {
                                      s.push(top->_Left);
                             }
                   }
          }

          void _InOrder_NonR(Node * root)
          {
                   stack<Node *> s;
                   Node* cur = root ;
                   while (cur || !s.empty())
                   {
                             while (cur)
                             {
                                      s.push(cur);
                                      cur = cur->_Left;
                             }
                             if (!s.empty())
                             {
                                      Node* top = s.top();
                                      cout << top->_data << " " ;
                                      s.pop();

                                      cur = top->_Right;
                             }
                   }
          }

          /*size_t _Size(Node* root)
          {
                   if (root == NULL)
                   {
                             return 0;
                   }
                   else
                   {
                             return _Size(root->_Left) + _Size(root->_Right) + 1;
                   }
          }*/
          size_t _Size(Node * root, int& size )//遍历
          {
                   if (root == NULL)
                   {
                             return 0;
                   }
                   size++;
                   _Size( root->_Left, size );
                   _Size( root->_Right, size );
          }

          size_t _Depth(Node * root)
          {
                   if (root == NULL)
                   {
                             return 0;
                   }
                   else
                   {
                             size_t left = _Depth(root ->_Left);
                             size_t right = _Depth(root ->_Right);
                             return left > right ? left + 1 : right + 1;
                   }
          }

          size_t _LeafSize(Node * root)
          {
                   if (root == NULL)
                   {
                             return 0;
                   }
                   if (root ->_Left == NULL && root->_Right == NULL )
                   {
                             return 1;
                   }
                   return _LeafSize(root ->_Left) + _LeafSize(root->_Right);
          }

          size_t _GetKLevel(Node * root, int K )
          {
                   if (root == NULL)
                   {
                             return 0;
                   }
                   if (root !=NULL && K==1)
                   {
                             return 1;
                   }
                             return _GetKLevel(root ->_Left, K-1)+ _GetKLevel(root->_Right, K -1);
          }
};
int main()
{
          int array[10] = { 1, 2, 3, '#' , '#', 4, '#', '#' , 5, 6 };
          BinaryTree<int > tree(array,10,'#');
          tree.PreOrder();
          tree.InOrder();
          tree.PostOrder();
          tree.PreOrder_NonR();
          tree.InOrder_NonR();
          cout<< "叶子节点：" <<tree.LeafSize()<<endl;
          cout << "Size: "<< tree.Size() << endl;
          cout << "Depth:" << tree.Depth() << endl;
          cout << "GetKLevel:" << tree.GetKLevel(2) << endl;
          getchar();
          return 0;
}
