#pragma once
#include <string>

struct QueueNode {
    std::string data;
    QueueNode* next;
    QueueNode(const std::string& value) : data(value), next(nullptr) {}
};

class Queue {
private:
    QueueNode* front;
    QueueNode* rear;
    int count;

public:
    Queue();
    ~Queue();
    
    void enqueue(const std::string& value);
    std::string dequeue();
    std::string getFront() const;
    bool isEmpty() const;
    int size() const;
    
    std::string toJSON() const;
    void fromJSON(const std::string& json);
    void saveBinary(const std::string& filename) const;
    void loadBinary(const std::string& filename);
    void saveText(const std::string& filename) const;
    void loadText(const std::string& filename);
    void print() const;
};
