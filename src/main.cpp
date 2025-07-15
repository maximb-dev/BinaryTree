#include "../include/binary_tree.h"
#include <iostream>

int main() {
    BinaryTree::Tree<int> tree;

    // Вставка значений
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(13);
    tree.insert(17);

    // Обход дерева (in-order)
    std::cout << "In-order traversal: ";
    tree.inorder([](int val) {
        std::cout << val << " ";
    });
    std::cout << std::endl;

    // Поиск
    std::cout << "Searching for 13: ";
    std::cout << (tree.search(13) ? "Found" : "Not found") << std::endl;

    // Удаление
    tree.remove(10);
    std::cout << "After deleting 10: ";
    tree.inorder([](int val) {
        std::cout << val << " ";
    });
    std::cout << std::endl;

    // Сериализация
    std::string serialized = tree.serialize();
    std::cout << "Serialized tree: " << serialized << std::endl;

    // Десериализация
    BinaryTree::Tree<int> restored;
    restored.deserialize(serialized);
    std::cout << "Restored tree (in-order): ";
    restored.inorder([](int val) {
        std::cout << val << " ";
    });
    std::cout << std::endl;

    return 0;
}