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
  def cum(self, value, root):
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

