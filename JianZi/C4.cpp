#include "moststd.h"
using namespace JZ;
//P132-T21
//Leetcode -T155 Min Stack
class MinStack {
	stack<int>stk;
	stack<int>mins;
public:
	void push(int x) {
		if (mins.empty())
			mins.push(x);
		else
		{
			if (x <= mins.top())
				mins.push(x);
		}
		stk.push(x);
	}

	void pop() {
		int top = stk.top();
		stk.pop();
		if (top == mins.top())
			mins.pop();
	}

	int top() {
		return stk.top();
	}

	int getMin() {
		return mins.top();
	}
};
//P134--T22
class IsPopOrder
{
public:
	bool isPopOrder(const vector<int>&arrPush, const vector<int>&arrPop)
	{
		if (arrPush.size() != arrPop.size())
			return false;
		if (arrPush.empty())
			return true;
		int indexToPush = 0, indexToPop = 0;
		stack<int>stk;
		while (indexToPush != arrPush.size())
		{
			if (stk.empty()||arrPop[indexToPop] != stk.top())
			{
				stk.push(arrPush[indexToPush++]);
			}
			else
			{
				while (!stk.empty() &&indexToPop<=arrPop.size()-1 &&arrPop[indexToPop] == stk.top())
				{
					stk.pop();
					++indexToPop;
				}
			}
		}
		while (!stk.empty() && indexToPop <= arrPop.size() - 1 && arrPop[indexToPop] == stk.top())
		{
			stk.pop();
			++indexToPop;
		}
		return stk.empty();
	}
};
//P140--T24
class SequenceOfBST
{
	int getRightOfLeftPart(const vector<int>&sequence, int left, int right)
	{
		int val = sequence[right];
		int i = right - 1;
		for (; i >= left; --i)
		{
			if (sequence[i]<val)
				break;
		}
		return i;
	}
	bool help(const vector<int>&sequence, int left, int right)
	{
		if (left == right|| left > right)
			return true;
		int rightOfLeftPart = getRightOfLeftPart(sequence,left,right);
		for (int i = rightOfLeftPart - 1; i >= left; --i)
		{
			if (sequence[i] >= sequence[right])
				return false;
		}
		return help(sequence, left, rightOfLeftPart) && help(sequence,rightOfLeftPart+1,right-1);
	}
public:
	bool VerifySquenceOfBST(vector<int> sequence) {
		if (sequence.empty())
			return false;
		return help(sequence,0,sequence.size()-1);
	}
};

class PathInTree
{
    struct TreeNode {
		int val;
		struct TreeNode *left;
		struct TreeNode *right;
		TreeNode(int x) :val(x), left(NULL), right(NULL){}
	};
	bool isLeaf(TreeNode*node)
	{
		return !node->left&&!node->right;
	}
	void help(vector<vector<int>>&res, deque<int>&prePath, int preSum,TreeNode* root, int expectNumber)
	{
		if (!root)
			return;
		int curSum = root->val + preSum;
		prePath.push_back(root->val);
		if (curSum == expectNumber&&isLeaf(root))
			res.push_back(vector<int>(prePath.begin(),prePath.end()));
		help(res,prePath,curSum,root->left,expectNumber);
		help(res,prePath,curSum,root->right,expectNumber);
		prePath.pop_back();
	}
public:
	vector<vector<int> > FindPath(TreeNode* root, int expectNumber) {
		vector<vector<int>>res;
		deque<int>prePath;
		help(res,prePath,0,root,expectNumber);
		return res;
	}

};
/*
void main()
{
	try
	{
		
		int itrpt = 0;
	}
	catch (const runtime_error& e)
	{
		cout << "runtime error caught:" << e.what() << endl;
	}
	
}
*/