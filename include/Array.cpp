#include "Array.hpp"
#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

Array::Array(int cap) : capacity(cap) {
    data.reserve(cap);
}

void Array::insert(int index, const std::string& value) {
    if (index < 0 || index > (int)data.size()) {
        throw std::out_of_range("Index out of range");
    }
    data.insert(data.begin() + index, value);
}

void Array::remove(int index) {
    if (index < 0 || index >= (int)data.size()) {
        throw std::out_of_range("Index out of range");
    }
    data.erase(data.begin() + index);
}

std::string Array::get(int index) const {
    if (index < 0 || index >= (int)data.size()) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

void Array::set(int index, const std::string& value) {
    if (index < 0 || index >= (int)data.size()) {
        throw std::out_of_range("Index out of range");
    }
    data[index] = value;
}

int Array::size() const {
    return data.size();
}

bool Array::isEmpty() const {
    return data.empty();
}

std::string Array::toJSON() const {
    json j;
    j["capacity"] = capacity;
    j["elements"] = data;
    return j.dump();
}

void Array::fromJSON(const std::string& jsonStr) {
    json j = json::parse(jsonStr);
    capacity = j["capacity"];
    data = j["elements"].get<std::vector<std::string>>();
}

void Array::saveBinary(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    int size = data.size();
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));
    for (const auto& item : data) {
        size_t len = item.length();
        file.write(reinterpret_cast<const char*>(&len), sizeof(len));
        file.write(item.c_str(), len);
    }
    file.close();
}

void Array::loadBinary(const std::string& filename) {
    data.clear();
    std::ifstream file(filename, std::ios::binary);
    int size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));
    
    for (int i = 0; i < size; i++) {
        size_t len;
        file.read(reinterpret_cast<char*>(&len), sizeof(len));
        std::string item(len, '\0');
        file.read(&item[0], len);
        data.push_back(item);
    }
    file.close();
}

void Array::saveText(const std::string& filename) const {
    std::ofstream file(filename);
    file << data.size() << std::endl;
    for (const auto& item : data) {
        file << item << std::endl;
    }
    file.close();
}

void Array::loadText(const std::string& filename) {
    data.clear();
    std::ifstream file(filename);
    int size;
    file >> size;
    file.ignore();
    
    for (int i = 0; i < size; i++) {
        std::string item;
        std::getline(file, item);
        data.push_back(item);
    }
    file.close();
}

void Array::print() const {
    std::cout << "Array: ";
    for (const auto& item : data) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}
