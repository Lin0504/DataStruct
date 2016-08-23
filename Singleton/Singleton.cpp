#include<iostream>
#include<assert.h>
#include<mutex>


using namespace std;
//懒汉模式：第一次调用GetInstance，创建对象
class Singleton
{
public:
	//将获取对象的函数设为static ,不用通过对象调用获取唯一实例的函数
	static Singleton* GetInstance()
	{
		if (Instance == NULL)
		{
			Instance = new Singleton();
		}
		return Instance;
	}
	//删除唯一实例
	static void DelSingleton()
	{
		if (Instance)
		{
			delete Instance;
			Instance = NULL;
		}
	}
	void Print()
	{
		cout << _a << endl;
	}
private:
	//将构造函数，拷贝构造函数，赋值运算符函数设为私有，限制只能在类内创建对象
	Singleton()
		:_a(0)
	{}
	Singleton(const Singleton&);
		Singleton& operator=(const Singleton&);
	int _a;
	//指向实例的指针定义为静态私有，定义静态成员函数获取实例
	static Singleton *Instance;
};
//优化1：考虑线程安全问题
class Singleton1
{
public:
	//static Singleton1* GetInstance()
	//{
	//	mutex mtx;//此处加锁有问题，mtx是一个局部变量，两个线程加的不是同一把锁
	//	mtx.lock();
	//	if (_Instance == NULL)
	//	{
	//	
	//		_Instance = new Singleton1();
	//	}
	//	mtx.unlock();
	//	return _Instance;
	//}
	static Singleton1*GetInstance()
	{
		if (_Instance == NULL)//加双重判断提高效率，避免高并发场景下每次获取实例都进行加锁
		{
			lock_guard<mutex> lck(_mtx);//出了作用域会调用析构函数自动解锁
			if (_Instance == NULL)
			{
				//_Instance = new Singleton1();//此处会有编译器将指令重排的可能，在高并发场景下，获取未初始化的实例
				//1.分配空间 2.调用构造函数 3.赋值
				//编译器编译优化可能会将指令重排，将3放到2 的前面去,在高并发场景下，其他线程获取到未调用构造函数初始化的实例
				//进一步优化
				Singleton1 *tmp = new Singleton1();
				//MemoryBarrier();//加内存栅栏，防止编译器重拍后的赋值放在栅栏之前，确保_Instance获得的是完整初始化的实例；
				_Instance = tmp;
			}
		}
		return _Instance;
	}

	static void DelSingleton()
	{
		lock_guard<mutex> lck(_mtx);
		if (_Instance)
		{
			delete _Instance;
			_Instance = NULL;
		}
	}

	void Print()
	{
		cout << _a << endl;
	}
private:
	int _a;
	static Singleton1* _Instance;
	static mutex _mtx;
	Singleton1()
		:_a(0)
	{}
	Singleton1(const Singleton1&);
	Singleton1& operator=(const Singleton1&);
};
Singleton1* Singleton1::_Instance = NULL;
mutex Singleton1::_mtx;


//饿汉模式：调用获取实例函数之前，实例对象已经创建好
//方式一
class Singleton2
{
public:
	static Singleton2* GetInstance()
	{
		assert(_Instance);
		return _Instance;
	}

private:
	int _a;
	Singleton2()
		:_a(0)
	{}
	Singleton2(const Singleton2&);
	Singleton2& operator=(const Singleton2&);
	static Singleton2* _Instance;
};
//静态对象是在main函数之前初始化的，所以是线程安全的
Singleton2* Singleton2::_Instance = new Singleton2;

//方式二
class Singleton22
{
public:
	Singleton22* GetInstance()
	{
		static Singleton22 _Instance;
		return &_Instance;
	}
private:
	int _a;
	Singleton22()
		:_a(0)
	{}

	Singleton22(const Singleton22&);
	Singleton22& operator=(const Singleton22&);
};
void test1()
{
	Singleton1::GetInstance();
	Singleton1::GetInstance()->Print();
}
void test2()
{
	Singleton2::GetInstance();
}
int main()
{
	test1();
	getchar();
	return 0;
}
