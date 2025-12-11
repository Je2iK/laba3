// RedBlackTree - Self-balancing binary search tree (replaces AVL)
#pragma once
#include <string>

enum Color { RED, BLACK };

struct RBNode {
    std::string data;
    Color color;
    RBNode* left;
    RBNode* right;
    RBNode* parent;
    RBNode(const std::string& value) : data(value), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    RBNode* root;
    RBNode* nil;
    
    void leftRotate(RBNode* x);
    void rightRotate(RBNode* x);
    void insertFixup(RBNode* z);
    void inorderTraversal(RBNode* node, std::string& result) const;

public:
    RedBlackTree();
    ~RedBlackTree();
    void insert(const std::string& value);
    bool search(const std::string& value) const;
    void remove(const std::string& value);
    bool isEmpty() const;
    std::string toJSON() const;
    void fromJSON(const std::string& json);
    void saveBinary(const std::string& filename) const;
    void loadBinary(const std::string& filename);
    void saveText(const std::string& filename) const;
    void loadText(const std::string& filename);
    void print() const;
};
