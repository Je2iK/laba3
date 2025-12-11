// RedBlackTree - Self-balancing binary search tree (replaces AVL)
#pragma once
#include <string>
#include "nlohmann/json.hpp"

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
    nlohmann::json serialize() const;
    void deserialize(const nlohmann::json& json);
    void serializeBinary(std::ostream& os) const;
    void deserializeBinary(std::istream& is);
    void serializeText(std::ostream& os) const;
    void deserializeText(std::istream& is);
    void print() const;
};
