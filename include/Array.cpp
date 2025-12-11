#include "Array.hpp"
#include <iostream>
#include <sstream>

Array::Array(int cap) : capacity(cap) { data.reserve(cap); }

void Array::insert(int index, const std::string& value) {
    if (index < 0 || index > (int)data.size()) throw std::out_of_range("Index out of range");
    data.insert(data.begin() + index, value);
}

void Array::remove(int index) {
    if (index < 0 || index >= (int)data.size()) throw std::out_of_range("Index out of range");
    data.erase(data.begin() + index);
}

std::string Array::get(int index) const {
    if (index < 0 || index >= (int)data.size()) throw std::out_of_range("Index out of range");
    return data[index];
}

void Array::set(int index, const std::string& value) {
    if (index < 0 || index >= (int)data.size()) throw std::out_of_range("Index out of range");
    data[index] = value;
}

int Array::size() const { return data.size(); }
bool Array::empty() const { return data.empty(); }
bool Array::isEmpty() const { return empty(); }

nlohmann::json Array::serialize() const {
    nlohmann::json j;
    j["capacity"] = capacity;
    j["elements"] = data;
    return j;
}

void Array::deserialize(const nlohmann::json& j) {
    capacity = j["capacity"];
    data = j["elements"].get<std::vector<std::string>>();
}

void Array::serializeBinary(std::ostream& os) const {
    int size = data.size();
    os.write(reinterpret_cast<const char*>(&size), sizeof(size));
    for (const auto& item : data) {
        size_t len = item.length();
        os.write(reinterpret_cast<const char*>(&len), sizeof(len));
        os.write(item.c_str(), len);
    }
}

void Array::deserializeBinary(std::istream& is) {
    data.clear();
    int size;
    is.read(reinterpret_cast<char*>(&size), sizeof(size));
    for (int i = 0; i < size; i++) {
        size_t len;
        is.read(reinterpret_cast<char*>(&len), sizeof(len));
        std::string item(len, '\0');
        is.read(&item[0], len);
        data.push_back(item);
    }
}

void Array::serializeText(std::ostream& os) const {
    os << data.size() << std::endl;
    for (const auto& item : data) {
        os << item << std::endl;
    }
}

void Array::deserializeText(std::istream& is) {
    data.clear();
    int size;
    is >> size;
    is.ignore();
    for (int i = 0; i < size; i++) {
        std::string item;
        std::getline(is, item);
        data.push_back(item);
    }
}

void Array::print() const {
    std::cout << "Array: ";
    for (const auto& item : data) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}
