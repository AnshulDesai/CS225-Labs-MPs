/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
    template <typename T>
void BinaryTree<T>::mirror()
{
    if (root == NULL) {
      return;
    }
    mirror(root);
}
/**
* Helper Function
* @param subRoot
*/

template <typename T>
void BinaryTree<T>::mirror(Node * subRoot) {
  if (subRoot == NULL) {
    return;
  }
  Node * temp = subRoot -> right;
  subRoot -> right = subRoot -> left;
  subRoot -> left = temp;
  mirror(subRoot -> right);
  mirror(subRoot -> left);
}
/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
  stack<T> check;
  int mark;
  InorderTraversal<int> temp(root);
  //pushes all items into a stack
  for (TreeTraversal<int>::Iterator ctr = temp.begin(); ctr != temp.end(); ++ctr) {
    check.push((*ctr) -> elem);
  }
  if (check.empty() == true) {
    return true;
  }
  //places the mark as the greatest element "in theory"
  else {
    mark = check.top();
    check.pop();
  }
  //loop to check if it is in order
  while (check.empty() == false) {
    if (mark < check.top()) {
      return false;
    }
    mark = check.top();
    check.pop();
  }
  return true;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    // your code here
    return isOrderedHelper(root);
}
/**
*@param subroot
* @return bool
*/
template <typename T>
bool BinaryTree<T>::isOrderedHelper(Node * subroot) const {
  if (subroot -> right == NULL && subroot -> left == NULL) {
    return true;
  }
  if (subroot -> left == NULL) {
    if (subroot -> right -> elem < subroot -> elem) {
      return false;
    }
    return isOrderedHelper(subroot -> right);
  }
  else if (subroot -> right == NULL) {
    if (subroot -> left -> elem > subroot -> elem) {
      return false;
    }
    return isOrderedHelper(subroot -> left);
  }
  else {
    if (subroot -> left -> elem > subroot -> elem) {
      return false;
    }
    if (subroot -> right -> elem < subroot -> elem) {
      return false;
    }
    return (isOrderedHelper(subroot -> left) && isOrderedHelper(subroot -> right));
  }
}
/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::getPaths(vector<vector<T> > &paths) const
{
    // your code here
    vector<T> boonk;
    getPathHelper(root, paths, boonk);
}

/**
* @param yikes
* @param paths
* @param boonk
*/
template <typename T>
void BinaryTree<T>::getPathHelper(Node * yikes, vector<vector<T>> &paths, vector<T> boonk) const {
  if (yikes == NULL)
    return;
  if (yikes -> left == NULL && yikes -> right == NULL){
    boonk.push_back(yikes -> elem);
    paths.push_back(boonk);
    return;
  }
  boonk.push_back(yikes -> elem);
  if (yikes -> left != NULL) {
    getPathHelper(yikes -> left, paths, boonk);
  }
  if (yikes -> right != NULL) {
    getPathHelper(yikes -> right, paths, boonk);
  }
}

/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    return sumHelper(root, 0);
}

template <typename T>
int BinaryTree<T>::sumHelper(Node * subRoot, int dist) const {
  if (subRoot == NULL) {
    return 0;
  }
  return dist + sumHelper(subRoot -> left, dist + 1) + sumHelper(subRoot -> right, dist + 1);
}
