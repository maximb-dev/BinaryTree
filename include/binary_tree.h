#pragma once

#include <iostream>
#include <memory>
#include <functional>
#include <sstream>
#include <algorithm>

namespace BinaryTree {

    template<typename T>
    class Node {
    public:
        T data;
        std::unique_ptr<Node<T>> left, right;
        explicit Node(T val) : data(val) {}
    };

    template<typename T>
    class Tree {
    private:
        std::unique_ptr<Node<T>> root;

        int height(const std::unique_ptr<Node<T>>& node) const {
            return node ? 1 + std::max(height(node->left), height(node->right)) : 0;
        }

        int getBalance(const std::unique_ptr<Node<T>>& node) const {
            return node ? height(node->left) - height(node->right) : 0;
        }

        std::unique_ptr<Node<T>> rotateRight(std::unique_ptr<Node<T>> y) {
            auto x = std::move(y->left);
            y->left = std::move(x->right);
            x->right = std::move(y);
            return x;
        }

        std::unique_ptr<Node<T>> rotateLeft(std::unique_ptr<Node<T>> x) {
            auto y = std::move(x->right);
            x->right = std::move(y->left);
            y->left = std::move(x);
            return y;
        }

        void balance(std::unique_ptr<Node<T>>& node) {
            int bf = getBalance(node);
            if (bf > 1) {
                if (getBalance(node->left) < 0) node->left = rotateLeft(std::move(node->left));
                node = rotateRight(std::move(node));
            } else if (bf < -1) {
                if (getBalance(node->right) > 0) node->right = rotateRight(std::move(node->right));
                node = rotateLeft(std::move(node));
            }
        }

        void insert(std::unique_ptr<Node<T>>& node, T val) {
            if (!node) node = std::make_unique<Node<T>>(val);
            else if (val < node->data) insert(node->left, val);
            else if (val > node->data) insert(node->right, val);
            balance(node);
        }

        std::unique_ptr<Node<T>> remove(std::unique_ptr<Node<T>>& node, T val) {
            if (!node) return nullptr;
            if (val < node->data) node->left = remove(node->left, val);
            else if (val > node->data) node->right = remove(node->right, val);
            else {
                if (!node->left) return std::move(node->right);
                if (!node->right) return std::move(node->left);
                Node<T>* minNode = findMin(node->right.get());
                node->data = minNode->data;
                node->right = remove(node->right, minNode->data);
            }
            balance(node);
            return std::move(node);
        }

        Node<T>* findMin(Node<T>* node) const {
            while (node->left) node = node->left.get();
            return node;
        }

        bool search(const std::unique_ptr<Node<T>>& node, T val) const {
            if (!node) return false;
            if (val == node->data) return true;
            return val < node->data ? search(node->left, val) : search(node->right, val);
        }

        void inorder(const std::unique_ptr<Node<T>>& node, const std::function<void(T)>& visit) const {
            if (!node) return;
            inorder(node->left, visit);
            visit(node->data);
            inorder(node->right, visit);
        }

        void serialize(const std::unique_ptr<Node<T>>& node, std::ostringstream& out) const {
            if (!node) { out << "# "; return; }
            out << node->data << " ";
            serialize(node->left, out);
            serialize(node->right, out);
        }

        std::unique_ptr<Node<T>> deserialize(std::istringstream& in) {
            std::string val;
            in >> val;
            if (val == "#") return nullptr;
            auto node = std::make_unique<Node<T>>(static_cast<T>(std::stoi(val)));
            node->left = deserialize(in);
            node->right = deserialize(in);
            return node;
        }

    public:
        void insert(T val) { insert(root, val); }
        void remove(T val) { root = remove(root, val); }
        bool search(T val) const { return search(root, val); }
        void inorder(const std::function<void(T)>& visit) const { inorder(root, visit); }
        std::string serialize() const { std::ostringstream out; serialize(root, out); return out.str(); }
        void deserialize(const std::string& data) { std::istringstream in(data); root = deserialize(in); }
    };

}