#pragma once
#include <string>
#include <vector>
#include "nlohmann/json.hpp"

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
    bool empty() const;
    bool isEmpty() const;
    nlohmann::json serialize() const;
    void deserialize(const nlohmann::json& json);
    void serializeBinary(std::ostream& os) const;
    void deserializeBinary(std::istream& is);
    void serializeText(std::ostream& os) const;
    void deserializeText(std::istream& is);
    void print() const;
};
