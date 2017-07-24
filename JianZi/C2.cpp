#include "moststd.h"
using namespace JZ;
//T1--P24
class CMyString1
{
	char*  data;
public:
	CMyString1& operator=(const CMyString1&rhs)
	{
		//非异常安全
		if (&rhs != this)
		{
			delete[]data;
			data = NULL;
			data = new char[strlen(rhs.data)+1];//当new返回异常时,此时data已经是空指针，原来指向的内容被删除，即状态发生了变化，故不是异常安全的
			strcpy_s(data, strlen(rhs.data) + 1, rhs.data);
		}
		return *this;
	}
};

class CMyString2
{
	//"effective c++"  P55 Item11
	char*  data;
public:
	CMyString2& operator=(const CMyString2&rhs)
	{
		if (&rhs != this)
		{
			char* oriData = data;
			data = new char[strlen(rhs.data) + 1];//malloc失败时返回null指针（0）,但new失败时引起bad_alloc异常，故此时data的值并没有改变，还是指向之前的内容，当然异常的时候后面的语句就没有执行到。这里可不能用malloc，malloc失败不返回异常
			strcpy_s(data, strlen(rhs.data) + 1, rhs.data);
			delete[]oriData;
		}	
		return *this;
	}
};
class CMyString3
{
    //copy-swap
	char*  data;
public:
	CMyString3& operator=(const CMyString3&rhs)
	{
		//这里可以加this!=&rhs判断，也可以不加，如果自赋值不经常出现的话加了反而不好，多了一个逻辑分支对流水线不利
		CMyString3 tmp(rhs);//当这里出现异常时，data状态不变，符合异常安全
		char* tmpData = data;
		data = tmp.data;
		tmp.data = tmpData;
		return *this;//原来内容的删除就交给tmp的析构函数了，从而避免内存泄漏
	}
};
//T2--Singleton
//http://www.cnblogs.com/ZhYQ-Note/articles/6089444.html
//不管用那种方法唯一不变的是,instance()的返回类型是static T&（返回T类型引用的静态成员函数，返回引用是我们不用每次都复制一个T类型的object）
//Singleton的成员都是静态成员（除了构造函数和析构函数），因为没有生成Singleton对象，所以不能用非静态成员，因为非静态成员的使用是基于具体对象的，而静态成员的使用是跟类具体对象没有关系的，而只跟这个类有关系，所以调用的时候是Singleton<T>::instance()
template<class T>
class Singleton1
{
	//单线程下的
private:
	static T* value;//static data member注意这里仅仅是声明，并没有定义及初始化，类的静态成员变量的定义及初始化要放在类外面（类定义的头文件中）
		Singleton1();
		~Singleton1();
public:
	static T& instance()
	{
		if (!value_)
		{
			//在多线程下是不安全的，因为两个线程可能同时到达这里，这样的话就会产生两个实例，就不是单例了
			value_ = new T();
		}
		return *value_;
	}
};
template<class T>//静态数据成员不放在类的构造函数里面定义是因为，static数据成员应该是全局语意的，其生命期不依赖于某个具体的类，如果放在构造函数里面定义的话，那就要等到具体的类生成的时候才定义了
T* Singleton1<T>::value = NULL;//注意不能省略前面定义的类型T*，就跟类外定义函数不能省略返回类型一样，只是这里多了“Singleton1<T>::”，而且不用static

template<class T>
class Singleton2
{
	//多线程下安全，但效率低，因为每次检查value是否为空都要加锁
private:
	static mutex mtx_;
	static T* value_;
	Singleton2();
	~Singleton2();
public:
	static T& instance()
	{
		{
			lock_guard<mutex>guard(mtx_);//RAII
			if (!value_)
			{
				value_ = new T();
			}
		}
		return *value_;
	}
};
template<class T>
T* Singleton2<T>::value_ = NULL;
template<class T>
mutex Singleton2<T>::mtx_;

template<class T>
class Singleton3
{
	//Double checked Lock,只在c++11及以后是正确的
	//这种方法能减少每次检查都上锁，只在实例还没有生成的时候才上锁
    //（singleton2是:1加锁->2判断非空,singleton3是：1判断非空->2加锁->3判断非空），Singleton3只比Singleton2多了一句“if(!value_)”其他完全一样
private:
	static mutex mtx_;
	static T* value_;
	Singleton3();
	~Singleton3();
public:
	static T& instance()
	{
		if (!value_)
		{
			lock_guard<mutex>guard(mtx_);
			if (!value_)
			{
				//在c++11中，下一步是原子性的
				value_ = new T();//在c++11以前的话，这一句不是原子性的，若在执行该句的时候发生线程切换，有可能value_被赋予了构造内存地址值，但在该地址处还没有构造T出来，那么另外一个线程可能就会直接拿还没构造好的地址值来用了
			}
		}
		return *value_;
	}
};
template<class T>
T* Singleton3<T>::value_ = NULL;
template<class T>//这里还得要有template<class T>，因为上面的template<class T>管不了mtx_这里的定义了，它只管到一句
mutex Singleton3<T>::mtx_;

template<class T>
class Singleton4
{
    //by Scott Meyer
	//跟Singleton3一样，只对c++11及以后有效，但相比之下简洁得多
private:
	Singleton4();
    ~Singleton4();
public:
	static T& instance()
	{
		//If control enters the declaration concurrently while the variable is being initialized, 
		//the concurrent execution shall wait for completion of the initialization.
		static T value = new T();//c++11及以后，这一句是原子性的,static变量只被初始化一次，这一句也只执行一次！也就是说这一句既保证了线程安全性又保证了单例只生成一个
		return value;
	}
};
int getSize(int data[])
{
	return sizeof(data);
}
//P47
void replaceBlank(char str[], int maxCapacity)
{
	int numOfBlank = 0;
	for (int i = 0; str[i]!='\0'; ++i)
	{
		if (isblank(str[i]))
			++numOfBlank;
	}
	assert(maxCapacity>=strlen(str)+2*numOfBlank+1);
	int i = strlen(str), j = strlen(str) + 2 * numOfBlank;
	for (; i >= 0; --i)
	{
		if (!isblank(str[i]))
		{
			str[j--] = str[i];
		}
		else
		{
			str[j--] = '0';
			str[j--] = '2';
			str[j--] = '%';
		}
	}
}
//P59 --T7
class MyQueue {
	stack<int>stkPush;
	stack<int>stkPop;
public:
	/** Initialize your data structure here. */
	MyQueue() {

	}

	/** Push element x to the back of queue. */
	void push(int x) {
		stkPush.push(x);
	}

	/** Removes the element from in front of queue and returns that element. */
	int pop() {
		if (stkPop.empty() && stkPush.empty())
			throw runtime_error("Pop on an empty queue");
		if (stkPop.empty())
		{
			while (!stkPush.empty())
			{
				int t = stkPush.top();
				stkPush.pop();
				stkPop.push(t);
			}
		}
		int res = stkPop.top();
		stkPop.pop();
		return res;
	}

	/** Get the front element. */
	int peek() {
		if (stkPop.empty() && stkPush.empty())
			throw runtime_error("Peek on an empty queue");
		if (stkPop.empty())
		{
			while (!stkPush.empty())
			{
				int t = stkPush.top();
				stkPush.pop();
				stkPop.push(t);
			}
		}
		return stkPop.top();
	}

	/** Returns whether the queue is empty. */
	bool empty() {
		return stkPop.empty() && stkPush.empty();
	}
};
//P64
class QuickSort
{
	int partition(vector<int>&arr,int left,int right)
	{
		int val = arr[right];
		int i = left - 1;
		for (int j = left; j <= right; ++j)
		{
			if (arr[j] <= val)swap(arr[++i], arr[j]);
		}
		return i;
	}
public:
	void quickSort(vector<int>&arr,int left,int right)
	{
		if (right - left + 1 <= 1)
			return;
		int pivot = partition(arr,left,right);
		quickSort(arr,left,pivot-1);
		quickSort(arr,pivot+1,right);
	}
};
//P66-T8
class MinNumberInRotatedArray
{
public:
	int getMin(const vector<int>&arr)
	{
		assert(!arr.empty());
		int left = 0, right = arr.size() - 1;
		int mid = (left+right) / 2;
		if (arr[left] < arr[right])
			return arr[left];
		if (arr[left] == arr[right] && arr[left] == arr[mid])
			return *(min_element(arr.begin(),arr.end()));
		while (right - left>1)
		{
			mid = (left + right) / 2;
			int val = arr[mid];
			if (val >= arr[left])
			{
				left = mid;
			}
			else if (val <= arr[right])
			{
				right = mid;
			}
		}
		return arr[right];
	}
};
//T10--P78
class NumberOf1
{
public:
	int hammingWeight(uint32_t n) {
		//leetcode T191--Number of 1 bits
		int res = 0;
		for (int i = 0; i < 32; ++i)
		{
			res += (n&1);
			n=n >> 1;//注意千万不能写成n>>1
		}
		return res;
	}
	int numberOf1(int n)
	{
		int res = 0;
		while (n != 0)
		{
			n &= (n - 1);
			++res;
		}
		return res;
	}
};
