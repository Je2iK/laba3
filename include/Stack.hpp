// Stack - LIFO data structure implementation
#pragma once
#include <string>
#include <vector>
#include "nlohmann/json.hpp"

struct StackNode {
    std::string data;
    StackNode* next;
    
    StackNode(const std::string& value) : data(value), next(nullptr) {}
};

class Stack {
private:
    StackNode* topNode;
    int count;

public:
    Stack();
    ~Stack();
    
    void push(const std::string& value);
    std::string pop();
    std::string top() const;
    bool empty() const;
    bool isEmpty() const;
    int size() const;
    bool contains(const std::string& value) const;
    
    nlohmann::json serialize() const;
    void deserialize(const nlohmann::json& json);
    void serializeBinary(std::ostream& os) const;
    void deserializeBinary(std::istream& is);
    void serializeText(std::ostream& os) const;
    void deserializeText(std::istream& is);
    void print() const;
};
