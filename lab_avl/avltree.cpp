/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node * new_top = t->right;
    t->right = new_top->left;
    new_top->left = t;
    t->height = std::max(heightOrNeg1(t->left), heightOrNeg1(t->right)) + 1;
    t = new_top;
    t->height = std::max(heightOrNeg1(t->right), heightOrNeg1(t->left)) + 1;

}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node * new_top = t->left;
    t->left = new_top->right;
    new_top->right = t;
    t->height = std::max(heightOrNeg1(t->left), heightOrNeg1(t->right)) + 1;
    t = new_top;
    t->height = std::max(heightOrNeg1(t->right), heightOrNeg1(t->left)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if (subtree == NULL) { return; }
    int q = balancefactor(subtree);
    if (q == 2){
        if (balancefactor(subtree->right) > 0){
            rotateLeft(subtree);
        }
        else{
            rotateRightLeft(subtree);
        }
    }
    if (q == -2){
        if (balancefactor(subtree->left) < 0){
            rotateRight(subtree);
        }
        else{
            rotateLeftRight(subtree);
        }
    }
    subtree->height = 1 + std::max(heightOrNeg1(subtree->right), heightOrNeg1(subtree->left));
}

//helper function
template <class K, class V>
int AVLTree<K, V>::balancefactor(Node* subtree)
{
    return heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(subtree == NULL){
      subtree = new Node(key, value);
    }
    else if(key < subtree->key){
      insert(subtree->left, key, value);
    }
    else{
      insert(subtree->right, key, value);
    }
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
        //rebalance(subtree);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
        //rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node * child = subtree->left;
            while (child->right != NULL) {
                child = child->right;
            }
            swap(subtree, child);
            remove(subtree->left, key);
            rebalance(child);
        } else {
            /* one-child remove */
            // your code here
            Node * temp = (subtree->left != NULL) ? subtree->left: subtree->right;
            delete subtree;
            subtree = temp;
        }
        // your code here
    }
    rebalance(subtree);
}
