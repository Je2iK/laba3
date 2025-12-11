#include "ChainHashTable.hpp"
#include <iostream>
#include <sstream>

ChainHashTable::ChainHashTable(int size) : tableSize(size), count(0) {
    buckets.resize(size);
}

int ChainHashTable::hash(const std::string& key) const {
    int hash = 0;
    for (char c : key) {
        hash = (hash * 31 + c) % tableSize;
    }
    return hash < 0 ? -hash : hash;
}

void ChainHashTable::insert(const std::string& key, const std::string& value) {
    int index = hash(key);
    
    // Проверяем, существует ли ключ
    for (auto& node : buckets[index]) {
        if (node.key == key) {
            node.value = value;
            return;
        }
    }
    
    // Добавляем новый узел
    buckets[index].emplace_back(key, value);
    count++;
}

std::string ChainHashTable::find(const std::string& key) const {
    int index = hash(key);
    
    for (const auto& node : buckets[index]) {
        if (node.key == key) {
            return node.value;
        }
    }
    return "";
}

bool ChainHashTable::hasKey(const std::string& key) const {
    int index = hash(key);
    
    for (const auto& node : buckets[index]) {
        if (node.key == key) {
            return true;
        }
    }
    return false;
}

void ChainHashTable::remove(const std::string& key) {
    int index = hash(key);
    
    auto& bucket = buckets[index];
    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if (it->key == key) {
            bucket.erase(it);
            count--;
            return;
        }
    }
}

int ChainHashTable::size() const {
    return count;
}

bool ChainHashTable::isEmpty() const {
    return count == 0;
}

nlohmann::json ChainHashTable::serialize() const {
    nlohmann::json j;
    j["tableSize"] = tableSize;
    j["count"] = count;
    j["buckets"] = nlohmann::json::array();
    
    for (const auto& bucket : buckets) {
        nlohmann::json bucketJson = nlohmann::json::array();
        for (const auto& node : bucket) {
            nlohmann::json nodeJson;
            nodeJson["key"] = node.key;
            nodeJson["value"] = node.value;
            bucketJson.push_back(nodeJson);
        }
        j["buckets"].push_back(bucketJson);
    }
    
    return j;
}

void ChainHashTable::deserialize(const nlohmann::json& j) {
    buckets.clear();
    tableSize = j["tableSize"];
    count = j["count"];
    buckets.resize(tableSize);
    
    auto bucketsJson = j["buckets"];
    for (size_t i = 0; i < bucketsJson.size(); ++i) {
        for (const auto& nodeJson : bucketsJson[i]) {
            buckets[i].emplace_back(nodeJson["key"], nodeJson["value"]);
        }
    }
}

void ChainHashTable::serializeBinary(std::ostream& os) const {
    os.write(reinterpret_cast<const char*>(&tableSize), sizeof(tableSize));
    os.write(reinterpret_cast<const char*>(&count), sizeof(count));
    
    for (const auto& bucket : buckets) {
        int bucketSize = bucket.size();
        os.write(reinterpret_cast<const char*>(&bucketSize), sizeof(bucketSize));
        
        for (const auto& node : bucket) {
            size_t keyLen = node.key.length();
            size_t valueLen = node.value.length();
            
            os.write(reinterpret_cast<const char*>(&keyLen), sizeof(keyLen));
            os.write(node.key.c_str(), keyLen);
            os.write(reinterpret_cast<const char*>(&valueLen), sizeof(valueLen));
            os.write(node.value.c_str(), valueLen);
        }
    }
}

void ChainHashTable::deserializeBinary(std::istream& is) {
    buckets.clear();
    
    is.read(reinterpret_cast<char*>(&tableSize), sizeof(tableSize));
    is.read(reinterpret_cast<char*>(&count), sizeof(count));
    
    buckets.resize(tableSize);
    
    for (int i = 0; i < tableSize; ++i) {
        int bucketSize;
        is.read(reinterpret_cast<char*>(&bucketSize), sizeof(bucketSize));
        
        for (int j = 0; j < bucketSize; ++j) {
            size_t keyLen, valueLen;
            
            is.read(reinterpret_cast<char*>(&keyLen), sizeof(keyLen));
            std::string key(keyLen, '\0');
            is.read(&key[0], keyLen);
            
            is.read(reinterpret_cast<char*>(&valueLen), sizeof(valueLen));
            std::string value(valueLen, '\0');
            is.read(&value[0], valueLen);
            
            buckets[i].emplace_back(key, value);
        }
    }
}

void ChainHashTable::serializeText(std::ostream& os) const {
    os << tableSize << " " << count << std::endl;
    
    for (const auto& bucket : buckets) {
        os << bucket.size() << std::endl;
        for (const auto& node : bucket) {
            os << node.key << " " << node.value << std::endl;
        }
    }
}

void ChainHashTable::deserializeText(std::istream& is) {
    buckets.clear();
    
    is >> tableSize >> count;
    buckets.resize(tableSize);
    
    for (int i = 0; i < tableSize; ++i) {
        int bucketSize;
        is >> bucketSize;
        
        for (int j = 0; j < bucketSize; ++j) {
            std::string key, value;
            is >> key >> value;
            buckets[i].emplace_back(key, value);
        }
    }
}

void ChainHashTable::display() const {
    std::cout << "Hash Table (size=" << count << "):" << std::endl;
    
    for (int i = 0; i < tableSize; ++i) {
        if (!buckets[i].empty()) {
            std::cout << "Bucket " << i << ": ";
            for (const auto& node : buckets[i]) {
                std::cout << "[" << node.key << ":" << node.value << "] ";
            }
            std::cout << std::endl;
        }
    }
}
