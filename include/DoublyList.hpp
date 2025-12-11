#pragma once
#include <string>

struct DoublyListNode {
    std::string data;
    DoublyListNode* next;
    DoublyListNode* prev;
    DoublyListNode(const std::string& value) : data(value), next(nullptr), prev(nullptr) {}
};

class DoublyList {
private:
    DoublyListNode* head;
    DoublyListNode* tail;
    int count;

public:
    DoublyList();
    ~DoublyList();
    void pushFront(const std::string& value);
    void pushBack(const std::string& value);
    void popFront();
    void popBack();
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
