#include "moststd.h"
using namespace JZ;
//T--38
class GetNumberOfK_Solution
{
	int getFirstK(vector<int>&data, int k)
	{
		if (data.empty())
			return -1;
		
		int b = 0, e = data.size() - 1, m;
		while (e > b)
		{
			m = (e + b) / 2;
			if (data[m] > k)
				e = m - 1;
			else if (data[m] < k)
				b = m + 1;
			else
			{//data[m]==k
				if (m == b || (m - 1 >= b&&data[m - 1] != k))
					return m;
				else
				{
					e = m - 1;
				}
			}
		}
		return data[e] == k ? e : -1;
	}
	int getLastK(vector<int>&data, int k)
	{
		if (data.empty())
			return -1;
		int b = 0, e = data.size() - 1, m;
		while (e > b)
		{
			m = (e + b) / 2;
			if (data[m] > k)
				e = m - 1;
			else if (data[m] < k)
				b = m + 1;
			else
			{//data[m]==k
				if (m == e || (m + 1 <= e&&data[m + 1] != k))
					return m;
				else
					b = m + 1;
			}
		}

		return data[e] == k ? e : -1;
	}
public:
	int GetNumberOfK(vector<int> data, int k) {
		int res = 0;
		int f = getFirstK(data,k);
		int l = getLastK(data,k);
		if (f>-1 && l > -1)
			res = l - f+1;
		return res;
	}
};
//zuo P328, JZ P211
void FindNumsAppearOnce(vector<int> data, int* num1, int *num2) {
	int e0 = 0;
	for (int d : data)
		e0 ^= d;
	int rightOne = (e0&(~e0+1));
	int e00 = 0;
	for (int d : data)
	{
		if ((rightOne&d) != 0)//位运算符优先级很低的，比！=还要低，所以这里不能是rightOne&d！=0
			e00 ^= d;
	}
	*num1 = e00;
	*num2 = e00^e0;
}
//JZ P214 问题1
vector<int> FindNumbersWithSum(vector<int> array, int sum) {
	vector<int>res;
	int head = 0, tail = array.size() - 1;
	while (tail > head)
	{
		int a = array[head], b = array[tail];
		if (a + b == sum)
		{
			res = {a,b};
			break;
		}
		else if (a + b < sum)
		{
			++head;
		}
		else
		{
			--tail;
		}
	}
	return res;
}
//P216 问题二
vector<vector<int> > FindContinuousSequence(int sum) {
	vector<vector<int>>res;
	if (sum < 3)
		return res;
	int small = 1, big = 2;
	int cursum = 3;
	while (big < sum&&small <= sum / 2&&small<big)
	{
		if (cursum == sum)
		{
			vector<int>r;
			for (int i = small; i <= big; ++i)
				r.push_back(i);
			res.push_back(r);
			cursum -= small;
			++small;
		}
		else if (cursum < sum)
		{
			++big;
			cursum += big;
		}
		else
		{
			cursum -= small;
			++small;
		}
	}
	return res;
}
//leetcode -560. Subarray Sum Equals K
int subarraySum(vector<int>& nums, int k) {
	if (nums.empty())return 0;
	int res = 0;
	unordered_multimap<int, int>mp;
	mp.insert(make_pair(0,-1));
	int sum = 0;
	for (int i = 0; i < nums.size(); ++i)
	{
		sum += nums[i];
		res += mp.count(sum-k);
		mp.insert(make_pair(sum,i));
	}
	return res;
}
//JZ-P226
bool IsContinuous(vector<int> numbers) {
	if (numbers.empty())
		return false;
	sort(numbers.begin(), numbers.end());
	int numOfZeros = 0;
	for (int number : numbers)
		if (number == 0)
			++numOfZeros;
	int i = numOfZeros;
	int lack = 0;
	int sz = numbers.size();
	for (; i < sz - 1; ++i)
	{
		if (numbers[i + 1] == numbers[i])
			return false;
		lack += (numbers[i + 1] - numbers[i] - 1);
	}
	return numOfZeros >= lack;
}
//JZ--P228 T45
int LastRemaining_Solution(int n, int m)
{
	list<int>lst;
	for (int i = 0; i < n; ++i)
		lst.push_back(i);
	list<int>::iterator cur = lst.begin();
	while (lst.size() != 1)
	{
		int cnt = 0;
		while (cnt != m - 1)
		{
			++cur;
			if (cur == lst.end())
				cur = lst.begin();
			++cnt;
		}
		lst.erase(cur++);
		if (cur == lst.end())
			cur = lst.begin();
	}
	return lst.front();
}
//P232 -T46
//1+2+..+n
class Sumtemp
{
	static int N;
	static int Sum;
public:
	Sumtemp(){ ++N; Sum += N; }
	static void reset(){ N = 0; Sum = 0; }
	static int getSum(){ return Sum; }
};
int Sumtemp::N = 0;
int Sumtemp::Sum = 0;
int Sum_Solution(int n) {
	Sumtemp::reset();//不能省了！！！！！
	vector<Sumtemp>temps(n);
	return Sumtemp::getSum();
}
class Print1ToN
{
	static int n;
public:
	Print1ToN(){ ++n; cout << n << endl; }
	static void reset(){ n = 0; }
};
int Print1ToN::n = 0;
void print1ToN(int n)
{
	Print1ToN::reset();
	vector<Print1ToN>temps(n);
}
//JZ P238
class Solution_Add {
public:
	int Add(int num1, int num2)
	{
		int sum, carry;
		do{
			sum = (num1^num2);
			carry = ((num1&num2)<<1);
			num1 = sum;
			num2 = carry;
		} while (num2 != 0);
		return num1;
	}
};
