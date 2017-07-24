#include "moststd.h"
using namespace JZ;
int maxSubArray(vector<int>& nums) {
	if (nums.size() == 1)
		return nums[0];
	int res = nums[0];
	int pre = nums[0];
	int cur;
	for (int i = 1; i < nums.size(); ++i)
	{
		if (pre < 0)
			cur = nums[i];
		else
			cur = pre + nums[i];
		pre = cur;
		res = max(cur, res);	
	}
	return res;
}
//p176 -T32

int NumberOf1Between1AndN_Solution(int n)
{
	if (n <= 0)
		return 0;
	string s = to_string(n);
	int sz = s.size();
	if (sz == 1)
		return 1;
	int first = s[0]-'0';
	int numFirstDigits, numOtherDigits, numRecursiveDigits;
	if (first > 1)
	{
		numFirstDigits = pow(10, sz - 1);
	}
	else
	{
		numFirstDigits = stoi(s.substr(1)) + 1;
	}
	numOtherDigits = first*(sz - 1)*pow(10, sz - 2);
	numRecursiveDigits = NumberOf1Between1AndN_Solution(stoi(s.substr(1)));
	return numFirstDigits + numOtherDigits + numRecursiveDigits;
}
//P177 -T33

class PrintMinNumberSolution {
	struct MyComp
	{
		bool operator()(int v1,int v2)const
		{
			string s1 = to_string(v1) + to_string(v2);
			string s2 = to_string(v2) + to_string(v1);
			return s1 < s2;
		}
	};
public:
	string PrintMinNumber(vector<int> numbers) {
		sort(numbers.begin(),numbers.end(),MyComp());
		string res = "";
		for (int number : numbers)
		{
			res += to_string(number);
		}
		return res;
	}
};
//P182--T34  Leetcode--T263,264
class UglyNumber
{
public:
	bool isUgly(int num) {
		if (num == 1)
			return 1;
		while (num % 2 == 0)
			num = num / 2;
		while (num % 3 == 0)
			num = num / 3;
		while (num % 5 == 0)
			num = num / 5;
		return num == 1;
	}
	int nthUglyNumber(int n) {
		vector<int>arr;
		arr.reserve(n);
		arr.push_back(1);
		int t2 = 0, t3 = 0, t5 = 0;
		int val;
		while (arr.size() != n)
		{
			val = min(min(arr[t2]*2,arr[t3]*3),arr[t5]*5);
			if (val == arr[t2] * 2)
			{
				++t2;
			}
			if (val == arr[t3] * 3)
			{
				++t3;
			}
			if (val==arr[t5]*5)
			{
				++t5;
			}
			arr.push_back(val);
		}
		return arr.back();
	}
};
//P186  /Leetcode-T387 First Unique Character in a String
class FirstUniqueChar
{
public:
	int firstUniqChar(string s) {
		if (s.empty())
			return -1;
		unordered_map<char, int>mp;
		for (auto ch : s)
		{
			++mp[ch];
		}
		for (int i = 0; i < s.size(); ++i)
		{
			if (mp[s[i]] == 1)
				return i;
		}
		return -1;
	}
};
//leetcode https://leetcode.com/problems/reverse-pairs/#/description --T493
class ReversePairs_TLE
{
	//乘以2一定要注意溢出啊
	struct BSTreeNode
	{
		int val;
		int same;
		int leftSize;
		BSTreeNode* left;
		BSTreeNode*right;
		BSTreeNode*parent;
		BSTreeNode(int v) :val(v), same(1), leftSize(0), left(NULL), right(NULL), parent(NULL){}
	};
	int insert(BSTreeNode*root, int val)
	{
		assert(root != NULL);
		BSTreeNode* p = root, *pp = p->parent;
		//返回满足当前树中节点的val值的2倍小于val的所有节点的数目
		int res = 0;
		int hmax = INT_MAX / 2;
		int hmin = INT_MIN / 2;
		while (p)
		{
			if (p->val > hmax || p->val < hmin)
			{
				if (p->val > hmax)
				{
					p = p->left;
				}
				else
				{
					res += (p->leftSize + p->same);
					p = p->right;
				}
			}
			else
			{
				if (val < 2 * (p->val))
					p = p->left;
				else if (val > 2 * (p->val))
				{
					res += (p->leftSize + p->same);
					p = p->right;
				}
				else
				{
					res += p->leftSize;
					break;
				}
			}
		}
		//insert the node,update the tree
		p = root, pp = p->parent;
		while (p)
		{
			pp = p;
			if (val < p->val)
			{
				++(p->leftSize);
				p = p->left;
			}
			else if (val > p->val)
			{
				p = p->right;
			}
			else
			{
				++(p->same);
				break;
			}
		}
		if (!p)
		{
			BSTreeNode* node = new BSTreeNode(val);
			node->parent = pp;
			if (val < pp->val)
			{
				pp->left = node;
			}
			else
			{
				pp->right = node;
			}
		}

		return res;
	}
public:
	int reversePairs(vector<int>& nums) {
		if (nums.empty())
			return 0;
		BSTreeNode* root = new BSTreeNode(nums.back());
		int res = 0;
		int sz = nums.size();
		for (int i = sz - 2; i >= 0; --i)
		{
			res += insert(root, nums[i]);
		}
		return res;
	}
};
class ReversePairs
{
	int countAndSort(vector<int>::iterator start, vector<int>::iterator end)
	{
		if (end-start<=1)
			return 0;
		auto mid = start + (end - start) / 2;
		int res = countAndSort(start, mid) + countAndSort(mid,end);
		for (auto i = start, j = mid; i != mid; ++i)
		{
			while (j!=end&&*i > 2L * *j)
				++j;
			res += (j-mid);
		}
		inplace_merge(start,mid,end);
		return res;
	}
public:
	int reversePairs(vector<int>& nums) {
		return countAndSort(nums.begin(), nums.end());
	}
  
};

