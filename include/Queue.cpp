#include "Queue.hpp"
#include <iostream>
#include <sstream>

Queue::Queue() : frontNode(nullptr), rear(nullptr), count(0) {}

Queue::~Queue() {
    while (!empty()) {
        dequeue();
    }
}

// Добавляет элемент в очередь
void Queue::enqueue(const std::string& value) {
    QueueNode* newNode = new QueueNode(value);
    if (empty()) {
        frontNode = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    count++;
}

// Удаляет и возвращает первый элемент
std::string Queue::dequeue() {
    if (empty()) {
        throw std::runtime_error("Queue is empty");
    }
    
    QueueNode* temp = frontNode;
    std::string value = temp->data;
    frontNode = frontNode->next;
    
    if (frontNode == nullptr) {
        rear = nullptr;
    }
    
    delete temp;
    count--;
    return value;
}

std::string Queue::front() const {
    if (empty()) {
        throw std::runtime_error("Queue is empty");
    }
    return frontNode->data;
}

std::string Queue::getFront() const {
    return front();
}

bool Queue::empty() const {
    return frontNode == nullptr;
}

bool Queue::isEmpty() const {
    return empty();
}

int Queue::size() const {
    return count;
}

// Сериализация в JSON
nlohmann::json Queue::serialize() const {
    nlohmann::json j;
    j["size"] = count;
    j["elements"] = nlohmann::json::array();
    
    QueueNode* current = frontNode;
    while (current != nullptr) {
        j["elements"].push_back(current->data);
        current = current->next;
    }
    
    return j;
}

// Десериализация из JSON
void Queue::deserialize(const nlohmann::json& j) {
    while (!empty()) {
        dequeue();
    }
    
    auto elements = j["elements"];
    for (const auto& element : elements) {
        enqueue(element.get<std::string>());
    }
}

void Queue::serializeBinary(std::ostream& os) const {
    os.write(reinterpret_cast<const char*>(&count), sizeof(count));
    
    QueueNode* current = frontNode;
    while (current != nullptr) {
        size_t len = current->data.length();
        os.write(reinterpret_cast<const char*>(&len), sizeof(len));
        os.write(current->data.c_str(), len);
        current = current->next;
    }
}

void Queue::deserializeBinary(std::istream& is) {
    while (!empty()) {
        dequeue();
    }
    
    int size;
    is.read(reinterpret_cast<char*>(&size), sizeof(size));
    
    for (int i = 0; i < size; i++) {
        size_t len;
        is.read(reinterpret_cast<char*>(&len), sizeof(len));
        
        std::string element(len, '\0');
        is.read(&element[0], len);
        enqueue(element);
    }
}

void Queue::serializeText(std::ostream& os) const {
    os << count << std::endl;
    
    QueueNode* current = frontNode;
    while (current != nullptr) {
        os << current->data << std::endl;
        current = current->next;
    }
}

void Queue::deserializeText(std::istream& is) {
    while (!empty()) {
        dequeue();
    }
    
    int size;
    is >> size;
    is.ignore();
    
    for (int i = 0; i < size; i++) {
        std::string element;
        std::getline(is, element);
        enqueue(element);
    }
}

// Выводит содержимое очереди
void Queue::print() const {
    std::cout << "Queue: ";
    QueueNode* current = frontNode;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}
