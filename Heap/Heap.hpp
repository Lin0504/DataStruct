#include<iostream>
using namespace std;
#include<vector>
#include<assert.h>
template<typename T>
class Heap
{
public:
          Heap()
          {
          }

          Heap( const T* array , size_t size)
          {
                    for (int i = 0; i < size; i++)
                   {
                             _array.push_back( array[i]);
                   }

                    for (int i = (_array.size() - 2) / 2; i >= 0; --i)
                   {
                             AdjustDown(i);
                   }
          }

           void Push( const T& data)
          {
                   _array.push_back(data);
                   AdjustUp(_array.size() - 1);
          }

           void Pop()
          {
                   assert(_array.size() > 0);
                   swap(_array[0], _array[_array.size() - 1]);
                   _array.pop_back();
                   AdjustDown(0);
          }

           void AdjustDown(int parents)
          {
                    int child = parents * 2 + 1;
                    while (child <_array.size())
                   {
                              if (child+1<_array.size() && _array[child] < _array[child + 1])
                             {
                                      ++child;
                             }
                              if (_array[parents] < _array[child])
                             {
                                      swap(_array[parents], _array[child]);
                                      parents = child;
                                      child = parents * 2 + 1;
                             }
                              else
                             {
                                       break;
                             }
                   }
          }

           void AdjustUp(int child)
          {
                    int parents = (child - 1) / 2;
                    while (child >0)
                   {
                              if (_array[parents] < _array[child])
                             {
                                      swap(_array[parents], _array[child]);
                                      child = parents;
                                      parents = (child - 1) / 2;
                             }
                              else
                             {
                                       break;
                             }
                   }
          }

          T& GetTop()
          {
                   assert(_array.size());
                    return _array[0];
          }
           bool Empty()
          {
                    return _array.empty();
          }

          size_t Size()
          {
                    return _array.size();
          }

           void Print()
          {
                    for (int i = 0; i < _array.size(); i++)
                   {
                             cout << _array[i] << " ";
                   }
                   cout << endl;
          }
protected:
          vector<T> _array;
};
int main()
{
           int array [10] = { 10, 16, 18, 12, 11, 13, 15, 17, 14, 19 };
          Heap< int> a1(array , sizeof( array) / sizeof (array[0]));
          a1.Print();
          cout << endl;
          a1.Pop();
          a1.Print();
          cout << endl;
          a1.Push(20);
          a1.Print();
          getchar();
           return 0;
}
