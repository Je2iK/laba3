#include "DoublyList.hpp"
#include <iostream>
#include <sstream>

DoublyList::DoublyList() : head(nullptr), tail(nullptr), count(0) {}

DoublyList::~DoublyList() {
    while (!isEmpty()) {
        popFront();
    }
}

void DoublyList::pushFront(const std::string& value) {
    DoublyListNode* newNode = new DoublyListNode(value);
    if (isEmpty()) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    count++;
}

void DoublyList::pushBack(const std::string& value) {
    DoublyListNode* newNode = new DoublyListNode(value);
    if (isEmpty()) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    count++;
}

void DoublyList::popFront() {
    if (isEmpty()) throw std::runtime_error("List is empty");
    DoublyListNode* temp = head;
    if (head == tail) {
        head = tail = nullptr;
    } else {
        head = head->next;
        head->prev = nullptr;
    }
    delete temp;
    count--;
}

void DoublyList::popBack() {
    if (isEmpty()) throw std::runtime_error("List is empty");
    DoublyListNode* temp = tail;
    if (head == tail) {
        head = tail = nullptr;
    } else {
        tail = tail->prev;
        tail->next = nullptr;
    }
    delete temp;
    count--;
}

void DoublyList::insert(int index, const std::string& value) {
    if (index == 0) { pushFront(value); return; }
    if (index == count) { pushBack(value); return; }
    
    DoublyListNode* current = head;
    for (int i = 0; i < index && current; i++) {
        current = current->next;
    }
    if (!current) throw std::out_of_range("Index out of range");
    
    DoublyListNode* newNode = new DoublyListNode(value);
    newNode->next = current;
    newNode->prev = current->prev;
    current->prev->next = newNode;
    current->prev = newNode;
    count++;
}

void DoublyList::remove(int index) {
    if (isEmpty()) throw std::runtime_error("List is empty");
    if (index == 0) { popFront(); return; }
    if (index == count - 1) { popBack(); return; }
    
    DoublyListNode* current = head;
    for (int i = 0; i < index && current; i++) {
        current = current->next;
    }
    if (!current) throw std::out_of_range("Index out of range");
    
    current->prev->next = current->next;
    current->next->prev = current->prev;
    delete current;
    count--;
}

std::string DoublyList::get(int index) const {
    DoublyListNode* current = head;
    for (int i = 0; i < index && current; i++) {
        current = current->next;
    }
    if (!current) throw std::out_of_range("Index out of range");
    return current->data;
}

int DoublyList::size() const { return count; }
bool DoublyList::isEmpty() const { return head == nullptr; }

nlohmann::json DoublyList::serialize() const {
    nlohmann::json j;
    j["size"] = count;
    j["elements"] = nlohmann::json::array();
    DoublyListNode* current = head;
    while (current) {
        j["elements"].push_back(current->data);
        current = current->next;
    }
    return j;
}

void DoublyList::deserialize(const nlohmann::json& j) {
    while (!isEmpty()) popFront();
    auto elements = j["elements"];
    for (const auto& element : elements) {
        pushBack(element.get<std::string>());
    }
}

void DoublyList::serializeBinary(std::ostream& os) const {
    os.write(reinterpret_cast<const char*>(&count), sizeof(count));
    DoublyListNode* current = head;
    while (current) {
        size_t len = current->data.length();
        os.write(reinterpret_cast<const char*>(&len), sizeof(len));
        os.write(current->data.c_str(), len);
        current = current->next;
    }
}

void DoublyList::deserializeBinary(std::istream& is) {
    while (!isEmpty()) popFront();
    int size;
    is.read(reinterpret_cast<char*>(&size), sizeof(size));
    for (int i = 0; i < size; i++) {
        size_t len;
        is.read(reinterpret_cast<char*>(&len), sizeof(len));
        std::string element(len, '\0');
        is.read(&element[0], len);
        pushBack(element);
    }
}

void DoublyList::serializeText(std::ostream& os) const {
    os << count << std::endl;
    DoublyListNode* current = head;
    while (current) {
        os << current->data << std::endl;
        current = current->next;
    }
}

void DoublyList::deserializeText(std::istream& is) {
    while (!isEmpty()) popFront();
    int size;
    is >> size;
    is.ignore();
    for (int i = 0; i < size; i++) {
        std::string element;
        std::getline(is, element);
        pushBack(element);
    }
}

void DoublyList::print() const {
    std::cout << "DoublyList: ";
    DoublyListNode* current = head;
    while (current) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}
