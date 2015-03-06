// Copyright (c) 2014 Jiasen Yang. All rights reserved.

/* --------------------------- DATE: AUG 11, 2014 --------------------------- */

/* ------------------------------ Definitions ------------------------------- */

// Definition for singly-linked list
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

// Definition for Binary Tree
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/* ----------------------------- Single Number ------------------------------ */
/* Given an array of integers, every element appears twice except for one. 
   Find that single one. */

int singleNumber(int A[], int n) {
	for (int i = 1; i < n; i++) {
		A[i] ^= A[i - 1];
	}
	return A[n - 1];
}

/* ------------------- Maximum Depth of Binary Tree ------------------------- */
/* Given a binary tree, find its maximum depth.
   The maximum depth is the number of nodes along the longest path from 
   the root node down to the farthest leaf node. */

int maxDepth(TreeNode *root) {
	if (root == NULL) return 0;
	return 1 + max(maxDepth(root->left), maxDepth(root->right));
}

/* ------------------------------- Same Tree -------------------------------- */
/* Given two binary trees, write a function to check if they are equal or not.
   Two binary trees are considered equal if they are structurally identical and 
   the nodes have the same value. */

bool isSameTree(TreeNode *p, TreeNode *q) {
	if (p == NULL && q == NULL) {
		return true;
	} else if (p == NULL || q== NULL) {
		return false;
	} 
	if (p->val != q->val) return false;
	return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}

/* ---------------------------- Reverse Integer ----------------------------- */
/* Reverse digits of an integer. */

int reverse(int x) {
	int q = x;  // Quotient
	int y = 0;  // Reversed integer
	while (q > 0) {
		y = y * 10 + q % 10;
		q = q / 10;
	}
	return y;
}

/* ------------------- Best Time to Buy and Sell Stock II ------------------- */
/* Say you have an array in which the i-th element is the price of a given stock
   on day i. Design an algorithm to find the maximum profit. You may complete as
   many transactions as you like (i.e., buy one and sell one share of the stock 
   multiple times). However, you may not engage in multiple transactions at the 
   same time (i.e., you must sell the stock before you buy again). */

int maxProfit(vector<int> &prices) {
	int profit = 0;
	for (int i = 1; i < prices.size(); i++) {
		if (prices[i] > prices[i - 1]) {
			profit += prices[i] - prices[i - 1];
		}
	}
	return profit;
}

/* ----------------------- Unique Binary Search Trees ----------------------- */
/* Given n, how many structurally unique BST's (binary search trees) exists that
   stores the values 1, ... , n? */

	int numTrees(int n) {
		if (n == 1) return 1;
		int num = 0;
		for (int r = 1; r <= n; r++) {  // Choose node i as the root
			num += numTrees(r - 1) * numTrees(n - r);
		}
		return num;
	}

/* --------------------------- Linked List Cycle ---------------------------- */
/* Given a linked list, determine if it has a cycle in it.
   Follow up: Can you solve it without using extra space? */

bool hasCycle(ListNode *head) {
	if (head == NULL || head->next == NULL) return false;
	ListNode *slow = head;
	ListNode *fast = head->next;
	while (slow != NULL && fast != NULL && fast->next != NULL) {
		if (slow == fast) return true;
		slow = slow->next;
		fast = fast->next->next;
	}
	return false;
}

/* --------------------- Binary Tree Inorder Traversal ---------------------- */
/* Given a binary tree, return the inorder traversal of its nodes' values. */

vector<int> inorderTraversal(TreeNode *root) {
	vector<int> out = vector<int>();
	if (root == NULL) return out;
	stack<TreeNode *> parentStack = stack<TreeNode *>();
	TreeNode *current = root;
	while (!parentStack.empty() || current != NULL) {
		if (current != NULL) {
			parentStack.push(current);
			current = current->left;
		} else {
			current = parentStack.top();
			parentStack.pop();
			out.push_back(current->val);
			current = current->right;
		}
	}
	return out;
}

/* -------------------- Binary Tree Preorder Traversal ---------------------- */
/* Given a binary tree, return the preorder traversal of its nodes' values. */

vector<int> preorderTraversal(TreeNode *root) {
	vector<int> out = vector<int>();
	if (root == NULL) return out;
	stack<TreeNode *> parentStack = stack<TreeNode *>();
	parentStack.push(root);
	while (!parentStack.empty()) {
		TreeNode *current = parentStack.top();
		parentStack.pop();
		out.push_back(current->val);
		if (current->right != NULL) parentStack.push(current->right);
		if (current->left != NULL) parentStack.push(current->left);
	}
	return out;
	}

/* -------------- Populating Next Right Pointers in Each Node --------------- */
// Given a binary tree
struct TreeLinkNode {
   	TreeLinkNode *left;
	TreeLinkNode *right;
   	TreeLinkNode *next;
};
/* Populate each next pointer to point to its next right node.
   If there is no next right node, the next pointer should be set to NULL.
   Initially, all next pointers are set to NULL.
   Note: You may only use constant extra space.
   You may assume that it is a perfect binary tree (i.e., all leaves are at the 
   same level, and every parent has two children). */

// Using O(n/2) extra space
void connect(TreeLinkNode *root) {
    if (root == NULL) return;
	queue<TreeLinkNode *> parentQueue = queue<TreeLinkNode *>();
	parentQueue.push(root);
	parentQueue.push(NULL);
	while (parentQueue.front() != NULL) {
		TreeLinkNode *current = parentQueue.front();
		parentQueue.pop();
		current->next = parentQueue.front();
		if (current->left != NULL) parentQueue.push(current->left);
		if (current->right != NULL) parentQueue.push(current->right);
		if (parentQueue.front() == NULL) {
			parentQueue.pop();
			parentQueue.push(NULL);
		}
	}
}

// Using constant extra space
void connect(TreeLinkNode *root) {
	TreeLinkNode *leftWall = root;
	while (leftWall != NULL) {
		TreeLinkNode *across = leftWall;
		while (across != NULL) {
			if (across->left != NULL) {
				across->left->next = across->right;
			}
			if (across->right != NULL && across->next != NULL) {
				across->right->next = across->next->left;
			}
			across = across->next;
		}
		leftWall = leftWall->left;
	}
}

/* ------------------------- Search Insert Position ------------------------- */
/* Given a sorted array and a target value, return the index if target is found.
   If not, return the index where it would be if it were inserted in order.
   You may assume no duplicates in the array. */

int searchInsert(int A[], int n, int target) {
    for (int i = 0; i < n; i++) {
		if (A[i] >= target) return i;
	}
	return n;
}

/* ------------------- Remove Duplicates from Sorted List ------------------- */
/* Given a sorted linked list, delete all duplicates such that each element 
   appears only once. */

ListNode *deleteDuplicates(ListNode *head) {
	ListNode *curr = head;
	ListNode *prev = NULL;
	while (curr != NULL) {
		prev = curr;
		curr = curr->next;
		while (curr != NULL && curr->val == prev->val) {
			prev->next = curr->next;
			delete curr;
			curr = prev->next;
		}
	}
	return head;
}

/* ---------------------------- Roman to Integer ---------------------------- */
/* Given a roman numeral, convert it to an integer.
   Input is guaranteed to be within the range from 1 to 3999. */

int romanToInt(string s) {
	int res = 0;
	char pre = ' ';
	for (int i = 0; i < s.length(); i++) {
		switch (s[i]) {
			case 'I': res += 1; break;
			case 'V': res += (pre == 'I' ? 4 - 1 : 5); break;
			case 'X': res += (pre == 'I' ? 9 - 1 : 10); break;
			case 'L': res += (pre == 'X' ? 40 - 10 : 50); break;
			case 'C': res += (pre == 'X' ? 90 - 10 : 100); break;
			case 'D': res += (pre == 'C' ? 400 - 100 : 500); break;
			case 'M': res += (pre == 'C' ? 900 - 100 : 1000); break;
			default: assert(false);
		}
		pre = s[i];
	}
	return res;
}

/* ---------------------------- Climbing Stairs ----------------------------- */
/* You are climbing a stair case. It takes n steps to reach to the top.
   Each time you can either climb 1 or 2 steps.
   In how many distinct ways can you climb to the top? */
// Alternative: \sum_{k = 1}^{n / 2} choose{n - k}{k}
// Alternative: compute Fibonacci sequence using O(n) memory

// Accepted: compute Fibonacci sequence using O(1) memory (DP)
int climbStairs(int n) {
	// Fibonacci sequence
	if (n == 0 || n == 1 || n == 2) return n;
	int backOne = 2;  // f[i - 1]
	int backTwo = 1;  // f[i - 2]
/*	
	int result;
	for (int i = 3; i <= n; i++) {
		result = stepOne + stepTwo;
		stepTwo = stepOne;
		stepOne = result;
	}
	return result;
*/
	for (int i = 3; i < n; i++) {
		backOne = backOne + backTwo;
		backTwo = backOne - backTwo;
	}
	return backOne + backTwo;
}

/* ---------------------------- Single Number II ---------------------------- */
/* Given an array of integers, every element appears three times except for one.
   Find that single one.
   Note: Your algorithm should have a linear runtime complexity.
   Could you implement it without using extra memory? */

// See Discuss for details
int singleNumber(int A[], int n) {
	int ones = 0, twos = 0, threes = 0;
	for (int i = 0; i < n; i++) {
		twos |= ones & A[i];
		ones ^= A[i];
		threes = ones & twos;
		ones &= ~threes;
		twos &= ~threes;
	}
	return ones;
}

/* ---------------------------- Maximum Subarray ---------------------------- */
/* Find the contiguous subarray within an array (containing at least one number)
   which has the largest sum. */

int maxSubArray(int A[], int n) {
	int current = A[0], best = A[0];
	for (int i = 1; i < n; i++) {
		current = max(current + A[i], A[i]);
		best = max(current, best);
	}
	return best;
}

/* --------------------------- DATE: AUG 12, 2014 --------------------------- */

/* ---------------------------- Integer to Roman ---------------------------- */
/* Given an integer, convert it to a roman numeral.
   Input is guaranteed to be within the range from 1 to 3999. */

class Solution {
	vector<int> int_dict {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
	vector<string> roman_dict {"M", "CM", "D", "CD", "C", "XC", "L", "XL", 
							"X", "IX", "V", "IV", "I"};
  public:
  	string intToRoman(int num) {
		for (int i = 0; i < int_dict.size(); i++) {
			if (num >= int_dict[i])
				return roman_dict[i] + intToRoman(num - int_dict[i]);
		}
		return "";
	}
};

/* ----------------------------- Remove Element ----------------------------- */
/* Given an array and a value, remove all instances of that value in place and 
   return the new length. The order of elements can be changed. 
   It doesn't matter what you leave beyond the new length. */

int removeElement(int A[], int n, int elem) {
		int l = 0, r = n - 1;
		while (A[r] == elem) r--;
		while (l < r) {
			if (A[l] == elem) {
				int temp = A[l];
				A[l] = A[r];
				A[r] = temp;
			}
			l++;
			while (A[r] == elem) r--;
		}
		return r + 1;
}

/* ------------------------- Merge Two Sorted Lists ------------------------- */
/* Merge two sorted linked lists and return it as a new list. The new list 
   should be made by splicing together the nodes of the first two lists. */

// Iterative
ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
	if (l1 == NULL) return l2;
	if (l2 == NULL) return l1;
	ListNode *curr = l1, *prev = NULL;
	// Insert the elements of l2 into l1
	while (curr != NULL && l2 != NULL) {
		if (l2->val < curr->val) {
			if (prev == NULL) {
				// Insert at head of l1
				l1 = l2;
				l2 = l2->next;
				l1->next = curr;
				prev = l1;
			} else {
				prev->next = l2;
				l2 = l2->next;
				prev->next->next = curr;
				prev = prev->next;
			}
		} else {
			prev = curr;
    		curr = curr->next;
		}
	}
	if (curr == NULL) {
		// Append remaining elements in l2 to l1
		prev->next = l2;
	}
	return l1;
}

// Recursive
ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
	if (l1 == NULL) return l2;
	if (l2 == NULL) return l1;
	ListNode * head;
	if (l1->val < l2->val) {
		head = l1;
		l1 = l1->next;
	} else {
		head = l2;
		l2 = l2->next;
	}
	head->next = mergeTwoLists(l1, l2);
	return head;
}

/* ------------------------------ N-Queens II ------------------------------- */
/* Follow for "N-Queens":
   Now, instead of outputting board configurations, return the total number of 
   distinct solutions. */

// Backtracking
class Solution {
	int count;
	int *colForRow;  // The Queen in row i resides in column colForRow[i]
	int N;  // Number of Queens
  public:
  	bool isValid(int queen_num, int col_num) {
  		for (int i = 0; i < queen_num; i++) {
  			int diff = colForRow[i] - col_num;
  			if (diff < 0) diff = -diff;  // Take absolute value
  			if (diff == 0 || diff == queen_num - i) return false;
  		}
  		return true;
  	}
  	void placeQueen(int queen_num) {
  		if (queen_num == N) {
  			count++;
  			return;
  		}
  		for (int j = 0; j < N; j++) {
  			if (isValid(queen_num, j)) {
  				colForRow[queen_num] = j;
  				placeQueen(queen_num + 1);
  			}
  		}
  	}
  	int totalNQueens(int n) {
  		count = 0;
  		N = n;
  		colForRow = new int[n];
  		placeQueen(0);
  		return count;
  	}
};

/* -------------------------- Balanced Binary Tree -------------------------- */
/* Given a binary tree, determine if it is height-balanced. For this problem, a 
   height-balanced binary tree is defined as a binary tree in which the depth of
   the two subtrees of every node never differ by more than 1. */

int height(TreeNode *root) {
	if (root == NULL) return 0;
	return 1 + max(height(root->left), height(root->right));
}
bool isBalanced(TreeNode *root) {
	if (root == NULL) return true;
	int diff = height(root->left) - height(root->right);
	if (diff < 0) diff = -diff;  // Take absolute value
	if (diff > 1) return false;
	return isBalanced(root->left) && isBalanced(root->right);
}

/* -------------------------- Swap Nodes in Pairs --------------------------- */
/* Given a linked list, swap every two adjacent nodes and return its head.
   Your algorithm should use only constant space. You may not modify the values 
   in the list, only nodes itself can be changed. */

ListNode *swapPairs(ListNode *head) {
		if (head == NULL || head->next == NULL) return head;
		ListNode *curr = head, *prev = NULL;
		while (curr != NULL && curr->next != NULL) {
			if (prev == NULL) {
				head = curr->next;
				curr->next = curr->next->next;
				head->next = curr;
			} else {
				prev->next = curr->next;
				curr->next = curr->next->next;
				prev->next->next = curr;
			}
			prev = curr;
			curr = curr->next;
		}
		return head;
}

/* --------------- Convert Sorted Array to Binary Search Tree --------------- */
/* Given an array where elements are sorted in ascending order, convert it to a 
   height balanced BST. */

TreeNode *sortedArrayToBST(vector<int> &num) {
	return helper(num, 0, num.size() - 1);
}
TreeNode *helper(vector<int> &num, int left, int right) {
	if (left > right) return NULL;
	int mid = left + (right - left) / 2;
	TreeNode *root = new TreeNode(num[mid]);
	root->left = helper(num, left, mid - 1);
	root->right = helper(num, mid + 1, right);
	return root;
}

/* ------------------ Remove Duplicates from Sorted Array ------------------- */
/* Given a sorted array, remove the duplicates in place such that each element 
   appear only once and return the new length. Do not allocate extra space for 
   another array, you must do this in place with constant memory. */

int removeDuplicates(int A[], int n) {
	int count = 0;
	for (int i = 0; i < n; i++) {
		if (count == 0 || A[i] != A[count - 1]) {
			A[count] = A[i];
			count++;
		}
	}
	return count;
}

/* ----------------------------- Symmetric Tree ----------------------------- */
/* Given a binary tree, check whether it is a mirror of itself (i.e., symmetric 
   around its center).
   Note: Bonus points if you could solve it both recursively and iteratively. */

bool isSymmetric(TreeNode *root) {
	if (root == NULL) return true;
	return isOpposite(root->left, root->right);
}
bool isOpposite(TreeNode *p, TreeNode *q) {
	if (p == NULL && q == NULL) {
		return true;
	} else if (p == NULL || q == NULL) {
		return false;
	}
	if (p->val != q->val) return false;
	return isOpposite(p->left, q->right) && isOpposite(p->right, q->left);
}

/* --------------------------- DATE: AUG 14, 2014 --------------------------- */

/* ------------------------------- Gray Code -------------------------------- */
/* The gray code is a binary numeral system where two successive values differ 
   in only one bit. Given a non-negative integer n representing the total number
   of bits in the code, print the sequence of gray code. A gray code sequence 
   must begin with 0. */

vector<int> grayCode(int n) {
    vector<int> gray;
    gray.push_back(0);
    for (int len = 0; len < n; len++) {
	    for (int i = gray.size() - 1; i >= 0; i--) {
	        gray.push_back(gray[i] + (1 << len));
	    }
	}
    return gray;
}

/* ------------------------------ Sort Colors ------------------------------- */
/* Given an array with n objects colored red, white or blue, sort them so that 
   objects of the same color are adjacent, with the colors in the order red, 
   white and blue. Here, we will use the integers 0, 1, and 2 to represent the 
   color red, white, and blue respectively.
   Follow up: A rather straight forward solution is a two-pass algorithm using 
   counting sort. First, iterate the array counting number of 0's, 1's, and 2's,
   then overwrite array with total number of 0's, then 1's and followed by 2's.
   Could you come up with an one-pass algorithm using only constant space? */

// Counting Sort
void sortColors(int A[], int n) {
    int counts[3] = {0};
	for (int i = 0; i < n; i++) {
		counts[A[i]]++;
	}
	int i = 0;
	for (int k = 0; k < 3; k++) {
		for (int j = 0; j < counts[k]; j++) {
			A[i] = k;
			i++;
		}
	}
}

void sortColors(int A[], int n) {
	int i = 0, k = n - 1;
	while (i <= k) {
		while (A[i] == 0) i++;
		while (A[k] == 2) k--;
		bool sorted = true;
		for (int j = i; j <= k; j++) {
			if (A[j] == 0) {
				int temp = A[i];
				A[i] = A[j];
				A[j] = temp;
				i++;
				sorted = false;
			}
			if (A[j] == 2) {
				int temp = A[k];
				A[k] = A[j];
				A[j] = temp;
				k--;
				sorted = false;
			}
		}
		if (sorted) break;
	}
}

// One-pass
void sortColors(int A[], int n) {
    int i = -1, j = -1, k = -1;
	for (int p = 0; p < n; p++) {
		if (A[p] == 0) {
			A[++k] = 2;
			A[++j] = 1;
			A[++i] = 0;
		} else if (A[p] == 1) {
			A[++k] = 2;
			A[++j] = 1;
		} else {
			A[++k] = 2;
		}
	}
}

/* --------------------------- Pascal's Triangle ---------------------------- */
/* Given numRows, generate the first numRows of Pascal's triangle. */

vector<vector<int> > generate(int numRows) {
	    vector<vector<int> > out;
		if (numRows == 0) return out;
		out = {{1}};
		for (int nrow = 1; nrow < numRows; nrow++) {
			vector<int> lastRow = out.back();
			vector<int> newRow (lastRow.size() + 1, 1);
			for (int i = 1; i < newRow.size() - 1; i++) {
				newRow[i] = lastRow[i] + lastRow[i - 1];
			}
			out.push_back(newRow);
		}
		return out;
}

/* -------------------------------- Plus One -------------------------------- */
/* Given a non-negative number represented as an array of digits, plus one to
   the number. The digits are stored such that the most significant digit is at 
   the head of the list. */

vector<int> plusOne(vector<int> &digits) {
	int i = digits.size() - 1;
	while (i >= 0 && digits[i] == 9) i--;
	if (i >= 0) {
		digits[i]++;		
	} else {
		digits.push_back(0);
		digits[0] = 1;
		i++;
	}
	for (++i; i < digits.size(); i++) {
		digits[i] = 0;
	}
	return digits;
}

/* ------------------------------ Rotate Image ------------------------------ */
/* You are given an n x n 2D matrix representing an image.
   Rotate the image by 90 degrees (clockwise).
   Follow up: Could you do this in-place? */

void rotate(vector<vector<int> > &matrix) {
	int n = matrix.size();
	vector<vector<int> > newMatrix = matrix;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			newMatrix[i][j] = matrix[n - 1 - j][i];
		}
	}
	matrix = newMatrix;
}

// In-place
	void rotate(vector<vector<int> > &matrix) {
			int n = matrix.size();
			reverse(matrix.begin(), matrix.end());  // Flip upside down
			// Reflect across main diagonal
			for (int i = 0; i < n; i++) {
				for (int j = i + 1; j < n; j++) {
					// Swap elements
					int temp = matrix[i][j];
					matrix[i][j] = matrix[j][i];
					matrix[j][i] = temp;
				}
			}
	}

// In-place
void rotate(vector<vector<int> > &matrix) {
	int n = matrix.size();
	for (int i = 0; i < n/2; i++) {
		for (int j = i; j < n - 1 -i; j++) {
			int temp = matrix[i][j];
			matrix[i][j] = matrix[n - 1 - j][i];
			matrix[n - 1 - j][i] = matrix[n - 1 - i][n - 1 - j];
			matrix[n - 1 - i][n - 1 - j] = matrix[j][n - 1 - i];
			matrix[j][n - 1 - i] = temp;
		}
	}
}

/* --------------------------- DATE: AUG 16, 2014 --------------------------- */

/* -------------------------- Generate Parentheses -------------------------- */
/* Given n pairs of parentheses, write a function to generate all combinations 
   of well-formed parentheses. */

class Solution {
  public:
	void printPar(int l, int r, string str, vector<string> &out) {
		if (l < 0 || r < l) return;  // invalid state
		if (l == 0 && r == 0) {
			out.push_back(str);  // found one
		} else {
		    // try a left paren, if there are some available
			if (l > 0) printPar(l - 1, r, str + '(', out);
			// try a right paren, if there’s a matching left
			if (r > l) printPar(l, r - 1, str + ')', out);
		}
	}
	vector<string> generateParenthesis(int n) {
	    vector<string> out = vector<string>();
		printPar(n, n, "", out);
		return out;
	}
};
/* ------------------------------ Unique Paths ------------------------------ */
/* A robot is located at the top-left corner of an m * n grid.
   The robot can only move either down or right at any point in time.
   The robot is trying to reach the bottom-right corner of the grid.
   How many possible unique paths are there? */

int uniquePaths(int m, int n) {
	if (m <= 0 || n <= 0) return 0;
	if (m == 1 || n == 1) return 1;
	vector<vector<int> > map(m, vector<int>(n));
	// map = new int *[m];
	// for (int i = 0; i < m; i++) {
	// 	map[i] = new int[n];
	// }
	map[0][0] = 0;
	// Initialize first column to 1's
	for (int i = 1; i < m; i++) map[i][0] = 1;
	// Initialize first row to 1's
	for (int j = 1; j < n; j++) map[0][j] = 1;
	for (int i = 1; i < m; i++) {
		for (int j = 1; j < n; j++) {
			map[i][j] = map[i - 1][j] + map[i][j - 1];
		}
	}
	return map[m - 1][n - 1];
}

/* ------------------------------ Permutations ------------------------------ */
/* Given a collection of numbers, return all possible permutations. */

vector<vector<int> > permute(vector<int> &num) {
	vector<vector<int> > out;
	perm(num, 0, num.size() - 1, out);
	return out;
}
void perm(vector<int> num, int l, int r, vector<vector<int> > &out) {
	// Permute num[l..r]
	if (l == r) {
		out.push_back(num);
	} else {
		for (int i = l; i <= r; i++) {
			int temp = num[i];
			num[i] = num[l];
			num[l] = temp;
			perm(num, l + 1, r, out);
		}
	}
}

/* ------------------ Binary Tree Level Order Traversal II ------------------ */
/* Given a binary tree, return the bottom-up level order traversal of its nodes'
   values. (i.e., from left to right, level by level from leaf to root). */

vector<vector<int> > levelOrderBottom(TreeNode *root) {
	vector<vector<int> > out;
	if (root == NULL) return out;
	queue<TreeNode *> parentQueue;
	parentQueue.push(root);
	parentQueue.push(NULL);
	while (parentQueue.front() != NULL) {
		vector<int> level;
		while (parentQueue.front() != NULL) {
			TreeNode *current = parentQueue.front();
			parentQueue.pop();
			level.push_back(current->val);
			if (current->left != NULL) parentQueue.push(current->left);
			if (current->right != NULL) parentQueue.push(current->right);
		}
		out.push_back(level);
		parentQueue.pop();  // Pop NULL
		parentQueue.push(NULL);
	}
	reverse(out.begin(), out.end());
	return out;
}

/* --------------------------- Search a 2D Matrix --------------------------- */
/* Write an efficient algorithm that searches for a value in an m * n matrix.
   This matrix has the following properties:
   Integers in each row are sorted from left to right. The first integer of each
   row is greater than the last integer of the previous row. */

bool searchMatrix(vector<vector<int> > &matrix, int target) {
    int m = matrix.size(), n = matrix[0].size();
    if (m == 0) return false;
	if (target < matrix[0][0] || target > matrix[m - 1][n - 1]) return false;
	int low = 0, high = m - 1, row;
	while (low <= high) {
		row = low + (high - low) / 2;
		if (target >= matrix[row][0] && target <= matrix[row][n - 1]) {
			break;
		} else if (target < matrix[row][0]) {
			high = row - 1;
		} else {
			low = row + 1;
		}
	}
	// Located correct row
	int left = 0, right = matrix[row].size() - 1, mid;
	while (left <= right) {
		mid = left + (right - left) / 2;
		if (target == matrix[row][mid]) {
			return true;
		} else if (target < matrix[row][mid]) {
			right = mid - 1;
		} else {
			left = mid + 1;
		}
	}
	return false;
}

/* --------------------------- DATE: AUG 17, 2014 --------------------------- */

/* -------------------- Best Time to Buy and Sell Stock --------------------- */
/* Say you have an array in which the i-th element is the price of a given stock
   on day i. If you were only permitted to complete at most one transaction 
   (i.e., buy one and sell one share of the stock), design an algorithm to find 
   the maximum profit. */

int maxProfit(vector<int> &prices) {
	if (prices.size() == 0) return 0;
	int low = prices[0], profit = 0;
	for (int i = 0; i < prices.size(); i++) {
		if (low > prices[i]) {
			low = prices[i];
		}
		if (profit < prices[i] - low) {
			profit = prices[i] - low;
		}
	}
	return profit;
}

/* ---------------------------- Minimum Path Sum ---------------------------- */
/* Given an m * n grid filled with non-negative numbers, find a path from top
   left to bottom right which minimizes the sum of all numbers along its path.
   Note: You can only move either down or right at any point in time. */

int minPathSum(vector<vector<int> > &grid) {
	if (grid.size() == 0) return 0;
	int m = grid.size(), n = grid[0].size();
	int map[m][n];
	map[0][0] = grid[0][0];
	for (int i = 1; i < m; i++) {
		map[i][0] = map[i - 1][0] + grid[i][0];
	}
	for (int j = 1; j < n; j++) {
		map[0][j] = map[0][j - 1] + grid[0][j];
	}
	for (int i = 1; i < m; i++) {
		for (int j = 1; j < n; j++) {
			map[i][j] = min(map[i - 1][j], map[i][j - 1]) + grid[i][j];
		}
	}
	return map[m - 1][n - 1];
}

/* -------------------- Binary Tree Postorder Traversal --------------------- */
/* Given a binary tree, return the postorder traversal of its nodes' values.
   Note: Recursive solution is trivial, could you do it iteratively? */

vector<int> postorderTraversal(TreeNode *root) {
    vector<int> out;
	if (root == NULL) return out;
	stack<TreeNode *> parentStack;
	parentStack.push(root);
	TreeNode *prev = NULL;
	while (!parentStack.empty()) {
		TreeNode *curr = parentStack.top();
		if (prev == NULL || prev->left == curr || prev->right == curr) {
			// Traversing down the tree from the parent
			if (curr->left != NULL) {
				parentStack.push(curr->left);
			} else if (curr->right != NULL) {
				parentStack.push(curr->right);
			}
		} else if (curr->left == prev) {
			// Traversing up the tree from the left
			if (curr->right != NULL) parentStack.push(curr->right);
		} else {
			// Traversing up the tree from the right
			out.push_back(curr->val);
			parentStack.pop();
		}
		prev = curr;
	}
}

// Using two stacks
vector<int> postorderTraversal(TreeNode *root) {
	vector<int> out;
	if (root == NULL) return out;
	stack<TreeNode *> parentStack, outStack;
	parentStack.push(root);
	while (!parentStack.empty()) {
		TreeNode *current = parentStack.top();
		parentStack.pop();
		outStack.push(current);
		if (current->left != NULL) parentStack.push(current->left);
		if (current->right != NULL) parentStack.push(current->right);
	}
	while (!outStack.empty()) {
		TreeNode *temp = outStack.top();
		outStack.pop();
		out.push_back(temp->val);
	}
}

/* ----------------------- Container with Most Water ------------------------ */
/* Given n non-negative integers a_1, a_2, ... , a_n, each represents a point at
   coordinate (i, a_i). n vertical lines are drawn such that the two endpoints
   of line i are at (i, a_i) and (i, 0). Find two lines, which together with the
   x-axis forms a container, such that the container contains the most water.
   Note: You may not slant the container. */

int maxArea(vector<int> &height) {
	int l = 0, r = height.size() - 1, area = 0;
	while (l < r) {
		area = max(area, (r - l) * min(height[l], height[r]));
		if (height[l] < height[r]) {
			l++;
		} else {
			r--;
		}
	}
	return area;
}

/* ----------------------- Linked List Cycle II ------------------------ */
/* Given a linked list, return the node where the cycle begins. If there is no 
   cycle, return NULL. Follow up: Can you solve it without using extra space? */

ListNode *detectCycle(ListNode *head) {
	ListNode *slow = head, *fast = head;
	do {
		if (slow == NULL || fast == NULL || fast->next == NULL) return NULL;
		fast = fast->next->next;
		slow = slow->next;
	} while (slow != fast);
	// List contains cycle
	slow = head;
	while (slow != fast) {
		// Let slow and fast move at same speed
		slow = slow->next;
		fast = fast->next;
	}
	return slow;
}

/* --------------------------- DATE: AUG 18, 2014 --------------------------- */

/* ------------------- Binary Tree Level Order Traversal -------------------- */
/* Given a binary tree, return the level order traversal of its nodes' values. 
   (i.e., from left to right, level by level). */

vector<vector<int> > levelOrder(TreeNode *root) {
	vector<vector<int> > out;
	if (root == NULL) return out;
	queue<TreeNode *> parentQueue;
	parentQueue.push(root);
	parentQueue.push(NULL);
	while (parentQueue.front() != NULL) {
		vector<int> level;
		while (parentQueue.front() != NULL) {
			TreeNode *current = parentQueue.front();
			parentQueue.pop();
			level.push_back(current->val);
			if (current->left != NULL) parentQueue.push(current->left);
			if (current->right != NULL) parentQueue.push(current->right);
		}
		out.push_back(level);
		parentQueue.pop();
		parentQueue.push(NULL);
	}
	return out;
}

/* ----------------------- Set Matrix Zeroes ------------------------ */
/* Given an m * n matrix, if an element is 0, set its entire row and column to 
   0's. Do it in place.
   Follow up: Did you use extra space?
   A straight forward solution using O(m * n) space is probably a bad idea.
   A simple improvement uses O(m + n) space, but is still not the best solution.
   Could you devise a constant space solution? */

// Using O(m + n) space
void setZeroes(vector<vector<int> > &matrix) {
	int m = matrix.size();
	int n = matrix[0].size();
	vector<int> rows(m, 1);
	vector<int> cols(n, 1);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (matrix[i][j] == 0) {
				rows[i] = 0;
				cols[j] = 0;
			}
		}
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (rows[i] == 0 || cols[j] == 0) {
				matrix[i][j] = 0;
			}
		}
	}
}

// Using constant space
void setZeroes(vector<vector<int> > &matrix) {
    int m = matrix.size();
	int n = matrix[0].size();
	bool firstRowZero = false;
	bool firstColZero = false;
	// Check if first column contains zero
	for (int i = 0; i < m; i++) {
		if (matrix[i][0] == 0) {
			firstColZero = true;
			break;
		}
	}
	// Check if first row contains zero
	for (int j = 0; j < n; j++) {
		if (matrix[0][j] == 0) {
			firstRowZero = true;
			break;
		}
	}
	// Find zeroes and store the info in first row and column
	for (int i = 1; i < m; i++) {
		for (int j = 1; j < n; j++) {
			if (matrix[i][j] == 0) {
				matrix[i][0] = 0;
				matrix[0][j] = 0;
			}
		}
	}
	// Set zeroes except first row and column
	for (int i = 1; i < m; i++) {
		for (int j = 1; j < n; j++) {
			if (matrix[i][0] == 0 || matrix[0][j] == 0) {
				matrix[i][j] = 0;
			}
		}
	}
	// Set zeroes for first column if needed
	if (firstColZero) {
		for (int i = 0; i < m; i++) {
			matrix[i][0] = 0;
		}
	}
	// Set zeroes for first row if needed
	if (firstRowZero) {
		for (int j = 0; j < n; j++) {
			matrix[0][j] = 0;
		}
	}
}

/* ---------------------------- Spiral Matrix II ---------------------------- */
/* Given an integer n, generate a square matrix filled with elements from 1 to 
   n^2 in spiral order. */

vector<vector<int> > generateMatrix(int n) {
    vector<vector<int> > matrix(n, vector<int>(n, 0));
	if (n == 0) return matrix;
	for (int d = 0; d <= n/2; d++) {  // Spiral depth
		for (int j = d; j < n - d; j++) {
		    if (j == 0) {
		        matrix[0][0] = 1;
		        continue;
		    }
		    matrix[d][j] = matrix[d][j - 1] + 1;
		}
		for (int i = d + 1; i < n - d; i++) {
			matrix[i][n - d - 1] = matrix[i - 1][n - d - 1] + 1;
		}
		for (int j = n - d - 2; j >= d; j--) {
			matrix[n - d - 1][j] = matrix[n - d - 1][j + 1] + 1;
		}
		for (int i = n - d - 2; i > d; i--) {
			matrix[i][d] = matrix[i + 1][d] + 1;
		}
	}
	return matrix;
}

/* -------------------------------- Path Sum -------------------------------- */
/* Given a binary tree and a sum, determine if the tree has a root-to-leaf path 
   such that adding up all the values along the path equals the given sum. */

bool hasPathSum(TreeNode *root, int sum) {
    if (root == NULL) return false;
    if (root->left == NULL && root->right == NULL) return sum == root->val;
	return hasPathSum(root->left, sum - root->val) || 
		   hasPathSum(root->right, sum - root->val);
}

/* ------------------- Search in Rotated Sorted Array II -------------------- */
/* Follow up for "Search in Rotated Sorted Array":
   What if duplicates are allowed?
   Would this affect the run-time complexity? How and why? 
   Write a function to determine if a given target is in the array. */

bool search(int A[], int n, int target) {
  	int low = 0, high = n - 1;
	while (low <= high) {
		int mid = low + (high - low)/2;
		if (target == A[mid]) return true;
		if (A[low] < A[mid]) {  // Left half is sorted
			if (A[low] <= target && target < A[mid]) {
				high = mid - 1;
			} else {
				low = mid + 1;
			}
		} else if (A[low] > A[mid]) {  // Right half is sorted
			if (A[mid] < target && target <= A[high]) {
				low = mid + 1;
			} else {
				high = mid - 1;
			}
		} else {  // A[low] == A[mid]
			low++;
		}
	}
	return false;
}

/* ----------------- Remove Duplicates from Sorted Array II ----------------- */
/* Follow up for "Remove Duplicates":
   What if duplicates are allowed at most twice? */

int removeDuplicates(int A[], int n) {
		int count = 0;
		for (int i = 0; i < n; i++) {
			if (count == 0 || A[i] != A[count - 2]) {
				A[count] = A[i];
				count++;
			}
		}
		return count;
}

/* -------------------------- Pascal's Triangle II -------------------------- */
/* Given an index k, return the k-th row of Pascal's triangle.
   Note: Could you optimize your algorithm to use only O(k) extra space? */

vector<int> getRow(int rowIndex) {
	vector<int> row (1, 1);
	for (int k = 0; k < rowIndex; k++) {
		row.push_back(1);
		for (int i = 1; i < row.size() - 1; i++) {
			row[i] = row[i] + row[i - 1];
		}
	}
	return row;
}

/* ------------- Populating Next Right Pointers in Each Node II ------------- */
/* Follow up for  "Populating Next Right Pointers in Each Node":
   What if the given tree could be any binary tree? Would your previous solution
   still work? Note: You may only use constant extra space. */

void connect(TreeLinkNode *root) {
TreeLinkNode *curr = root;  // Current node of current level
	TreeLinkNode *head = NULL;  // Head node of next level
	TreeLinkNode *prev = NULL;  // Leading node on next level
	while (curr != NULL) {
		while (curr != NULL) {
			if (curr->left != NULL) {
				(prev ? prev->next : head) = curr->left;
				prev = curr->left;
			}
			if (curr->right != NULL) {
				(prev ? prev->next : head) = curr->right;
				prev = curr->right;
			}
			curr = curr->next;
		}
		// Move to next level
		curr = head;
		head = NULL;
		prev = NULL;
	}
}

/* ------------------------------ Combinations ------------------------------ */
/* Given two integers n and k, return all possible combinations of k numbers 
   out of 1, ... , n. */

// Backtracking
vector<vector<int> > combine(int n, int k) {
	vector<vector<int> > res;
	combinations(n, k, 1, {}, res);
	return res;
}
void combinations(int n, int k, int pos, vector<int> current,
				  vector<vector<int> > &res) {
	if (k == 0) {
		res.push_back(current);
		return;
	}
	for (int i = pos; i <= n; i++) {
	    vector<int> copy = current;
	    copy.push_back(i);
		combinations(n, k - 1, i + 1, copy, res);
	}
}

// Iterative
vector<vector<int> > combine(int n, int k) {
	vector<vector<int> > out;
	if (k == 0) return out;
	for (int i = 1; i <= n; i++) out.push_back({i});
	for (int len = 1; len < k; len++) {
		int num = out.size();
		for (int i = 0; i < num; i++) {
			for (int j = out[i][len - 1] + 1; j <= n; j++) {
				vector<int> current = out[i];
				current.push_back(j);
				out.push_back(current);
			}
		}
		out.erase(out.begin(), out.begin() + num);
	}
	return out;
}

/* --------------------------- DATE: AUG 20, 2014 --------------------------- */

/* ------------------------ Sum Root-to-Leaf Numbers ------------------------ */
/* Given a binary tree containing digits from 0-9 only, each root-to-leaf path 
   could represent a number. Find the total sum of all root-to-leaf numbers. */

// Recursive
int sumNumbers(TreeNode *root) {
    int result = 0;
    preorder(root, 0, result);
    return result;
}
void preorder(TreeNode *root, int temp, int &result) {
    if (root == NULL) return;
    temp = 10 * temp + root->val;
    if (root->left == NULL && root->right == NULL) {
        // Reached leaf node
        result += temp;
    } else {
        preorder(root->left, temp, result);
        preorder(root->right, temp, result);
    }
}

/* ------------------ Removing n-th Node from End of List ------------------- */
/* Given a linked list, remove the n-th node from the end of list and return its
   head. Note: Given n will always be valid. Try to do this in one pass. */

ListNode *removeNthFromEnd(ListNode *head, int n) {
    if (head == NULL) return head;
	ListNode *fast = head, *prev = head;
	for (int i = 0; i < n; i++) {
	    fast = fast->next;
	}
	if (fast == NULL) {
	    // Remove head
	    return head->next;
	} else {
	    fast = fast->next;
	}
	while (fast != NULL) {
		fast = fast->next;
		prev = prev->next;
	}
	ListNode *curr = prev->next;
	prev->next = curr->next;
	delete curr;
	return head;
}

/* ---------------------- Minimum Depth of Binary Tree ---------------------- */
/* Given a binary tree, find its minimum depth, i.e., the number of nodes along 
   the shortest path from the root node down to the nearest leaf node. */

int minDepth(TreeNode *root) {
    if (root == NULL) return 0;
	if (root->left == NULL && root->right == NULL) {
		return 1;
	} else if (root->left == NULL) {
		return 1 + minDepth(root->right);
	} else if (root->right == NULL) {
		return 1 + minDepth(root->left);
	} else {
		return 1 + min(minDepth(root->left), minDepth(root->right));
	}
}

/* -------------------------- Length of Last Word --------------------------- */
/* Given a string s consisting of upper/lower-case alphabets and empty space 
   characters ' ', return the length of the last word in the string. If the last
   word does not exist, return 0.
   Note: A word is defined as a character sequence consisting of non-space 
   characters only. */

int lengthOfLastWord(const char *s) {
	int len = 0;
	while (s[len] != '\0') len++;
	if (len == 0) return 0;  // Empty string
	while (s[len - 1] == ' ') len--;  // Locate last non-space character
	if (len == 0) return 0;  // String only contains spaces
	for (int i = len - 1; i >= 0; i--) {
		if (s[i] == ' ') return len - 1 - i;
	}
	return len;
}

/* --------------------------- Palindrome Number ---------------------------- */
/* Determine whether an integer is a palindrome. Do this without extra space. */

bool isPalindrome(int x) {
	if (x < 0) return false;
	int div = 1;
	while (x / div >= 10) {
		div *= 10;
	}
	while (x != 0) {
		int l = x / div;
		int r = x % 10;
		if (l != r) return false;
		x = (x % div) / 10;
		div /= 100;
	}
	return true;
}

/* --------------------------- DATE: AUG 20, 2014 --------------------------- */

/* -------------------------- Trapping Rain Water --------------------------- */
/* Given n non-negative integers representing an elevation map where the width 
   of each bar is 1, compute how much water it is able to trap after raining. */

int trap(int A[], int n) {
	if (n == 0) return 0;
	int area = 0, block = 0, level = 0, l = 0, r = n - 1, temp;
	while (l <= r) {
		temp = min(A[l], A[r]);
		if (temp > level) {
			area += (temp - level) * (r - l + 1);
			level = temp;
		}
		if (A[l] < A[r]) {
			block += A[l];
			l++;
		} else {
			block += A[r];
			r--;
		}
	}
	return area - block;
}


/* --------------------------- Valid Parentheses ---------------------------- */
/* Given a string containing just the characters '(', ')', '{', '}', '[', ']',
   determine if it is valid. The brackets must close in the correct order; "()" 
   and "()[]{}" are all valid but "(]" and "([)]" are not. */

bool isValid(string s) {
	    stack<char> charStack;
	    for (int i = 0; i < s.length(); i++) {
	        if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
	            charStack.push(s[i]);
	        } else {
	        	if (charStack.empty()) return false;
	        	char temp = charStack.top();
	        	if (s[i] == ')' && temp == '(' ||
	                s[i] == '}' && temp == '{' ||
	                s[i] == ']' && temp == '[') {
	            	charStack.pop();
	        	} else {
	            	return false;
	        	}
	    	}
	    }
	    return charStack.empty();
}

/* ------------------- Flatten Binary Tree to Linked List------------------- */
/* Given a binary tree, flatten it to a linked list in-place.
   Hints: If you notice carefully in the flattened tree, each node's right child
   points to the next node of a pre-order traversal. */

void flatten(TreeNode *root) {
    if (root == NULL) return;
    stack<TreeNode *> parentStack;
    parentStack.push(root);
    while (!parentStack.empty()) {
        TreeNode *current = parentStack.top();
        parentStack.pop();
        if (current->right != NULL) parentStack.push(current->right);
        if (current->left != NULL) parentStack.push(current->left);
        if (!parentStack.empty()) {
            current->left = NULL;
            current->right = parentStack.top();
        } else {
            current->right = NULL;
        }
    }
}

/* ---------------------- Longest Consecutive Sequence ---------------------- */
/* Given an unsorted array of integers, find the length of the longest consecu-
   tive elements sequence. Your algorithm should run in O(n) complexity. */

int longestConsecutive(vector<int> &num) {
	unordered_map<int, int> map;
	int len = 0;
	for (int i = 0; i < num.size(); i++) {
		if (map.count(num[i])) continue;
		int lower = num[i], upper = num[i];
		if (map.count(num[i] - 1)) lower = map[num[i] - 1];
		if (map.count(num[i] + 1)) upper = map[num[i] + 1];
		len = max(len, upper - lower + 1);
		map[num[i]] = num[i];
		map[lower] = upper;
		map[upper] = lower;
	}
	return len;
}

/* --------------------------- DATE: AUG 24, 2014 --------------------------- */

/* ------------------------------ Valid Sudoku ------------------------------ */
/* Determine if a Sudoku is valid, according to the rules:
   Each row must have the numbers 1-9 occuring just once.
   Each column must have the numbers 1-9 occuring just once.
   The numbers 1-9 must occur just once in each of the 9 sub-boxes of the grid.
   The Sudoku board could be partially filled, where empty cells are filled with
   the character '.'.
   Note: A valid Sudoku board (partially filled) is not necessarily solvable.
   Only the filled cells need to be validated. */

bool isValidSudoku(vector<vector<char> > &board) {
    for (int i = 0; i < 9; i++) {
        vector<bool> row (9, false), col (9, false);
        for (int j = 0; j < 9; j++) {
            // Check rows
            if (board[i][j] != '.') {
                if (row[board[i][j] - '1']) return false;
                row[board[i][j] - '1'] = true;
            }
            // Check columns
            if (board[j][i] != '.') {
                if (col[board[j][i] - '1']) return false;
                col[board[j][i] - '1'] = true;
            }
        }
    }
    // Check blocks
    for (int m = 0; m < 3; m++) {
        for (int n = 0; n < 3; n++) {
            vector<bool> block (9, false);
            for (int i = 3*m; i < 3*m + 3; i++) {
                for (int j = 3*n; j < 3*n + 3; j++) {
                    if (board[i][j] != '.') {
                        if (block[board[i][j] - '1']) return false;
                        block[board[i][j] - '1'] = true;
                    }
                }
            }
        }
    }
    return true;
}

/* --------------------------- Search for a Range --------------------------- */
/* Given a sorted array of integers, find the starting and ending position of a 
   given target value. Your algorithm's runtime complexity must be in the order 
   of O(log n). If the target is not found in the array, return [-1, -1]. */

int binarySearch(int A[], int low, int high, int target) {
	while (low <= high) {
		int mid = low + (high - low)/2;
		if (target == A[mid]) {
			return mid;
		} else if (target < A[mid]) {
			high = mid - 1;
		} else {
			low = mid + 1;
		}
	}
	return -1;
}
vector<int> searchRange(int A[], int n, int target) {
	int left, right;
	left = right = binarySearch(A, 0, n - 1, target);
	vector<int> range (2, -1);
	while (left != -1) {
	    range[0] = left;
	    left = binarySearch(A, 0, left - 1, target);
	}
	while (right != -1) {
	    range[1] = right;
	    right = binarySearch(A, right + 1, n - 1, target);
	}
	return range;
}

/* ----------------------------- Count and Say ------------------------------ */
/* The count-and-say sequence is the sequence of integers beginning as follows:
   1, 11, 21, 1211, 111221, ... Given an integer n, generate the n-th sequence.
   Note: The sequence of integers will be represented as a string. */

string countAndSay(int n) {
    if (n == 1) return "1";
    string res = "11";
    for (int k = 2; k < n; k++) {
        string s;
        int count = 1;
        for (int i = 0; i < res.size() - 1; i++) {
            if (res[i] == res[i + 1]) {
                count++;
            } else {
                s += to_string(count) + res[i];
                count = 1;
            }
        }
        // Treat the last character
        int n = res.size() - 1;
        s += (res[n] == res[n - 1] ? to_string(count) : "1") + res[n];
        res = s;
    }
    return res;
}

/* --------------------------- DATE: AUG 31, 2014 --------------------------- */

/* ------------------------------- Jump Game -------------------------------- */
/* Given an array of non-negative integers, you are initially positioned at the 
   first index of the array. Each element in the array represents your maximum 
   jump length at that position. Determine if you are able to reach the last 
   index. */

bool canJump(int A[], int n) {
    int reach = 0;
	for (int i = 0; i <= reach; i++) {
	    if (reach < i + A[i]) reach = i + A[i];
		if (reach >= n - 1) return true; 
	}
	return reach >= n - 1;
}

bool canJump(int A[], int n) {
    int count = 0;
    for (int i = n - 2; i >= 0; i--) {
        A[i] <= count ? count++ : count = 0;
    }
    return count == 0;
}

/* --------------- Convert Sorted List to Binary Search Tree --------------- */
/* Given a singly linked list where elements are sorted in ascending order, 
   convert it to a height balanced BST. */

TreeNode *sortedListToBST(ListNode *head) {
    int len = 0;
    ListNode *curr = head;
    while (curr != NULL) {
        len++;
        curr = curr->next;
    }
    return helper(head, len);
}
TreeNode *helper(ListNode *head, int len) {
    if (len == 0) return NULL;
    ListNode *curr = head;
    for (int i = 0; i < len/2; i++)
        curr = curr->next;
    TreeNode *root = new TreeNode(curr->val);
    root->left = helper(head, len/2);
    root->right = helper(curr->next, len - len/2 - 1);
    return root;
}
