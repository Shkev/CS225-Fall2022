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
    assert(t != nullptr);
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    Node* tmp = t->right;
    t->right = tmp->left;
    tmp->left = t;
    t->height = 1 + std::max(heightOrNeg1(t->right), heightOrNeg1(t->left));
    tmp->height = 1 + std::max(heightOrNeg1(tmp->right), heightOrNeg1(tmp->left));
    t = tmp;
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
    assert(t != nullptr);
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    Node* tmp = t->left;
    t->left = tmp->right;
    tmp->right = t;
    t->height = 1 + std::max(heightOrNeg1(t->right), heightOrNeg1(t->left));
    tmp->height = 1 + std::max(heightOrNeg1(tmp->right), heightOrNeg1(tmp->left));
    t = tmp;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    if (subtree == nullptr) {
        return;
    }
    subtree->height =  1 + std::max(heightOrNeg1(subtree->right), heightOrNeg1(subtree->left));
    int balance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
    if (balance == -2) {
        assert(subtree->left != nullptr);
        int l_balance = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
        if (l_balance == -1) {
            rotateRight(subtree);
        } else {
            rotateLeftRight(subtree);
        }
    } else if (balance == 2) {
        assert(subtree->right != nullptr);
        int r_balance = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
        if (r_balance == -1) {
            rotateRightLeft(subtree);
        } else {
            rotateLeft(subtree);
        }
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    if (subtree == nullptr) {
        subtree = new Node(key, value);
    } else if (key < subtree->key) {
        insert(subtree->left, key, value);
    } else {
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
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            delete subtree;
            subtree = nullptr;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            Node* iop = GetIOP(subtree);
            swap(iop, subtree);
            remove(subtree->left, key);
        } else {
            /* one-child remove */
            Node* child = subtree->left != nullptr ? subtree->left : subtree->right;
            delete subtree;
            subtree = child;
        }
    }
    rebalance(subtree);
}

template <class K, class V>
typename AVLTree<K, V>::Node* AVLTree<K, V>::GetIOP(Node* subtree) {
    if (subtree == nullptr || subtree->left == nullptr) {
        return nullptr;
    }
    Node* iop = subtree->left;
    while (iop->right != nullptr) {
        iop = iop->right;
    }
    return iop;
}