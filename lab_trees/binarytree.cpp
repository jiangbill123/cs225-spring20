/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>
#include <limits.h>

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
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
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
    std::cout << std::endl;
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
    std::cout << subRoot->elem << ' ';

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
    //your code here
    if (root == NULL) { return; }
    mirror(root);
    return;
}

 template <typename T>
void BinaryTree<T>::mirror(Node* root){
    //base
    if (root->left == NULL && root->right == NULL) { return; }

    Node * temp = root->left;
    root->left = root->right;
    root->right = temp;
    if (root->right != NULL) { mirror(root->right); }
    if (root->left != NULL) {mirror(root->left); }
    return;
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
    //your code here
    InorderTraversal<int> iot(root);
    T temp;
    bool flag = true;
    for (typename TreeTraversal<T>::Iterator iter = iot.begin(); iter != iot.end(); ++iter ){
        if (flag){
            temp = (*iter)->elem;
            flag = false;
        }
        else if ((*iter)->elem < temp){
            return false;
        }
        else{
            temp = (*iter)->elem;
        }

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
    //return false;
    return isOrderedRecursive(this->getRoot(), INT_MIN, INT_MAX);
}

template <typename T>
bool BinaryTree<T>::isOrderedRecursive(Node * subRoot, int min, int max) const {
    //base
    if (subRoot == NULL){
        return true;
    }

    if ( (subRoot->elem <= min) || (subRoot->elem > max)){
        return false;
    }
    //RULE for BST: for a given subroot, any values on the left subtree is less than the subroot value
    //              AND any values on the right subtree is larger than the value of the subroot
    return isOrderedRecursive(subRoot->left, min, subRoot->elem) && isOrderedRecursive(subRoot->right, subRoot->elem, max);
}

