#include "moststd.h"
using namespace JZ;
listNode* JZ::genList(std::vector<int>&arr)
{
	if (arr.empty())return NULL;
	listNode* cur, *pre, *head;
	head = (listNode*)malloc(sizeof(listNode));
	head->val = arr[0];
	head->next = NULL;
	pre = head;
	for (int i = 1; i < (int)arr.size(); ++i)
	{
		cur = (listNode*)malloc(sizeof(listNode));
		cur->val = arr[i];
		cur->next = NULL;
		pre->next = cur;
		pre = cur;
	}
	return head;
}
void JZ::printList(listNode*lstHead)
{
	while (lstHead != NULL)
	{
		std::cout << lstHead->val << " ";
		lstHead = lstHead->next;
	}
	std::cout << std::endl;
}
vector<string>split(const string& str, char delim)
{
	vector<string>res;
	size_t start = 0;
	for (size_t i = 0; i < str.size(); ++i)
	{
		if (str[i] == delim)
		{
			res.push_back(str.substr(start, i - start));
			start = i + 1;
		}
	}
	return res;
}
string JZ::serialByLevel(treeNode*root)
{
	string res = "";
	queue<treeNode*>q;
	q.push(root);
	while (!q.empty())
	{
		treeNode* front = q.front();
		q.pop();
		if (!front)
		{
			res += "#!";
		}
		else
		{
			res += to_string(front->val) + "!";
			q.push(front->left);
			q.push(front->right);
		}
	}
	return res;
}
treeNode* JZ::reconByLevelString(const string& levelStr)
{
	if (levelStr == "#!")return NULL;
	vector<string>items = split(levelStr, '!');
	queue<treeNode*>q;
	int cnt = 0;
	treeNode* root = new treeNode(stoi(items[0]));
	q.push(root);
	for (size_t i = 1; i < items.size(); ++i)
	{
		treeNode* cur = (items[i] == "#" ? NULL : new treeNode(stoi(items[i])));
		if (cnt == 0)
		{
			q.front()->left = cur;
		}
		if (cnt == 1)
		{
			q.front()->right = cur;
		}
		if (cur)q.push(cur);
		++cnt;
		if (cnt == 2)
		{
			cnt = 0;
			q.pop();
		}
	}
	return root;
}
string getSpace(int num)
{
	string res = "";
	for (int i = 0; i < num; ++i)
	{
		res += " ";
	}
	return res;
}
void printInOrder(treeNode*head, int height, int spaceLen, string to)
{
	if (!head)return;
	printInOrder(head->right, height + 1, spaceLen, "v");
	string val = to + to_string(head->val) + to;
	int lenM = val.length();
	int lenL = (spaceLen - lenM) / 2;
	int lenR = spaceLen - lenM - lenL;
	val = getSpace(lenL) + val + getSpace(lenR);
	cout << getSpace(height*spaceLen) + val << endl;
	printInOrder(head->left, height + 1, spaceLen, "^");
}
void JZ::printTree(treeNode*root)
{
	cout << "´òÓ¡¶þ²æÊ÷:\n";
	printInOrder(root, 0, 17, "H");
}