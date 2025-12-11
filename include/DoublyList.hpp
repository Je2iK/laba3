// DoublyList - Двусвязный список
#pragma once
#include <string>
#include "nlohmann/json.hpp"

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
    nlohmann::json serialize() const;
    void deserialize(const nlohmann::json& json);
    void serializeBinary(std::ostream& os) const;
    void deserializeBinary(std::istream& is);
    void serializeText(std::ostream& os) const;
    void deserializeText(std::istream& is);
    void print() const;
};
