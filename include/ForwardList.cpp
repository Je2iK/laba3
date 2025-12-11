#include "ForwardList.hpp"
#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"

ForwardList::ForwardList() : head(nullptr), count(0) {}
ForwardList::~ForwardList() { while (!isEmpty()) popFront(); }

void ForwardList::pushFront(const std::string& value) {
    ForwardListNode* newNode = new ForwardListNode(value);
    newNode->next = head;
    head = newNode;
    count++;
}

void ForwardList::popFront() {
    if (isEmpty()) throw std::runtime_error("List is empty");
    ForwardListNode* temp = head;
    head = head->next;
    delete temp;
    count--;
}

void ForwardList::insert(int index, const std::string& value) {
    if (index == 0) { pushFront(value); return; }
    ForwardListNode* current = head;
    for (int i = 0; i < index - 1 && current; i++) current = current->next;
    if (!current) throw std::out_of_range("Index out of range");
    ForwardListNode* newNode = new ForwardListNode(value);
    newNode->next = current->next;
    current->next = newNode;
    count++;
}

void ForwardList::remove(int index) {
    if (isEmpty()) throw std::runtime_error("List is empty");
    if (index == 0) { popFront(); return; }
    ForwardListNode* current = head;
    for (int i = 0; i < index - 1 && current; i++) current = current->next;
    if (!current || !current->next) throw std::out_of_range("Index out of range");
    ForwardListNode* temp = current->next;
    current->next = temp->next;
    delete temp;
    count--;
}

std::string ForwardList::get(int index) const {
    ForwardListNode* current = head;
    for (int i = 0; i < index && current; i++) current = current->next;
    if (!current) throw std::out_of_range("Index out of range");
    return current->data;
}

int ForwardList::size() const { return count; }
bool ForwardList::isEmpty() const { return head == nullptr; }

std::string ForwardList::toJSON() const {
    nlohmann::json j;
    j["size"] = count;
    j["elements"] = nlohmann::json::array();
    ForwardListNode* current = head;
    while (current) {
        j["elements"].push_back(current->data);
        current = current->next;
    }
    return j.dump();
}

void ForwardList::fromJSON(const std::string& jsonStr) {
    while (!isEmpty()) popFront();
    nlohmann::json j = nlohmann::json::parse(jsonStr);
    auto elements = j["elements"];
    for (auto it = elements.rbegin(); it != elements.rend(); ++it) {
        pushFront(it->get<std::string>());
    }
}

void ForwardList::saveBinary(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    file.write(reinterpret_cast<const char*>(&count), sizeof(count));
    ForwardListNode* current = head;
    while (current) {
        size_t len = current->data.length();
        file.write(reinterpret_cast<const char*>(&len), sizeof(len));
        file.write(current->data.c_str(), len);
        current = current->next;
    }
}

void ForwardList::loadBinary(const std::string& filename) {
    while (!isEmpty()) popFront();
    std::ifstream file(filename, std::ios::binary);
    int size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));
    std::vector<std::string> elements;
    for (int i = 0; i < size; i++) {
        size_t len;
        file.read(reinterpret_cast<char*>(&len), sizeof(len));
        std::string element(len, '\0');
        file.read(&element[0], len);
        elements.push_back(element);
    }
    for (auto it = elements.rbegin(); it != elements.rend(); ++it) {
        pushFront(*it);
    }
}

void ForwardList::saveText(const std::string& filename) const {
    std::ofstream file(filename);
    file << count << std::endl;
    ForwardListNode* current = head;
    while (current) {
        file << current->data << std::endl;
        current = current->next;
    }
}

void ForwardList::loadText(const std::string& filename) {
    while (!isEmpty()) popFront();
    std::ifstream file(filename);
    int size;
    file >> size;
    file.ignore();
    std::vector<std::string> elements;
    for (int i = 0; i < size; i++) {
        std::string element;
        std::getline(file, element);
        elements.push_back(element);
    }
    for (auto it = elements.rbegin(); it != elements.rend(); ++it) {
        pushFront(*it);
    }
}

void ForwardList::print() const {
    std::cout << "ForwardList: ";
    ForwardListNode* current = head;
    while (current) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}
