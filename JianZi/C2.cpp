#include "moststd.h"
using namespace JZ;
//T1--P24
class CMyString1
{
	char*  data;
public:
	CMyString1& operator=(const CMyString1&rhs)
	{
		//���쳣��ȫ
		if (&rhs != this)
		{
			delete[]data;
			data = NULL;
			data = new char[strlen(rhs.data)+1];//��new�����쳣ʱ,��ʱdata�Ѿ��ǿ�ָ�룬ԭ��ָ������ݱ�ɾ������״̬�����˱仯���ʲ����쳣��ȫ��
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
			data = new char[strlen(rhs.data) + 1];//mallocʧ��ʱ����nullָ�루0��,��newʧ��ʱ����bad_alloc�쳣���ʴ�ʱdata��ֵ��û�иı䣬����ָ��֮ǰ�����ݣ���Ȼ�쳣��ʱ����������û��ִ�е�������ɲ�����malloc��mallocʧ�ܲ������쳣
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
		//������Լ�this!=&rhs�жϣ�Ҳ���Բ��ӣ�����Ը�ֵ���������ֵĻ����˷������ã�����һ���߼���֧����ˮ�߲���
		CMyString3 tmp(rhs);//����������쳣ʱ��data״̬���䣬�����쳣��ȫ
		char* tmpData = data;
		data = tmp.data;
		tmp.data = tmpData;
		return *this;//ԭ�����ݵ�ɾ���ͽ���tmp�����������ˣ��Ӷ������ڴ�й©
	}
};
//T2--Singleton
//http://www.cnblogs.com/ZhYQ-Note/articles/6089444.html
//���������ַ���Ψһ�������,instance()�ķ���������static T&������T�������õľ�̬��Ա�������������������ǲ���ÿ�ζ�����һ��T���͵�object��
//Singleton�ĳ�Ա���Ǿ�̬��Ա�����˹��캯������������������Ϊû������Singleton�������Բ����÷Ǿ�̬��Ա����Ϊ�Ǿ�̬��Ա��ʹ���ǻ��ھ������ģ�����̬��Ա��ʹ���Ǹ���������û�й�ϵ�ģ���ֻ��������й�ϵ�����Ե��õ�ʱ����Singleton<T>::instance()
template<class T>
class Singleton1
{
	//���߳��µ�
private:
	static T* value;//static data memberע�������������������û�ж��弰��ʼ������ľ�̬��Ա�����Ķ��弰��ʼ��Ҫ���������棨�ඨ���ͷ�ļ��У�
		Singleton1();
		~Singleton1();
public:
	static T& instance()
	{
		if (!value_)
		{
			//�ڶ��߳����ǲ���ȫ�ģ���Ϊ�����߳̿���ͬʱ������������Ļ��ͻ��������ʵ�����Ͳ��ǵ�����
			value_ = new T();
		}
		return *value_;
	}
};
template<class T>//��̬���ݳ�Ա��������Ĺ��캯�����涨������Ϊ��static���ݳ�ԱӦ����ȫ������ģ��������ڲ�������ĳ��������࣬������ڹ��캯�����涨��Ļ����Ǿ�Ҫ�ȵ�����������ɵ�ʱ��Ŷ�����
T* Singleton1<T>::value = NULL;//ע�ⲻ��ʡ��ǰ�涨�������T*���͸����ⶨ�庯������ʡ�Է�������һ����ֻ��������ˡ�Singleton1<T>::�������Ҳ���static

template<class T>
class Singleton2
{
	//���߳��°�ȫ����Ч�ʵͣ���Ϊÿ�μ��value�Ƿ�Ϊ�ն�Ҫ����
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
	//Double checked Lock,ֻ��c++11���Ժ�����ȷ��
	//���ַ����ܼ���ÿ�μ�鶼������ֻ��ʵ����û�����ɵ�ʱ�������
    //��singleton2��:1����->2�жϷǿ�,singleton3�ǣ�1�жϷǿ�->2����->3�жϷǿգ���Singleton3ֻ��Singleton2����һ�䡰if(!value_)��������ȫһ��
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
				//��c++11�У���һ����ԭ���Ե�
				value_ = new T();//��c++11��ǰ�Ļ�����һ�䲻��ԭ���Եģ�����ִ�иþ��ʱ�����߳��л����п���value_�������˹����ڴ��ֵַ�����ڸõ�ַ����û�й���T��������ô����һ���߳̿��ܾͻ�ֱ���û�û����õĵ�ֵַ������
			}
		}
		return *value_;
	}
};
template<class T>
T* Singleton3<T>::value_ = NULL;
template<class T>//���ﻹ��Ҫ��template<class T>����Ϊ�����template<class T>�ܲ���mtx_����Ķ����ˣ���ֻ�ܵ�һ��
mutex Singleton3<T>::mtx_;

template<class T>
class Singleton4
{
    //by Scott Meyer
	//��Singleton3һ����ֻ��c++11���Ժ���Ч�������֮�¼��ö�
private:
	Singleton4();
    ~Singleton4();
public:
	static T& instance()
	{
		//If control enters the declaration concurrently while the variable is being initialized, 
		//the concurrent execution shall wait for completion of the initialization.
		static T value = new T();//c++11���Ժ���һ����ԭ���Ե�,static����ֻ����ʼ��һ�Σ���һ��Ҳִֻ��һ�Σ�Ҳ����˵��һ��ȱ�֤���̰߳�ȫ���ֱ�֤�˵���ֻ����һ��
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
			n=n >> 1;//ע��ǧ����д��n>>1
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
