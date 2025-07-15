# Binary Tree in C++

A simple and modern C++ implementation of a self-balancing binary search tree (AVL Tree). This API supports insertion, deletion, search, in-order traversal, and serialization/deserialization.
# Features

✅ Insertion and deletion with automatic balancing

🔍 Value search

🌿 In-order traversal using lambdas

🧵 Serialization and deserialization (e.g. for saving/loading trees)

# Example

    #include "binary_tree.h"
    #include <iostream>
    
    int main() {
    BinaryTree::Tree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);

    tree.inorder([](int val) {
        std::cout << val << " ";
    });

    if (tree.search(15)) {
        std::cout << "\nFound 15";
    }

    std::string data = tree.serialize();
    BinaryTree::Tree<int> restored;
    restored.deserialize(data);

    return 0;
}

# Serialization Format

Serialization converts the tree into a string (pre-order traversal), using # for null pointers. Example:

    10 5 # # 15 # #

This is useful for saving and loading trees.