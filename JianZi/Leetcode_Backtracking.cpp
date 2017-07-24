#include "moststd.h"
using namespace JZ;
//216. Combination Sum III
class Solution_combinationSum3 {
	void bt(int targetNumOfDigits, int targetNumber, int srcIndex, vector<int>&curItem, int curNumber,vector<vector<int>>&res)
	{
		if (curItem.size() == targetNumOfDigits || curNumber >= targetNumber)
		{
			if (curNumber == targetNumber&&curItem.size() == targetNumOfDigits)
				res.push_back(curItem);
			return;
		}
		for (int i = srcIndex + 1; i <= 9; ++i)
		{
			curNumber += i;
			curItem.push_back(i);
			bt(targetNumOfDigits,targetNumber,i,curItem,curNumber,res);
			curItem.pop_back();
			curNumber -= i;
		}
	}
public:
	vector<vector<int>> combinationSum3(int k, int n) {
		vector<vector<int>>res;
		int lmin = (1 + k)*k / 2;
		int lmax = (19 - k)*k / 2;
		if (k <= 0 || k >= 10 || n <= 0 || n < lmin || n > lmax)
			return res;

		vector<int>curItem;
		bt(k,n,0,curItem,0,res);
		return res;
	}
};

//leetcode 39. Combination Sum
class Solution_combinationSum {
	void bt(int targetNumber, int srcIndex, vector<int>&srcCandidates, vector<int>&curItem, int curNumber, vector<vector<int>>&res)
	{
		if (curNumber >= targetNumber)
		{
			if (curNumber == targetNumber)
				res.push_back(curItem);
			return;
		}
		for (int i = srcIndex; i <srcCandidates.size(); ++i)
		{
			curItem.push_back(srcCandidates[i]);
			curNumber += srcCandidates[i];
			bt(targetNumber,i,srcCandidates,curItem,curNumber,res);
			curItem.pop_back();
			curNumber -= srcCandidates[i];
		}
	}
public:
	vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
		vector<vector<int>>res;
		vector<int>item;
		sort(candidates.begin(),candidates.end());
		bt(target,0,candidates,item,0,res);
		return res;
	}
};
//leetcode 77. Combinations
class Solution_combine {
public:
	void backTracking(vector<vector<int>>&res, vector<int>&item, int curNum, int n, int k)
	{
		if (item.size() == k)
		{
			res.push_back(item);
			return;
		}
		for (int num = curNum + 1; num <= n; ++num)
		{
			item.push_back(num);
			backTracking(res, item, num, n, k);
			item.pop_back();
		}
	}
	vector<vector<int>> combine(int n, int k) {
		vector<vector<int>>res;
		if (k > n)
			return res;
		vector<int>item;
		backTracking(res, item, 0, n, k);
		return res;
	}
};
//40. Combination Sum II
class Solution_combinationSum2 {
	void bt(int targetNumber, int srcIndex, vector<int>&srcCandidates, vector<int>&curItem, int curNumber, vector<vector<int>>&res)
	{
		if (curNumber >= targetNumber)
		{
			if (curNumber == targetNumber)
				res.push_back(curItem);
			return;
		}
		for (int i = srcIndex+1; i <srcCandidates.size(); ++i)
		{
			if (i!=srcIndex+1&&srcCandidates[i] == srcCandidates[i - 1])
				continue;
			curItem.push_back(srcCandidates[i]);
			curNumber += srcCandidates[i];
			bt(targetNumber, i, srcCandidates, curItem, curNumber, res);
			curItem.pop_back();
			curNumber -= srcCandidates[i];
		}
	}
public:
	vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
		vector<vector<int>>res;
		vector<int>item;
		sort(candidates.begin(), candidates.end());
		bt(target, -1, candidates, item, 0, res);
		return res;
	}
};
//leetcode 46. Permutations
class Solution_Permutations {
	void bt(int targetSize, set<int>&srcSt, vector<int>&curItem,vector<vector<int>>&res)
	{
		if (curItem.size() == targetSize)
		{
			res.push_back(curItem);
			return;
		}
		vector<int>nums(srcSt.begin(),srcSt.end());
		for (int num : nums)
		{
			curItem.push_back(num);
			srcSt.erase(num);
			bt(targetSize,srcSt,curItem,res);
			curItem.pop_back();
			srcSt.insert(num);
		}
	}
public:
	vector<vector<int>> permute(vector<int>& nums) {
		vector<vector<int>>res;
		vector<int>curItem;
		set<int>srcSt(nums.begin(),nums.end());
		bt(nums.size(),srcSt,curItem,res);
		return res;
	}
};
//leetcode 47. Permutations II
class Solution_permuteUnique {
	void bt(int targetSize,int srcIndex,vector<int>&srcNums,vector<int>&curItem,vector<vector<int>>&res)
	{
		if (curItem.size() == targetSize)
		{
			res.push_back(curItem);
			return;
		}
		vector<int>srcNums2 = srcNums;
		sort(srcNums2.begin()+srcIndex,srcNums2.end());
		for (int i = srcIndex; i < srcNums2.size(); ++i)
		{
			if (i != srcIndex&&srcNums2[i] == srcNums2[i - 1])
			{
				continue;
			}
			swap(srcNums2[srcIndex],srcNums2[i]);
			curItem.push_back(srcNums2[srcIndex]);
			bt(targetSize,srcIndex+1,srcNums2,curItem,res);
			curItem.pop_back();
			swap(srcNums2[srcIndex],srcNums2[i]);
		}
	}
public:
	vector<vector<int>> permuteUnique(vector<int>& nums) {
		vector<vector<int>>res;
		vector<int>curItem;
		bt(nums.size(),0,nums,curItem,res);
		return res;
	}
};

//leetcode 17. Letter Combinations of a Phone Number
class Solution_letterCombinations {
	void bt(int targetSize, int srcIndex, string&srcDigits, unordered_map<char, vector<char>>&srcMp, string&curItem, vector<string>&res)
	{
		if (curItem.size() == targetSize)
		{
			res.push_back(curItem);
			return;
		}
		vector<char>letters = srcMp[srcDigits[srcIndex]];
		for (char letter : letters)
		{
			curItem.push_back(letter);
			bt(targetSize,srcIndex+1,srcDigits,srcMp,curItem,res);
			curItem.pop_back();
		}
	}
public:
	vector<string> letterCombinations(string digits) {
		vector<string>res;
		if (digits.empty())
			return res;
		string curItem;
		unordered_map<char, vector<char>>srcMp;
		srcMp['2'] = {'a','b','c'};
		srcMp['3'] = {'d','e','f'};
		srcMp['4'] = { 'g', 'h', 'i' };
		srcMp['5'] = { 'j', 'k', 'l' };
		srcMp['6'] = { 'm', 'n', 'o' };
		srcMp['7'] = { 'p', 'q', 'r', 's' };
		srcMp['8'] = { 't', 'u', 'v' };
		srcMp['9'] = { 'w', 'x', 'y', 'z' };
		bt(digits.size(),0,digits,srcMp,curItem,res);
		return res;
	}
};
//leetcode 131. Palindrome Partitioning
class Solution_partition {
	bool isPalin(string& s)
	{
		if (s.empty())
			return true;
		int i = 0;
		int j = s.size() - 1;
		while (j > i)
		{
			if (s[j] != s[i])
				return false;
			++i;
			--j;
		}
		return true;
	}
	void bt(int targetSize, int srcIndex, string&srcStr, int curSize, vector<string>&curItem, vector<vector<string>>&res)
	{
		if (curSize == targetSize||srcIndex>=srcStr.size())
		{
			if (curSize == targetSize)
			     res.push_back(curItem);
			return;
		}
		for (int len = 1; len <= srcStr.size() - srcIndex; ++len)
		{
			string part = srcStr.substr(srcIndex,len);
			if (!isPalin(part))
				continue;
			curItem.push_back(part);
			bt(targetSize,srcIndex+len,srcStr,curSize+len,curItem,res);
			curItem.pop_back();
		}
	}
public:
	vector<vector<string>> partition(string s) {
		vector<vector<string>>res;
		if (s.empty())return res;
		vector<string>curItem;
		bt(s.size(),0,s,0,curItem,res);
		return res;
	}
};
//leetcode 22. Generate Parentheses
class Solution_generateParenthesis {
	void bt(int targetSize, int curLeftNum, int curRightNum, int curPendingLeft,string&curItem, vector<string>&res)
	{
		if (curItem.size() == 2 * targetSize)
		{
			if (curPendingLeft == 0)
				res.push_back(curItem);
			return;
		}
		if (curLeftNum < targetSize)
		{
			curItem.push_back('(');
			bt(targetSize,curLeftNum+1,curRightNum,curPendingLeft+1,curItem,res);
			curItem.pop_back();
		}
		if (curRightNum < targetSize&&curPendingLeft>0)
		{
			curItem.push_back(')');
			bt(targetSize, curLeftNum, curRightNum + 1, curPendingLeft - 1,curItem,res);
			curItem.pop_back();
		}
	}
public:
	vector<string> generateParenthesis(int n) {
		vector<string>res;
		if (n <= 0)return res;
		string curItem;
		bt(n,0,0,0,curItem,res);
		return res;
	}
};
//leetcode 89. Gray Code
class Solution_grayCode {
public:
	vector<int> grayCode(int n) {
		vector<int>res;
		if (n == 0)
		{
			res = {0};
			return res;
		}
		if (n == 1)
		{
			res = {0,1};
			return res;
		}
		vector<int>preRes = grayCode(n-1);
		res.insert(res.begin(),preRes.begin(),preRes.end());
		for (auto i = preRes.rbegin(); i != preRes.rend(); ++i)
		{
			int item = *i + pow(2,n-1);
			res.push_back(item);
		}
		return res;
	}
};

//leetcode 51.N-Queens
//a solution requires that no two queens share the same row, column, or diagonal
class Solution_solveNQueens {
	struct Point
	{
		int row;
		int col;
		Point(int r = 0, int c = 0) :row(r), col(c){}
	};
	bool isThreatened(Point p1, Point p2)
	{
		return  (p1.row == p2.row || p1.col == p2.col || abs(p1.row - p2.row) == abs(p1.col - p2.col));
	}
	bool isThreatened(const vector<Point>&pts, Point pt)
	{
		for (Point p : pts)
		{
			if (isThreatened(p, pt))
				return true;
		}
		return false;
	}
	bool bt(int targetSize,int curRow,vector<Point>&curPts,vector<vector<Point>>&res)
	{
		if (curRow == targetSize)
		{
			res.push_back(curPts);
			return true;
		}
		bool flag = false;
		for (int col = 0; col < targetSize; ++col)
		{
			Point pt(curRow,col);
			if (isThreatened(curPts, pt))
			{
				continue;
			}
			curPts.push_back(pt);
			flag = bt(targetSize,curRow+1,curPts,res);
			curPts.pop_back();
		}
		return flag;
	}
	vector<vector<string>>convert(vector<vector<Point>>&chessboards,int N)
	{
		vector<vector<string>>res;
		for (vector<Point>&chessboard : chessboards)
		{
			vector<string>item;
			for (Point pt : chessboard)
			{
				string s(N,'.');
				s[pt.col] = 'Q';
				item.push_back(s);
			}
			res.push_back(item);
		}
		return res;
	}
public:
	vector<vector<string>> solveNQueens(int n) {
		vector<vector<Point>>res0;
		vector<vector<string>>res;
		if (n <= 0)return res;
		vector<Point>curPts;
		bt(n,0,curPts,res0);
		res = convert(res0,n);
		return res;
	}
};
class Solution_restoreIpAddresses {
	bool isValidIPPart(const string&sub)
	{
		return  ((sub.size() < 3 && (sub[0] != '0' || (sub[0] == '0'&&sub.size() == 1))) || \
			(sub.size() == 3 && sub[0] != '0' && sub <= "255"));
	}
	vector<string>convert(vector<vector<string>>&ori)
	{
		vector<string>res;
		for (vector<string>&itemOri : ori)
		{
			string str = "";
			for (string&part : itemOri)
			{
				str += part;
				str += ".";
			}
			str.pop_back();
			res.push_back(str);
		}
		return res;
	}
	void bt(int targetSize, int srcIndex, string&srcStr, int curSize, vector<string>&curItem, vector<vector<string>>&res)
	{
		if (targetSize == curSize || curItem.size() == 4)
		{
			if (targetSize == curSize&&curItem.size() == 4)
				res.push_back(curItem);
			return;
		}
		for (int len = 1; len <= 3; ++len)
		{
			if (srcIndex + len <= srcStr.size())
			{
				string part = srcStr.substr(srcIndex,len);
				if (isValidIPPart(part))
				{
					curItem.push_back(part);
					bt(targetSize,srcIndex+len,srcStr,curSize+len,curItem,res);
					curItem.pop_back();
				}
			}
		}
	}
public:
	vector<string> restoreIpAddresses(string s) {
		vector<string>res;
		if (s.empty())return res;
		vector<vector<string>>res0;
		vector<string>curItem;
		bt(s.size(),0,s,0,curItem,res0);
		res = convert(res0);
		return res;
	}
};
//leetcode 79. Word Search
class Solution_worldSearch {
	struct Point
	{
		int row;
		int col;
		Point(int r = 0, int c = 0) :row(r), col(c){}
	};
	multimap<char, Point>genMp(const vector<vector<char>>& board)
	{
		multimap<char, Point>mp;
		for (int r = 0; r < board.size(); ++r)
		{
			for (int c = 0; c < board[0].size(); ++c)
			{
				mp.insert(make_pair(board[r][c],Point(r,c)));
			}
		}
		return mp;
	}
	bool bt(string& targetWord, vector<vector<char>>& board, int curSize, Point curPos)
	{
		if (curSize == targetWord.size())
			return true;
	
		bool found = false;
		int h = board.size()-1, w = board[0].size()-1;
		int dr[4] = {0,-1,0,1};
		int dc[4] = { -1, 0, 1, 0 };
		for (int i = 0; i < 4; ++i)
		{
			int nr = dr[i] + curPos.row, nc = dc[i] + curPos.col;
			if (nr >= 0 && nr <= h&&nc >= 0 && nc <= w&&board[nr][nc] != '*'&&board[nr][nc]==targetWord[curSize])
			{
				char temp = board[nr][nc];
				board[nr][nc] = '*';
				if (bt(targetWord, board, curSize + 1, Point(nr, nc)))
					return true;
				board[nr][nc] = temp;
			}
		}
		return false;
	}
public:
	bool exist(vector<vector<char>>& board, string word) {
		if (board.empty() || board[0].empty())
			return false;
		if (word.empty())
			return true;
		multimap<char, Point> mp = genMp(board);
		for (auto beg = mp.lower_bound(word[0]), end = mp.upper_bound(word[0]); beg != end; ++beg)
		{
			Point curPos = beg->second;
			char temp = board[curPos.row][curPos.col];
			board[curPos.row][curPos.col] = '*';
			if (bt(word, board, 1, curPos))
				return true;
			board[curPos.row][curPos.col] = temp;
		}
		return false;
	}
};

