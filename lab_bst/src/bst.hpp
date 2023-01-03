/**
 * @file bst.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V BST<K, V>::find(const K& key)
{
    Node*& found_node = find(root, key);
    return found_node->value;
}

template <class K, class V>
struct BST<K, V>::Node*& BST<K, V>::find(Node*& subtree, const K& key)
{
    if (subtree == nullptr) {
        return subtree;
    }
    if (key < subtree->key) {
        return find(subtree->left, key);
    }
    if (key > subtree->key) {
        return find(subtree->right, key);
    }
    return subtree;
}

template <class K, class V>
void BST<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void BST<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    Node*& new_node_ptr = find(subtree, key);
    if (new_node_ptr != nullptr) { // node already exists with given key
        return;
    }
    new_node_ptr = new Node(key, value);
}

template <class K, class V>
void BST<K, V>::swap(Node*& first, Node*& second)
{
    std::swap(first->key, second->key);
    std::swap(first->value, second->value);
}

template <class K, class V>
void BST<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void BST<K, V>::remove(Node*& subtree, const K& key)
{
    Node*& node_rem = find(subtree, key);
    if (node_rem == nullptr) return;
    if (node_rem->HasNoChildren()) {
        DeleteNode(node_rem);
    } else if (node_rem->HasOneChild()) {
        Node*& child = node_rem->left != nullptr ? node_rem->left : node_rem->right;
        Node* tmp = node_rem;
        node_rem = child;
        DeleteNode(tmp);
    } else if (node_rem->HasTwoChildren()) {
        Node* iop = FindIOP(node_rem);
        if (iop == nullptr) return;
        swap(node_rem, iop);
        remove(node_rem->left, key);
    }
}

template <class K, class V>
struct BST<K, V>::Node* BST<K, V>::FindIOP(Node* node) {
    if (node == nullptr || node->left == nullptr) return nullptr;
    Node* curr = node->left;
    while (curr->right != nullptr) {
        curr = curr->right;
    }
    return curr;
}

template <class K, class V>
void BST<K, V>::DeleteNode(Node*& node) {
    delete node;
    node = nullptr;
}

template <class K, class V>
BST<K, V> listBuild(std::vector<std::pair<K, V>> inList){
    BST<K, V> bst;
    for (std::pair<K, V> p : inList) {
        K key;
        V value;
        std::tie(key, value) = p;
        bst.insert(key, value);
    }
    return bst;
}

template <class K, class V>
std::vector<int> allBuild(std::vector<std::pair<K, V>> inList){
    std::vector<int> hist(inList.size(), 0);
    std::sort(inList.begin(), inList.end());
    do {
        BST<K, V> bst = listBuild(inList);
        int height = bst.height();
        hist.at(height)++;
    } while (std::next_permutation(inList.begin(), inList.end()));

    return hist;
}