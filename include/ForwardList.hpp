#pragma once
#include <string>

struct ForwardListNode {
    std::string data;
    ForwardListNode* next;
    ForwardListNode(const std::string& value) : data(value), next(nullptr) {}
};

class ForwardList {
private:
    ForwardListNode* head;
    int count;

public:
    ForwardList();
    ~ForwardList();
    void pushFront(const std::string& value);
    void popFront();
    void insert(int index, const std::string& value);
    void remove(int index);
    std::string get(int index) const;
    int size() const;
    bool isEmpty() const;
    std::string toJSON() const;
    void fromJSON(const std::string& json);
    void saveBinary(const std::string& filename) const;
    void loadBinary(const std::string& filename);
    void saveText(const std::string& filename) const;
    void loadText(const std::string& filename);
    void print() const;
};
