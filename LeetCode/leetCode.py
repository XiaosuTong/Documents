#################
##  Defination ##
#################

# Definition for a  binary tree node
class TreeNode:
  def __init__(self, x):
    self.val = x
    self.left = None
    self.right = None
    self.p = None
  def __repr__(self):
    return "node: %s" % self.val

class BinaryTree:
  def __init__(self):
    self.root = None
  def length(self):
    return self.size
  def search(self, k):
    node = self.root
    while node != None:
      if node.val == k:
        return node
      if node.val > k:
        node = node.left
      else :
        node = node.right
    return None
  def minimum(self, node):
    x = None
    while node.left != None:
      x = node.left
      node = node.left
    return x
  def maximum(self, node):
    x = None
    while node.right != None:
      x = node.right
      node = node.right
    return x
  def insert(self, k):
    t = TreeNode(k)
    parent = None
    node = self.root
    while node != None:
      parent = node
      if node.val > t.val:
        node = node.left
      else:
        node = node.right
    t.p = parent
    if parent == None:
      self.root = t
    elif t.val < parent.val:
      parent.left = t
    else:
      parent.right = t
    return t



####################################################################
##                  Valid Binary Search Tree                      ##
####################################################################
##  Given a binary tree, determine if it is a valid binary search tree (BST).
##  Assume a BST is defined as follows:
##   - The left subtree of a node contains only nodes with keys less than the node's key.
##   - The right subtree of a node contains only nodes with keys greater than the node's key.
##   - Both the left and right subtrees must also be binary search trees.

class Solution:
  # @param root, a tree node
  # @return a boolean
  def minmax(self, root, minv, maxv):
    if root == None:
      return True
    else:
      if root.val <= minv or root.val >= maxv:
        return False
      else:
        return self.minmax(root.left, minv, root.val) and self.minmax(root.right, root.val, maxv)
     
  def isValidBST(self, root):
    return self.minmax(root, -float('inf'), float('inf'))


#############################################################
##              Maximum Depth of Binary Tree               ##
#############################################################
##  Given a binary tree, find its maximum depth.
##  The maximum depth is the number of nodes along the longest path from 
##  the root node down to the farthest leaf node. 

class Solution:
  def maxDepth(self, root):
    if root == None:
      return 0
    else :
      return 1 + max(self.maxDepth(root.left), self.maxDepth(root.right))


#############################################################
##               Minimum Depth of Binary Tree              ##
#############################################################
##  Given a binary tree, find its minimum depth.
##  The minimum depth is the number of nodes along the shortest 
##  path from the root node down to the nearest leaf node.

class Solution:
  # @param root, a tree node
  # @return an integer
  def minDepth(self, root):
    if root == None:
      return 0
    if root.left == None and root.right != None:
      return self.minDepth( root.right ) + 1
    if root.left != None and root.right == None:
      return self.minDepth( root.left ) + 1
    return min( self.minDepth( root.left ), self.minDepth( root.right ) ) + 1


#############################################################
##                     Same Tree                           ##
#############################################################
##  Given two binary trees, write a function to check if they are equal or not.
##  Two binary trees are considered equal if they are structurally identical and 
##  the nodes have the same value. 

class Solution:
  # @param p, a tree node
  # @param q, a tree node
  # @return a boolean
  def check(self, p, q):
    if p == None and q == None:
      return True
    elif p == None or q == None:
      return False
    else:
      if p.val != q.val:
        return False
      else:
        return self.check(p.left, q.left) and self.check(p.right, q.right)
  def isSameTree(self, p, q):
    return self.check(p, q)


############################################################
##              Symmetric Tree                            ##
############################################################
##  Given a binary tree, check whether it is a mirror of itself 
##  (ie, symmetric around its center).

class Solution:
  # @param root, a tree node
  # @return a boolean
  def check(self, p, q):
    if p == None and q == None:
      return True
    elif p == None or q == None:
      return False
    else:
      if p.val != q.val:
        return False
      else:
        return self.check(p.left, q.right) and self.check(q.left, p.right)
  def isSymmetric(self, root):
    if root == None:
      return True
    else:
      return self.check(root.left, root.right)


##############################################################
##                   Path Sum                               ##
##############################################################
##  Given a binary tree and a sum, determine if the tree has a 
##  root-to-leaf path such that adding up all the values along the path equals the given sum. 

class Solution:
  # @param root, a tree node
  # @param sum, an integer
  # @return a boolean
  def cum(self, value, root): ## value is the current sum left
    if root == None:
      return False
    elif root.left == None and root.right == None:
      if root.val == value:
        return True
      else:
        return False
    else:
        return self.cum(value-root.val, root.right) or self.cum(value-root.val, root.left)
        ## have to use value-root.val because of negative number also is possible in the tree
  def hasPathSum(self, root, sum):
    if root == None:
      return False
    else:
      return self.cum(sum, root)


###############################################################
##                      Path Sum II                          ##
###############################################################
## Given a binary tree and a sum, find all root-to-leaf paths where 
## each path's sum equals the given sum. 

class Solution:
  # @param root, a tree node
  # @param sum, an integer
  # @return a list of lists of integers
  def pathSum(self, root, Sum):
    if root == None: 
      return []
    else:
      Solution.res = []
      Solution.Sum = Sum
      self.getPath(root, [root.val], root.val)
      return Solution.res
         
  def getPath(self, root, valList, currSum):
    if root.left == None and root.right == None:
      if currSum == Solution.Sum: 
        Solution.res.append(valList)
      return
    if root.left:
      self.getPath(root.left, valList + [root.left.val], currSum + root.left.val)
    if root.right:
      self.getPath(root.right, valList + [root.right.val], currSum + root.right.val)


###########################################################
##           Binary Tree Level Order Traversal           ##
###########################################################
##  Given a binary tree, return the level order traversal of its 
##  nodes' values. (ie, from left to right, level by level).

class Solution:
  # @param root, a tree node
  # @return a list of lists of integers
  def order(self, root, level):  ## level is the depth of previous node
    if root != None:
      if len(Solution.rst) < level+1:  ##  level+1 is the current level idx
        Solution.rst.append([])
      Solution.rst[level].append(root.val)
      self.order(root.left, level+1)  ## pass the next level of node with the corrent level idx
      self.order(root.right, level+1)  ## order of left child first then right child is matter
  def levelOrder(self, root):
    Solution.rst = []
    if root == None:
      return []
    else:
      self.order(root, 0)
      return Solution.rst


##############################################################
##          Binary Tree Level Order Traversal II            ##
##############################################################
##  Given a binary tree, return the bottom-up level order traversal of its 
##  nodes' values. (ie, from left to right, level by level from leaf to root).   

class Solution:
  # @param root, a tree node
  # @return a list of lists of integers
  def order(self, root, level):  ## level is the depth of previous node
    if root != None:
      if len(Solution.rst) < level+1:  ##  level+1 is the current level idx
        Solution.rst.append([])
      Solution.rst[level].append(root.val)
      self.order(root.left, level+1)  ## pass the next level of node with the corrent level idx
      self.order(root.right, level+1)  ## order of left child first then right child is matter
  def levelOrder(self, root):
    Solution.rst = []
    if root == None:
      return []
    else:
      self.order(root, 0)
      return Solution.rst[::-1]


###############################################################
##                Reverse Words in a String                  ##
###############################################################
##  Given an input string, reverse the string word by word.
##  For example,
##  Given s = "the sky is blue",
##  return "blue is sky the". 

##  What constitutes a word?
##   - A sequence of non-space characters constitutes a word.
##  Could the input string contain leading or trailing spaces?
##   - Yes. However, your reversed string should not contain leading or trailing spaces.
##  How about multiple spaces between two words?
##   - Reduce them to a single space in the reversed string.

class Solution:
  # @param s, a string
  # @return a string
  def reverseWords(self, s):
    Solution.rst = ""
    Solution.word = ""
    for ch in s:
      if ch != ' ':
        Solution.word += ch
      if ch == ' ':
        if len(Solution.word) != 0:
          if Solution.rst != '':
            Solution.rst = ' ' + Solution.rst 
          Solution.rst = Solution.word + Solution.rst
          Solution.word = ""
    if len(Solution.word) != 0:
      if Solution.rst != '':
        Solution.rst = ' ' + Solution.rst
      Solution.rst = Solution.word + Solution.rst
    return Solution.rst


################################################################
##                  Balanced Binary Tree                      ##
################################################################
##  Given a binary tree, determine if it is height-balanced.
##  For this problem, a height-balanced binary tree is defined as a binary tree in 
##  which the depth of the two subtrees of every node never differ by more than 1. 

class Solution:  
  # @param root, a tree node  
  # @return a boolean  
  def depth(self,root):  
    if root == None:
      return 0
    else :
      return 1 + max(self.depth(root.left), self.depth(root.right))
  def isBalanced(self, root):  
    if root==None:  
      return True  
    if abs(self.depth(root.left) - self.depth(root.right))>1:  
      return False  
    else:  
      return self.isBalanced(root.left) and self.isBalanced(root.right) 


###############################################################
##                       Single NUmber                       ##
###############################################################
##  Given an array of integers, every element appears twice except for one. 
##  Find that single one. 

class Solution:
  # @param A, a list of integer
  # @return an integer
  def singleNumber(self, A):
    l = len(A)
    x = A[0]
    if l == 1:
      return x
    else:
      for i in range(1,l):
        x ^= A[i]
      return x


################################################################
##                      Reverse Integer                       ##
################################################################
##  Reverse digits of an integer.
##  321 => 123
class Solution:
  # @return an integer
  def reverse(self, x):
    Solution.rst = 0
    target = str(abs(x))
    l = len(target)
    for i in range(l):
      Solution.rst += int(target[i])*(10**i)
    if abs(Solution.rst) > 2**31 - 1: 
      Solution.rst = 0
    if x >= 0:
      return Solution.rst
    else:
      return -Solution.rst


###############################################################
##              Binary Tree Inorder Traversal                ##
###############################################################
##  Given a binary tree, return the inorder traversal of its nodes' values.

class Solution:
  # @param root, a tree node
  # @return a list of integers
  def second(self, root):
    if root != None:
      self.second(root.left)
      Solution.rst.append(root.val)
      self.second(root.right)
  def inorderTraversal(self, root):
    Solution.rst = []
    self.second(root)
    return Solution.rst

## itertively:
class Solution:
  # @param root, a tree node
  # @return a list of integers
  def inorderTraversal(self, root):
    stack = []
    node = root
    rst = []
    while node != None or len(stack) > 0:
      if node != None:
        stack.append(node)
        node = node.left
      else:
        node = stack.pop()
        rst.append(node.val)
        node = node.right
    return rst


###############################################################
##               Binary Tree Preorder Traversal              ##
###############################################################
##  Given a binary tree, return the preorder traversal of its nodes' values.

class Solution:
  # @param root, a tree node
  # @return a list of integers
  def second(self, root):
    if root != None:
      Solution.rst.append(root.val)
      self.second(root.left)
      self.second(root.right)
  def preorderTraversal(self, root):
    Solution.rst = []
    self.second(root)
    return Solution.rst

## itertively:
class Solution:
  # @param root, a tree node
  # @return a list of integers
  def preorderTraversal(self, root):
    stack = []
    rst = []
    node = root
    while len(stack) > 0 or node != None:
      if node != None:
        rst.append(node.val)
        stack.append(node)
        node = node.left
      else:
        node = stack.pop().right
    return rst


#####################################################
##                 Roman to Integer                ##
#####################################################
##  Given a roman numeral, convert it to an integer.
##  Input is guaranteed to be within the range from 1 to 3999.

class Solution:
  # @return an integer
  def romanToInt(self, s):
    pre = ' '
    num = 0      
    for i in s:
      if i == "I":
        num += 1
      elif i == "V":
        if pre == "I":
          num += (4-1)
        else:
          num += 5
      elif i == "X":
        if pre == "I":
          num += (9-1)
        else:
          num += 10
      elif i == "L":
        if pre == "X":
          num += (40-10)
        else:
          num += 50
      elif i == "C":
        if pre == "X":
          num += (90-10)
        else:
          num += 100
      elif i == "D":
        if pre == "C":
          num += (400-100)
        else:
          num += 500
      elif i == "M":
        if pre == "C":
          num += (900-100)
        else:
          num += 1000
      pre = i
    return num


####################################################
##                    Plus One                    ##
####################################################

class Solution:
  # @param digits, a list of integer digits
  # @return a list of integer digits
  def plusOne(self, digits):
    length = len(digits)
    f = 1
    for i in range(length, 0, -1):
      digits[i-1] = digits[i-1] + f
      if digits[i-1] < 10:
        f = 0
      else:
        digits[i-1] = 0
        f = 1
    if sum(digits) == 0:
      digits = [1] + digits
    return digits


####################################################
##                  Rotate Array                  ##
####################################################
##  Rotate an array of n elements to the right by k steps.
##  For example, with n = 7 and k = 3, the array [1,2,3,4,5,6,7] is rotated 
##  to [5,6,7,1,2,3,4]. 
class Solution:
  # @param nums, a list of integer
  # @param k, num of steps
  # @return nothing, please modify the nums list in-place.
  def rotate(self, nums, k):
    length = len(nums)
    for i in range(0, k):
      b = nums[-1]
      for j in range(length-1, 0, -1):
        nums[j] = nums[j-1]
      nums[0] = b

class Solution:
  # @param nums, a list of integer
  # @param k, num of steps
  # @return nothing, please modify the nums list in-place.
  def rotate(self, nums, k):
    length = len(nums)
    if length < k:
      k = k - length
    tmp = nums[(length-k):length]
    nums[k:length] = nums[0:(length-k)]
    nums[0:k] = tmp


#####################################################
##                Remove Element                   ##
#####################################################
##  Given an array and a value, remove all instances of that value in place and return the new length.
##The order of elements can be changed. It doesn't matter what you leave beyond the new length

class Solution:
  # @param    A       a list of integers
  # @param    elem    an integer, value need to be removed
  # @return an integer
  def removeElement(self, A, elem):
    length = len(A)
    idx = length -1
    for i in range(length-1,-1,-1):
      if A[i] == elem:
        A[i] = A[idx]
        A[idx] = elem
        idx -= 1
    return idx+1


######################################################
##                   Two Sum                        ##
######################################################
##  Given an array of integers, find two numbers such that they add up to a specific target number.
##
##  The function twoSum should return indices of the two numbers such that they add up to the target, 
##  where index1 must be less than index2. Please note that your returned answers (both index1 and index2) are not zero-based.
##
##  You may assume that each input would have exactly one solution.
##
##  Input: numbers={2, 7, 11, 15}, target=9
##  Output: index1=1, index2=2 

class Solution:
  # @return a tuple, (index1, index2)
  def twoSum(self, num, target):
    index = []
    numsort = num[:]
    numsort.sort()
    i = 0
    j = len(numsort) - 1
    while i < j:
      if numsort[i] + numsort[j] == target:
        for k in range(0, len(num)):
          if num[k] == numsort[i]:
            index.append(k)
            break
        for k in range(len(num)-1,-1,-1):
          if num[k] == numsort[j]:
            index.append(k)
            break
        index.sort()
        break
      elif numsort[i] + numsort[j] > target:
        j -= 1
      else:
        i += 1
    return (index[0]+1, index[1]+1)


class Solution:
  # @return a tuple, (index1, index2)
  def twoSum(self, num, target):
    dic = {}
    for i in range(0, len(num)):
      x = num[i]
      if target-x in dic:
        return (dic[target-x]+1, i+1)
      else:
        dic[x] = i
  
######################################################
##        Remove Duplicates from Sorted Array       ##
######################################################
##  Given a sorted array, remove the duplicates in place such that each element 
##  appear only once and return the new length.
##
##  Do not allocate extra space for another array, you must do this in place with constant memory.
##
##  For example,
##  Given input array A = [1,1,2],
##  Your function should return length = 2, and A is now [1,2]. 

class Solution:
  # @param a list of integers
  # @return an integer
  def removeDuplicates(self, A):
    if A == []:
      return 0
    else:
      slow = 0
      for fast in range(len(A)):
        if A[slow] == A[fast]:
          continue
        else:
          slow += 1
          A[slow] = A[fast]
      return slow + 1


######################################################
##      Remove Duplicates from Sorted Array II      ##
######################################################
##  Follow up for "Remove Duplicates":
##  What if duplicates are allowed at most twice?
##
##  For example,
##  Given sorted array A = [1,1,1,2,2,3],
##  Your function should return length = 5, and A is now [1,1,2,2,3]. 

class Solution:
  # @param A a list of integers
  # @return an integer
  def removeDuplicates(self, A):
    if A == []:
      return 0
    elif len(A) <= 2:
      return len(A)
    else:
      slow = 0
      time = 0
      for fast in range(len(A)):
        if A[slow] == A[fast]:
          time += 1
          if time == 2:
            slow += 1
            A[slow] = A[fast]
        else:
          slow += 1
          A[slow] = A[fast]
          time = 1
      return slow + 1


####################################################
##          Merge Sorted Array                    ##
####################################################
##  Given two sorted integer arrays A and B, merge B into A as one sorted array.

##  You may assume that A has enough space (size that is greater or equal to m + n) 
##  to hold additional elements from B. The number of elements initialized in A and B are m and n respectively.

class Solution:
  # @param A  a list of integers
  # @param m  an integer, length of A
  # @param B  a list of integers
  # @param n  an integer, length of B
  # @return nothing(void)
  def merge(self, A, m, B, n):
    tmp = [0 for i in range(m+n)]
    i = 0
    j = 0
    k = 0
    while i < m and j < n:
      if A[i] <= B[j]:
        tmp[k] = A[i]
        i += 1
      else:
        tmp[k] =  B[j]
        j += 1
      k += 1
    if i == m:
      tmp[k:(m+n)] = B[j:n]
    if j == n:
      tmp[k:(m+n)] = A[i:m]
    A[:] = tmp[:]


####################################################
##     Best Time to Buy and Sell Stock            ##
####################################################
## Say you have an array for which the ith element is the price of a given stock on day i.

## If you were only permitted to complete at most one transaction (ie, buy one and sell one
## share of the stock), design an algorithm to find the maximum profit.    

class Solution:
  # @param prices, a list of integer
  # @return an integer
  def maxProfit(self, prices):
    if len(prices) == 0:
      return 0
    else:
      maxProfit = 0
      lowPrice = prices[0]
      for i in range(len(prices)):
        if prices[i] < lowPrice:
          lowPrice = prices[i]
        maxProfit = max(maxProfit, prices[i]-lowPrice)
      return maxProfit


#####################################################
##    Best Time to Buy and Sell Stock II           ##
#####################################################
## Say you have an array for which the ith element is the price of a given stock on day i.
##
## Design an algorithm to find the maximum profit. You may complete as many transactions 
## as you like (ie, buy one and sell one share of the stock multiple times). However, you 
## may not engage in multiple transactions at the same time (ie, you must sell the stock 
##  before you buy again).

class Solution:
  # @param prices, a list of integer
  # @return an integer
  def maxProfit(self, prices):
    profit = 0
    for i in range(1, len(prices)):
      if prices[i] > prices[i-1]:
        profit += prices[i] - prices[i-1]
    return profit


#####################################################
##                Majority Element                 ##
##################################################### 
##  Given an array of size n, find the majority element. The majority element is the element 
##  that appears more than ⌊ n/2 ⌋ times.
##
##  You may assume that the array is non-empty and the majority element always exist in the array.
class Solution:
  # @param num, a list of integers
  # @return an integer
  def majorityElement(self, num):
    rst = 0
    freq = 0
    for i in num:
      if freq == 0:
        rst = i
        freq += 1
      else:
        if rst == i:
          freq += 1
        else:
          freq -= 1
    return rst
        

#####################################################
##              Nth Fibonacci number               ##
#####################################################

class Solution:
  def fibona(self, n):
    if n == 0:
      return None
    if n == 1 or n == 2:
      return 1
    else:
      fib = 0
      first = 1
      second = 1
      for i in range(n-2):
        fib = first + second
        first = second
        second = fib
    return fib


#####################################################
##             Valid Parentheses                   ##
#####################################################
## Given a string containing just the characters '(', ')', '{', '}', '[' and ']', 
## determine if the input string is valid.
##
## The brackets must close in the correct order, "()" and "()[]{}" are all valid 
## but "(]" and "([)]" are not.
  
class Solution:
  # @return a boolean
  def isValid(self, s):
    stack = []
    for i in range(len(s)):
      if s[i] == '(' or s[i] == '[' or s[i] == '{':
        stack.append(s[i])
      if s[i] == ')':
        if stack == [] or stack.pop() != '(':
          return False
      if s[i] == ']':
        if stack == [] or stack.pop() != '[':
          return False
      if s[i] == '}':
        if stack == [] or stack.pop() != '{':
          return False
    if stack:
      return False
    else:
      return True


#####################################################
##               Excel Sheet Column Number         ##
#####################################################
## Given a column title as appear in an Excel sheet, return its corresponding column number.
## 
## For example:
##
##    A -> 1
##    B -> 2
##    C -> 3
##    ...
##    Z -> 26
##    AA -> 27
##    AB -> 28 

import re

class Solution:
  # @param s, a string
  # @return an integer
  def titleToNumber(self, s):
    string = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    idx = 1
    num = 0
    for i in s[::-1]:
      num = num + (26**(idx-1))*(re.search(i, string).start()+1)
      idx += 1
    return num



      
        









#####################################################
##                 ZigZag Conversion               ##
#####################################################
##  The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows 
##  like this: (you may want to display this pattern in a fixed font for better legibility)
##
##  P   A   H   N (0, 4, 8, 12)  #0
##  A P L S I I G (1, 3, 5, 7, ) #1
##  Y   I   R     (2, 6, 10,)    #2
##
##  And then read line by line: "PAHNAPLSIIGYIR"
##  Write the code that will take a string and make this conversion given a number of rows: 

class Solution:
  # @return a string
  def convert(self, s, nRows):
    mylist = []
    length = len(s)
    for i in range(nRows):
      j = i
      while j <= length:
        mylist.append(s[j])