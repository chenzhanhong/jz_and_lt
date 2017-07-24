#include "moststd.h"
using namespace JZ;
//p90-T11
class Power
{
	//不用考虑大数
	bool doubleEqual(double a, double b)
	{
		return abs(a - b) < 0.000001;
	}
	double powerWithUintExponent(double base, uint32_t expo)
	{
		if (expo == 0)
			return 1;
		if (expo == 1)
			return base;
		double h = powerWithUintExponent(base,expo>>1);
		double res = h*h;
		if ((expo & 0x1) == 1)
			res *= base;
		return res;
	}
public:
	double power(double base, int expo)
	{
		if (doubleEqual(base, 0.0) && expo <= 0)
			throw runtime_error("Invalid input");
		double res = powerWithUintExponent(base,abs(expo));
		return expo >= 0 ? res : 1 / res;
	}
};
//P94--T12
class Print1ToMaxOfNDigits
{
	//leetcode--T415
	string addStrings(string num1, string num2) {
		string&a = (num1.size() >= num2.size() ? num1 : num2);
		string&b = (num1.size() >= num2.size() ? num2 : num1);
		stack<char>chs;
		int carry = 0;
		int aa, bb, cur;
		for (int i = a.size() - 1, j = b.size() - 1; i >= 0; --i, --j)
		{
			aa = a[i] - 48;
			bb = (j >= 0 ? b[j] - 48 : 0);
			cur = aa + bb + carry;
			carry = cur / 10;
			cur = cur % 10;
			chs.push(cur + 48);
		}
		if (carry)
			chs.push('1');
		string res = "";
		while (!chs.empty())
		{
			res += chs.top();
			chs.pop();
		}
		return res;
	}
	bool increment(vector<char>&chs)
	{
		int i = chs.size()-1;
		int carry = 1;
		int aa,cur;
		while (1)
		{
			aa = chs[i]-48;
			cur = aa + carry;
			carry = cur / 10;
			cur = cur % 10;
			chs[i] = cur + 48;
			if (carry)
			{
				if (i == 0)
					return true;
				--i;
			}
			else
			{
				break;
			}
		}
		return false;
	}
	void printNumber(const vector<char>&chs)
	{
		//chs should not be all '0'
		bool flag = false;
		for (int i = 0; i < chs.size(); ++i)
		{
			if (!flag&&chs[i] != '0')
				flag = true;
			if (flag)
			{
				cout << chs[i];
			}
		}
		if (!flag)
			cout << 0;
		cout << " ";
	}
public:
	void print1ToMaxOfNDigits(int n)
	{
		if (n <= 0)
			throw runtime_error("invalid input");
		vector<char>chs(n,'0');
		do
		{
			printNumber(chs);
		} while (!increment(chs));
		cout << endl;
	}
};
//P102--T14
//参考左一书P382数组partition及quicksort里面的partition，这些例子都是把数组根据某项规则调整为前后两部分（调整为3部分的时候可以在2两部分的基础上做）
class ReorderOddEven
{
public:
	void reorderOddEven(vector<int>&arr)
	{
		if (arr.size() <= 1)
			return;
		int u = -1;
		for (int j = 0; j <= arr.size() - 1; ++j)
		{
			if (arr[j] % 2)
				swap(arr[++u],arr[j]);
		}
	}
	//考虑可扩展性,用仿函数
	typedef function<bool(int)> PartitionCB;
	void Partition(vector<int>&arr,const PartitionCB& cb)
	{
		if (arr.size() <= 1)
			return;
		int i = -1;
		for (int j = 0; j <= arr.size() - 1; ++j)
			if (cb(arr[j]))
				swap(arr[++i],arr[j]);
	}
};
//P110--T15
class KthNodeFromEnd
{
public:
	listNode* findKthToTail(listNode*head, uint32_t k)
	{
		if (!head || k == 0)
			return NULL;
		listNode* p1 = head;
		int i = 0;
		for (; i < k - 1&&p1; ++i)
		{
			p1 = p1->next;
		}
		if (!p1)
			return NULL;
		listNode*p2 = head;
		while (p1->next)
		{
			p2 = p2->next;
			p1 = p1->next;
		}
		return p2;
	}
};
//P114-T17
class MergeSortedLists
{
public:
	listNode* merge0(listNode*head1, listNode*head2)
	{
		if (!head1)
			return head2;
		if (!head2)
			return head1;
		listNode* nbig = (head1->val > head2->val ? head1 : head2);
		listNode* nsmall = (head1->val>head2->val?  head2:head1);
		listNode*resHead = new listNode(nsmall->val);
		nsmall = nsmall->next;
		//nbig = (!nsmall || nbig->val > nsmall->val ? nbig : nsmall);
		//nsmall = (!nsmall || nbig->val > nsmall->val ? nsmall : nbig);//这是错误的，因为nbig已经发生了变化！！！
		if (nsmall && nbig->val <= nsmall->val)
		{
			swap(nbig,nsmall);
		}
		listNode*cur = resHead;
		while (nsmall)
		{
			cur->next = new listNode(nsmall->val);
			nsmall = nsmall->next;
			if (nsmall && nbig->val <= nsmall->val)
			{
				swap(nbig, nsmall);
			}
			cur = cur->next;//千万别忘了cur的推进啊！！！
		}
		cur->next = nbig;
		return resHead;
	}
	listNode* merge(listNode*head1, listNode*head2)
	{
		//这里用递归的方法，并且实现真正的合并，不需要申请新的空间来存放节点
		if (!head1)
			return head2;
		if (!head2)
			return head1;
		listNode* res;
		if (head1->val < head2->val)
		{
			res = head1;
			res->next = merge(head1->next,head2);
		}
		else
		{
			res = head2;
			res->next = merge(head1,head2->next);
		}
		return res;
	}
};
//p117-T18
class SubstructrueInTree
{
private:
	bool doesTree1HasTree2FromHeadOfTree1(treeNode*t1, treeNode*t2)
	{
		if (!t2)
			return true;
		if (!t1 || t1->val != t2->val)
			return false;
		return doesTree1HasTree2FromHeadOfTree1(t1->left, t2->left) && doesTree1HasTree2FromHeadOfTree1(t1->right, t2->right);
	}
public:
	bool hasSubstructrue(treeNode*t1, treeNode*t2)
	{
		if (!t1)
			return t2 == NULL;
		return doesTree1HasTree2FromHeadOfTree1(t1, t2) || hasSubstructrue(t1->left, t2) || hasSubstructrue(t1->right, t2);
	}
};
/*
void main()
{
	try
	{
		
		vector<int>arr = {1,2,3,5,6,7,4};
		ReorderOddEven::PartitionCB oddEvenCB = [](int num)->bool{return num % 2; };
		ReorderOddEven::PartitionCB smallBigCB = [&arr](int num)->bool{return num <= arr.back(); };
		ReorderOddEven().Partition(arr, oddEvenCB);
		ReorderOddEven().Partition(arr,smallBigCB);
		
		vector<int>arr1 = {15};
		vector<int>arr2 = {2,4,6,8,9,11,13};
		listNode* head1 = genList(arr1), *head2 = genList(arr2);
		listNode* head = MergeSortedLists().merge(head1,head2);
		printList(head);
		int itrpt = 0;
		
	}
	catch (const runtime_error& e)
	{
		cout << "runtime error caught:" << e.what() << endl;
	}
}
*/