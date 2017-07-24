#include "moststd.h"
using namespace JZ;

class Solution_hasCycle {
	
public:
	bool hasCycle(ListNode *head) {
		if (!head)return false;
		ListNode* slow = head, *fast = head->next;
		while (fast&&fast->next&&fast != slow)
		{
			fast = fast->next->next;
			slow = slow->next;
		}
		if (fast == slow&&fast != NULL)
			return true;
		return false;
	}
};
class Solution_NthFromEnd {
	
public:
	ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
		//当找不到这样的node时返回NULL
		if (!pListHead || k <= 0)
			return NULL;
		int step = 0;
		ListNode*cur = pListHead;
		while (step != k&&cur)
		{
			cur = cur->next;
			++step;
		}
		if (step != k)
			return NULL;
		ListNode*res = pListHead;
		while (cur)
		{
			cur = cur->next;
			res = res->next;
		}
		return res;
	}

	ListNode* removeNthFromEnd(ListNode* head, int n) {
		int step = 0;
		auto cur = head;
		while (step != n)
		{
			cur = cur->next;
			++step;
		}
		ListNode* back = head, *pre = NULL, *newHead;
		while (cur)
		{
			cur = cur->next;
			pre = back;
			back = back->next;
		}
		if (back == head)
		{
			newHead = back->next;
			return newHead;
		}
		pre->next = back->next;
		return head;
	}
};

class ReverseLst
{
public:
	ListNode* ReverseList(ListNode* head) {
		if (!head)return NULL;
		ListNode* pre = NULL, *cur = head, *next;
		while (cur)
		{
			next = cur->next;
			cur->next = pre;
			pre = cur;
			cur = next;
		}
		return pre;
	}
};
class Solution_sortList {
	ListNode* Merge(ListNode* head1, ListNode* head2)
	{
		if (!head1)
			return head2;
		if (!head2)
			return head1;
		ListNode* big = (head1->val>head2->val?head1:head2);
		ListNode*small = (head1->val>head2->val ? head2 : head1);
		small->next = Merge(small->next,big);
		return small;
	}
	pair<ListNode*, ListNode*>split(ListNode*head)
	{
		if (!head)
			return{NULL,NULL};
		if (!head->next)
			return{ NULL, head };
		ListNode*slow = head, *fast = head->next;
		while (fast->next&&fast->next->next)
		{
			fast = fast->next->next;
			slow = slow->next;
		}
		ListNode*head2 = slow->next;
		slow->next = NULL;
		return{head,head2};
	}
	
public:
	ListNode* sortListRecur(ListNode* head) {
		if (!head || !head->next)
			return head;
		auto p = split(head);
		p.first=sortListRecur(p.first);
		p.second=sortListRecur(p.second);
		return Merge(p.first, p.second);
	}
};
class Solution_FindFirstCommonNode {
	int countNumOfList(ListNode*head)
	{
		int cnt = 0;
		while (head)
		{
			++cnt;
			head = head->next;
		}
		return cnt;
	}
public:
	ListNode* FindFirstCommonNode(ListNode* pHead1, ListNode* pHead2) {
		if (!pHead1 || !pHead2)return NULL;
		int num1 = countNumOfList(pHead1);
		int num2 = countNumOfList(pHead2);
		ListNode* longer = (num1>num2?pHead1:pHead2);
		ListNode* shorter = (num1>num2?pHead2:pHead1);
		int diff = abs(num1 - num2), step = 0;
		while (step != diff)
		{
			longer = longer->next;
			++step;
		}
		while (longer&&shorter)
		{
			if (longer == shorter)
				return longer;
			longer = longer->next;
			shorter = shorter->next;
		}
		return NULL;
	}
};
class Solution_numTrees {
public:
	int numTrees(int n) {
		vector<int>dp(n+1);
		dp[0] = 1;
		for (int i = 1; i <= n; ++i)
		{
			dp[i] = 0;
			for (int j = 1; j <= i; ++j)
			{
				dp[i] += (dp[j-1]*dp[i-j]);
			}
		}
		return dp[n];
	}
};
class Solution_Mirror {
public:
	void Mirror(TreeNode *pRoot) {
		if (!pRoot)return;
		auto temp = pRoot->left;
		pRoot->left = pRoot->right;
		pRoot->right = temp;
		Mirror(pRoot->left);
		Mirror(pRoot->right);
	}
};
int minNumberInRotateArray(vector<int> rotateArray) {
	if (rotateArray.empty())return 0;
	int bi = 0, ei = rotateArray.size() - 1;
	if (rotateArray[bi] < rotateArray[ei])
		return rotateArray[bi];
	int mid;
	while (ei - bi>1)
	{
		mid = bi + (ei - bi) / 2;
		if (rotateArray[bi] == rotateArray[ei]&&rotateArray[ei]==rotateArray[mid])
			return *min_element(rotateArray.begin()+bi,rotateArray.begin()+ei+1);
		//rotateArray[bi]>rotateArray[ei]
		if (rotateArray[mid] >= rotateArray[bi])
			bi = mid;
		else if (rotateArray[mid] <= rotateArray[ei])
			ei = mid;
	}
	return rotateArray[ei];
}
class Random_select
{
public:
	int random_partition(vector<int>&arr, int left, int right)
	{
		int ri = rand() % (right - left + 1) + left;
		swap(arr[ri],arr[right]);
		int val = arr[right];
		int i = left - 1;
		for (int j = left; j <= right; ++j)
		{
			if (arr[j] <= val)
				swap(arr[++i],arr[j]);
		}
		return i;
	}
	int random_select(vector<int>&arr, int left, int right, int i)
	{
		assert(left<=right);
		if (left == right)
			return arr[left];
		int pivot = random_partition(arr,left,right);
		int k = pivot - left + 1;
		if (k == i)
			return arr[pivot];
		else if (k > i)
			return random_select(arr, left,pivot - 1, i);
		else
			return random_select(arr,pivot+1,right,i-k);
	}
};
int MoreThanHalfNum_Solution(vector<int> numbers) {
	//数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字,如果不存在返回0
	if (numbers.empty())return 0;
	int cand = numbers[0];
	int times = 1;
	for (int i = 1; i < numbers.size(); ++i)
	{
		if (times == 0)
		{
			cand = numbers[i];
			times = 1;
		}
		else
		{
			if (cand == numbers[i])
				++times;
			else
				--times;
		}
	}
	int cnt = 0;
	for (int number : numbers)
	{
		if (number == cand)
			++cnt;
	}
	if (cnt <= numbers.size() / 2)
		return 0;
	return cand;
}
class Solution_lengthOfLongestSubstring {
	string longestSubString0(string&s)
	{
		string res;
		if (s.empty())return res;
		unordered_set<char>st;
		int maxSize = INT_MIN;
		int maxStart = 0;
		int right = 0, left = 0;
		while (right < s.size())
		{
			if (st.find(s[right]) == st.end())
			{
				st.insert(s[right]);
			}
			else
			{
				char c = s[right];
				char ce;
				while (left < right)
				{
					ce = s[left++];
					if (ce == c)
						break;
					st.erase(ce);
					
				}
			}
			if (right - left + 1 > maxSize)
			{
				maxSize = right - left + 1;
				maxStart = left;
			}
			++right;
		}
		return s.substr(maxStart,maxSize);
	}
	string longestSubString(string&s)
	{
		string res;
		if (s.empty())return res;
		vector<int>ht(128,0);
		int left = 0, right = 0, maxSize = INT_MIN, maxStartIndex = 0;
		while (right < s.size())
		{
			if (ht[s[right]] > 0)
			{
				while (s[left] != s[right])
				{
					ht[s[left++]]--;
				}
				ht[s[left++]]--;
			}
			assert(ht[s[right]]==0);
			ht[s[right]]++;
			if (right - left + 1 > maxSize)
			{
				maxSize = right - left + 1;
				maxStartIndex = left;
			}
			right++;
		}
		return s.substr(maxStartIndex,maxSize);
	}
public:
	int lengthOfLongestSubstring(string s) {
		return longestSubString(s).size();
	}
};
class Solution_LIS {
public:
	int lengthOfLIS0(vector<int>& nums) {
		vector<int>t;
		for (int num : nums)
		{
			auto it = lower_bound(t.begin(),t.end(),num);
			if (it == t.end())
				t.push_back(num);
			else
				*it = num;
		}
		return t.size();
	}
	vector<int>getDpArr(vector<int>&nums)
	{
		vector<int>dp(nums.size());
		vector<int>t;
		for (int i = 0; i < nums.size(); ++i)
		{
			auto it = lower_bound(t.begin(),t.end(),nums[i]);
			if (it == t.end())
			{
				t.push_back(nums[i]);
				dp[i] = t.size();
			}
			else
			{
				*it = nums[i];
				dp[i] = static_cast<int>(it-t.begin()+1);
			}
		}
		return dp;
	}
	vector<int>generateLISFromDpArr(vector<int>&nums, vector<int>&dp)
	{
		int index, len = 0;
		for (int i = 0; i < dp.size(); ++i)
		{
			if (dp[i]>len)
			{
				index = i;
				len = dp[i];
			}
		}
		vector<int>lis(len);
		while (len > 0)
		{
			--len;
			lis[len] = nums[index];
			for (int i = index - 1; i >= 0; --i)
			{
				if (nums[i] < nums[index] && dp[i] == dp[index] - 1)
				{
					index = i;
					break;
				}
			}
		}
		return lis;
	}
	vector<int>LIS(vector<int>&nums)
	{
		vector<int>lis;
		if (nums.empty())return lis;
		vector<int>dp = getDpArr(nums);
		lis = generateLISFromDpArr(nums,dp);
		return lis;
	}
	int lengthOfLIS(vector<int>& nums)
	{
		return LIS(nums).size();
	}
};
string LeftRotateString(string str, int n) {
	reverse(str.begin(),str.begin()+n);
	reverse(str.begin()+n,str.end());
	reverse(str.begin(),str.end());
	return str;
}
string longestPalindrome(string s) {
	if (s.empty())return string();
	vector<vector<bool>>dp(s.size(),vector<bool>(s.size(),false));
	for (int i = 0; i < s.size(); ++i)
		dp[i][i] = true;
	int maxLen = 1, maxStart = 0;
	for (int i = 1; i < s.size(); ++i)
	{
		if (dp[i - 1][i] = (s[i - 1] == s[i]))
		{
			if (2 > maxLen)
			{
				maxLen = 2;
				maxStart = i - 1;
			}
		}
		for (int j = i - 2; j >= 0; --j)
		{
			if (s[j] == s[i] && dp[j + 1][i - 1])
			{
				dp[j][i] = true;
				if (i - j + 1>maxLen)
				{
					maxLen = i - j + 1;
					maxStart = j;
				}
			}
		}
	}
	return s.substr(maxStart,maxLen);
}
class b
{
public:
	virtual void foob()
	{
		cout << "b\n";
	}
};
class d1 :public b
{
public:
	void foob()
	{
		cout << "d1v\n";
	}
	void food1()
	{
		cout << "d1\n";
	}
};
class d2 :public b
{
public:
	void foob()
	{
		cout << "d2v\n";
	}
	void food2()
	{
		cout << "d2\n";
	}
};
void main()
{
	try
	{
		b* pb = new d1;
		d2* pd2 = dynamic_cast<d2*>(pb);
		/*
		if (!pd2)
		{
			cout << "cast fail\n";
			return;
		}
		*/
		pd2->foob();
		int itrpt = 0;
	}
	catch (const runtime_error& e)
	{
		cout << "runtime error caught:" << e.what() << endl;
	}

}