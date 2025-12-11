// ChainHashTable - Hash table with chaining collision resolution (replaces Cuckoo)
#pragma once
#include <string>
#include <vector>
#include <list>
#include "nlohmann/json.hpp"

struct HashNode {
    std::string key;
    std::string value;
    HashNode(const std::string& k, const std::string& v) : key(k), value(v) {}
};

class ChainHashTable {
private:
    std::vector<std::list<HashNode>> buckets;
    int tableSize;
    int count;
    
    int hash(const std::string& key) const;

public:
    ChainHashTable(int size = 16);
    void insert(const std::string& key, const std::string& value);
    std::string find(const std::string& key) const;
    bool hasKey(const std::string& key) const;
    void remove(const std::string& key);
    int size() const;
    bool isEmpty() const;
    nlohmann::json serialize() const;
    void deserialize(const nlohmann::json& json);
    void serializeBinary(std::ostream& os) const;
    void deserializeBinary(std::istream& is);
    void serializeText(std::ostream& os) const;
    void deserializeText(std::istream& is);
    void display() const;
};
