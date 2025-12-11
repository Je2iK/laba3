// ChainHashTable - Hash table with chaining collision resolution (replaces Cuckoo)
#pragma once
#include <string>
#include <vector>
#include <list>

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
    std::string toJSON() const;
    void fromJSON(const std::string& json);
    void saveBinary(const std::string& filename) const;
    void loadBinary(const std::string& filename);
    void saveText(const std::string& filename) const;
    void loadText(const std::string& filename);
    void display() const;
};
