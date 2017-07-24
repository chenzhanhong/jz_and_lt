#include "moststd.h"
using namespace JZ;

//P244 -T49
class String2Int
{
	bool isValid(string& str)
	{
		if (str.empty())
			return false;
		if ((str[0] == '-' || str[0] == '+') && (str.size() == 1 || str[1] == '0'))
			return false;
		if (str[0] == '0'&&str.size() > 1)
			return false;
		int i = ((str[0] == '-' || str[0] == '+') ? 1 : 0);
		for (; i < str.size(); ++i)
		{
			if (str[i] > '9' || str[i] < '0')
				return false;
		}
		return true;
	}
public:
	int StrToInt(string str) {
		if (!isValid(str))
			return 0;
		bool isNegative = (str[0] == '-');
		int preMin = INT_MIN / 10;
		int resMin = INT_MIN % 10;
		int number = 0;
		int i = ((str[0] == '-' || str[0] == '+') ? 1 : 0);
		for (; i < str.size(); ++i)
		{
			int curBit = '0' - str[i];
			if (number < preMin || (number == preMin&&curBit < resMin))
				return 0;
			number = 10 * number + curBit;
		}
		if (!isNegative&&number == INT_MIN)
			return 0;
		return isNegative ? number : 0 - number;
	}
};
//leetcode 235. Lowest Common Ancestor of a Binary Search Tree
class Solution_BSTlowestCommonAncestor{
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	};
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		if (!root)return NULL;
		if (root == p || root == q)return root;
		int big = max(p->val,q->val);
		int small = min(p->val,q->val);
		if (big > root->val&&small < root->val)return root;
		if (big < root->val)return lowestCommonAncestor(root->left,p,q);
		return lowestCommonAncestor(root->right,p,q);
	}
};
//Leetcode 236. Lowest Common Ancestor of a Binary Tree
class Solution_lowestCommonAncestor {
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	};
	bool setupPath(TreeNode* root, TreeNode*node,list<TreeNode*>&path)
	{
		if (!root)return false;
		if (root == node)
		{
			path.push_back(node);
			return true;
		}
		path.push_back(root);
		bool foundl = setupPath(root->left,node,path);
		bool foundr = setupPath(root->right,node,path);
		bool found = foundl || foundr;
		if (!found)
			path.pop_back();
		return found;
	}
	bool setupPath0(TreeNode* root, TreeNode*node, list<TreeNode*>&resPath, list<TreeNode*>&prePath)
	{
		if (!root)return false;
		prePath.push_back(root);
		if (node == root)
		{
			resPath = prePath;
			return true;
		}
		if (setupPath0(root->left, node, resPath, prePath))
			return true;
		if (setupPath0(root->right, node, resPath, prePath))
			return true;
		prePath.pop_back();
		return false;
	}
	TreeNode* getLCA(const list<TreeNode*>&path1, const list<TreeNode*>&path2)
	{
		TreeNode* last=NULL;
		auto i1 = path1.begin(), i2 = path2.begin();
		while (i1 != path1.end() && i2 != path2.end())
		{
			if (*i1 == *i2)
				last = *i1;
			++i1;
			++i2;
		}
		return last;
	}
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		if (!root)return NULL;
		list<TreeNode*>path1, path2,prePath1,prePath2;
		setupPath0(root, p, path1, prePath1);
		setupPath0(root,q,path2,prePath2);
		return getLCA(path1,path2);
	}
};
