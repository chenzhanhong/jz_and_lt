#pragma once
#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <utility>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <mutex>
#include <stdexcept>
#include <time.h>
#include <cmath>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
namespace JZ
{
	using namespace std;
	
	struct listNode
	{
		int val;
		listNode* next;
		listNode(int v) :val(v), next(NULL){}
	};
	struct ListNode {
		int val;
		ListNode *next;
		ListNode(int x) : val(x), next(NULL) {}
	};
	struct treeNode
	{
		int val;
		treeNode* left;
		treeNode* right;
		treeNode(int v) :val(v), left(NULL), right(NULL){}
	};
	struct TreeNode
	{
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode(int v) :val(v), left(NULL), right(NULL){}
	};
	listNode* genList(std::vector<int>&arr);
	void printList(listNode*lstHead);
	void printTree(treeNode*root);
	string serialByLevel(treeNode*root);
	treeNode* reconByLevelString(const string& levelStr);
   
}
