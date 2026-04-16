#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

template <typename K, typename V>
struct AVLNode {
    K key;
    V value;
    int height;
    AVLNode* left;
    AVLNode* right;

    AVLNode(K k, V v) : key(k), value(v), height(1), left(nullptr), right(nullptr) {}
};

template <typename K, typename V>
class AVLTree {
private:
    AVLNode<K, V>* root;

    int height(AVLNode<K, V>* node) const {
        if (node == nullptr) return 0;
        return node->height;
    }

    int getBalance(AVLNode<K, V>* node) const {
        if (node == nullptr) return 0;
        return height(node->left) - height(node->right);
    }

    AVLNode<K, V>* rightRotate(AVLNode<K, V>* y) {
        AVLNode<K, V>* x = y->left;
        AVLNode<K, V>* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = std::max(height(y->left), height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;

        return x; 
    }
    AVLNode<K, V>* leftRotate(AVLNode<K, V>* x) {
        AVLNode<K, V>* y = x->right;
        AVLNode<K, V>* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = std::max(height(x->left), height(x->right)) + 1;
        y->height = std::max(height(y->left), height(y->right)) + 1;

        return y;
    }

    AVLNode<K, V>* insertHelper(AVLNode<K, V>* node, K key, V value) {
        if (node == nullptr)
            return new AVLNode<K, V>(key, value);

        if (key < node->key)
            node->left = insertHelper(node->left, key, value);
        else 
            node->right = insertHelper(node->right, key, value);

        node->height = 1 + std::max(height(node->left), height(node->right));

        int balance = getBalance(node);

        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        if (balance < -1 && key >= node->right->key)
            return leftRotate(node);

        if (balance > 1 && key >= node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    AVLNode<K, V>* searchHelper(AVLNode<K, V>* node, K key) const {
        if (node == nullptr || node->key == key) return node;
        if (key < node->key) return searchHelper(node->left, key);
        return searchHelper(node->right, key);
    }

    void saveReverseInOrderHelper(AVLNode<K, V>* node, std::ofstream& out) const {
        if (node != nullptr) {
            saveReverseInOrderHelper(node->right, out);
            out << node->key << "\t" << node->value << "\n";
            saveReverseInOrderHelper(node->left, out);
        }
    }

    void destroyTree(AVLNode<K, V>* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() { destroyTree(root); }

    void insert(K key, V value) {
        root = insertHelper(root, key, value);
    }

    V* search(K key) const {
        AVLNode<K, V>* result = searchHelper(root, key);
        if (result != nullptr) return &(result->value);
        return nullptr;
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream out(filename);
        if (out.is_open()) {
            saveReverseInOrderHelper(root, out);
            out.close();
        } else {
            std::cerr << "Nie udalo sie otworzyc pliku!\n";
        }
    }
};