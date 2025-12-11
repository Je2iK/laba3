#include "Queue.hpp"
#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

Queue::Queue() : front(nullptr), rear(nullptr), count(0) {}

Queue::~Queue() {
    while (!isEmpty()) {
        dequeue();
    }
}

void Queue::enqueue(const std::string& value) {
    QueueNode* newNode = new QueueNode(value);
    if (isEmpty()) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    count++;
}

std::string Queue::dequeue() {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }
    
    QueueNode* temp = front;
    std::string value = temp->data;
    front = front->next;
    
    if (front == nullptr) {
        rear = nullptr;
    }
    
    delete temp;
    count--;
    return value;
}

std::string Queue::getFront() const {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }
    return front->data;
}

bool Queue::isEmpty() const {
    return front == nullptr;
}

int Queue::size() const {
    return count;
}

std::string Queue::toJSON() const {
    json j;
    j["size"] = count;
    j["elements"] = json::array();
    
    QueueNode* current = front;
    while (current != nullptr) {
        j["elements"].push_back(current->data);
        current = current->next;
    }
    
    return j.dump();
}

void Queue::fromJSON(const std::string& jsonStr) {
    while (!isEmpty()) {
        dequeue();
    }
    
    json j = json::parse(jsonStr);
    auto elements = j["elements"];
    
    for (const auto& element : elements) {
        enqueue(element.get<std::string>());
    }
}

void Queue::saveBinary(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    file.write(reinterpret_cast<const char*>(&count), sizeof(count));
    
    QueueNode* current = front;
    while (current != nullptr) {
        size_t len = current->data.length();
        file.write(reinterpret_cast<const char*>(&len), sizeof(len));
        file.write(current->data.c_str(), len);
        current = current->next;
    }
    file.close();
}

void Queue::loadBinary(const std::string& filename) {
    while (!isEmpty()) {
        dequeue();
    }
    
    std::ifstream file(filename, std::ios::binary);
    int size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));
    
    for (int i = 0; i < size; i++) {
        size_t len;
        file.read(reinterpret_cast<char*>(&len), sizeof(len));
        
        std::string element(len, '\0');
        file.read(&element[0], len);
        enqueue(element);
    }
    file.close();
}

void Queue::saveText(const std::string& filename) const {
    std::ofstream file(filename);
    file << count << std::endl;
    
    QueueNode* current = front;
    while (current != nullptr) {
        file << current->data << std::endl;
        current = current->next;
    }
    file.close();
}

void Queue::loadText(const std::string& filename) {
    while (!isEmpty()) {
        dequeue();
    }
    
    std::ifstream file(filename);
    int size;
    file >> size;
    file.ignore();
    
    for (int i = 0; i < size; i++) {
        std::string element;
        std::getline(file, element);
        enqueue(element);
    }
    file.close();
}

void Queue::print() const {
    std::cout << "Queue: ";
    QueueNode* current = front;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}
