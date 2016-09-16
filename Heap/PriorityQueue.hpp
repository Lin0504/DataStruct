#include<iostream>
using namespace std;
#include<vector>
#include<assert.h>

template<typename T>
struct Less
{
           bool operator() (const T& Left,const T& Right)
          {
                    return Left < Right;
          }
};

template<typename T>
struct More
{
           bool operator()(const T& Left, const T& Right)
          {
                    return Left > Right;
          }
};

template<typename T,class Compare>
class Heap
{
public:
          Heap()
          {}
          Heap( const T *a, size_t size)
          {
                    for (int i = 0; i < size; ++i)
                   {
                             _a.push_back( a[i]);
                   }

                    for (int i = (_a.size() - 2) / 2; i >= 0; --i)
                   {
                             AdjustDown(i);
                   }
          }

           void Push(const T& data)
          {
                   _a.push_back( data);
                   AdjustUp(_a.size() - 1);
          }

           void Pop()
          {
                    assert(!_a.empty());
                   swap(_a[0], _a[_a.size() - 1]);
                   _a.pop_back();
                   AdjustDown(0);
          }
           void Print()
          {
                    for (int i = 0; i < _a.size(); i++)
                   {
                             cout << _a[i] << " ";
                   }
                   cout << endl;
          }
protected:
           void AdjustDown(int parent)
          {
                    Compare com;
                    int child = parent * 2 + 1;
                    while (child < _a.size())
                   {
                              if (child + 1 < _a.size() && com(_a[child], _a[child + 1]))
                             {
                                      ++child;
                             }
                              if (com(_a[parent ], _a[child]))
                             {
                                      swap(_a[ parent], _a[child]);
                                       parent = child;
                                      child = parent * 2 + 1;
                             }
                              else
                             {
                                       break;
                             }
                   }
          }

           void AdjustUp(int child)
          {
                    int parent = (child - 1) / 2;
                    Compare com;
                    while (child > 0)
                   {
                              if (child + 1 < _a.size() && com(_a[child], _a[ child + 1]))
                             {
                                      ++ child;
                             }

                              if (com(_a[parent], _a[child ]))
                             {
                                      swap(_a[parent], _a[ child]);
                                       child = parent;
                                      parent = ( child - 1) / 2;
                             }
                              else
                             {
                                       break;
                             }
                   }
          }
protected:
           vector<T > _a;
};

template<typename T>
class  PriorityQueue
{
public:
           void Push(const T& data)
          {
                   _hp.Push( data);
          }

           void Pop()
          {
                   _hp.Pop();
          }
protected:
          Heap< T> _hp;
};
int main()
{
           int a[10] = { 10, 11, 13, 12, 16, 18, 15, 17, 14, 19 };
           Heap<int , Less< int>> heap(a, sizeof (a) / sizeof(a[0]));
          heap.Push(1);
          heap.Print();
          heap.Pop();
          heap.Print();
          cout << endl;

           Heap<int , More< int>>heap1(a, sizeof (a) / sizeof(a[0]));
          heap1.Push(1);
          heap1.Print();
          heap1.Pop();
          heap1.Print();
          getchar();
           return 0;
}
