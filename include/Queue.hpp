#pragma once
#include <string>
#include "nlohmann/json.hpp"

struct QueueNode {
    std::string data;
    QueueNode* next;
    QueueNode(const std::string& value) : data(value), next(nullptr) {}
};

class Queue {
private:
    QueueNode* frontNode;
    QueueNode* rear;
    int count;

public:
    Queue();
    ~Queue();
    
    void enqueue(const std::string& value);
    std::string dequeue();
    std::string front() const;
    std::string getFront() const;
    bool empty() const;
    bool isEmpty() const;
    int size() const;
    
    nlohmann::json serialize() const;
    void deserialize(const nlohmann::json& json);
    void serializeBinary(std::ostream& os) const;
    void deserializeBinary(std::istream& is);
    void serializeText(std::ostream& os) const;
    void deserializeText(std::istream& is);
    void print() const;
};
