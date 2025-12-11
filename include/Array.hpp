#pragma once
#include <string>
#include <vector>

class Array {
private:
    std::vector<std::string> data;
    int capacity;

public:
    Array(int cap = 10);
    void insert(int index, const std::string& value);
    void remove(int index);
    std::string get(int index) const;
    void set(int index, const std::string& value);
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
