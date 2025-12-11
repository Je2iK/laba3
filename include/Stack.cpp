#include "Stack.hpp"
#include <iostream>
#include <sstream>

Stack::Stack() : topNode(nullptr), count(0) {}

Stack::~Stack() {
    while (!empty()) {
        pop();
    }
}

// Добавляет элемент в стек
void Stack::push(const std::string& value) {
    StackNode* newNode = new StackNode(value);
    newNode->next = topNode;
    topNode = newNode;
    count++;
}

// Удаляет и возвращает верхний элемент
std::string Stack::pop() {
    if (empty()) {
        throw std::runtime_error("Stack is empty");
    }
    
    StackNode* temp = topNode;
    std::string value = temp->data;
    topNode = topNode->next;
    delete temp;
    count--;
    return value;
}

// Возвращает верхний элемент без удаления
std::string Stack::top() const {
    if (empty()) {
        throw std::runtime_error("Stack is empty");
    }
    return topNode->data;
}

bool Stack::empty() const {
    return topNode == nullptr;
}

bool Stack::isEmpty() const {
    return empty();
}

int Stack::size() const {
    return count;
}

// Проверяет наличие элемента в стеке
bool Stack::contains(const std::string& value) const {
    StackNode* current = topNode;
    while (current != nullptr) {
        if (current->data == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Сериализация в JSON
nlohmann::json Stack::serialize() const {
    nlohmann::json j;
    j["size"] = count;
    j["elements"] = nlohmann::json::array();
    
    StackNode* current = topNode;
    while (current != nullptr) {
        j["elements"].push_back(current->data);
        current = current->next;
    }
    
    return j;
}

// Десериализация из JSON
void Stack::deserialize(const nlohmann::json& j) {
    while (!empty()) {
        pop();
    }
    
    auto elements = j["elements"];
    for (auto it = elements.rbegin(); it != elements.rend(); ++it) {
        push(it->get<std::string>());
    }
}

// Бинарная сериализация
void Stack::serializeBinary(std::ostream& os) const {
    os.write(reinterpret_cast<const char*>(&count), sizeof(count));
    
    StackNode* current = topNode;
    while (current != nullptr) {
        size_t len = current->data.length();
        os.write(reinterpret_cast<const char*>(&len), sizeof(len));
        os.write(current->data.c_str(), len);
        current = current->next;
    }
}

// Бинарная десериализация
void Stack::deserializeBinary(std::istream& is) {
    while (!empty()) {
        pop();
    }
    
    int size;
    is.read(reinterpret_cast<char*>(&size), sizeof(size));
    
    std::vector<std::string> elements;
    for (int i = 0; i < size; i++) {
        size_t len;
        is.read(reinterpret_cast<char*>(&len), sizeof(len));
        
        std::string element(len, '\0');
        is.read(&element[0], len);
        elements.push_back(element);
    }
    
    for (auto it = elements.rbegin(); it != elements.rend(); ++it) {
        push(*it);
    }
}

// Текстовая сериализация
void Stack::serializeText(std::ostream& os) const {
    os << count << std::endl;
    
    StackNode* current = topNode;
    while (current != nullptr) {
        os << current->data << std::endl;
        current = current->next;
    }
}

// Текстовая десериализация
void Stack::deserializeText(std::istream& is) {
    while (!empty()) {
        pop();
    }
    
    int size;
    is >> size;
    is.ignore();
    
    std::vector<std::string> elements;
    for (int i = 0; i < size; i++) {
        std::string element;
        std::getline(is, element);
        elements.push_back(element);
    }
    
    for (auto it = elements.rbegin(); it != elements.rend(); ++it) {
        push(*it);
    }
}

// Выводит содержимое стека
void Stack::print() const {
    std::cout << "Stack: ";
    StackNode* current = topNode;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}
