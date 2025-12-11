package main

import (
	"encoding/json"
	"fmt"
)

type ForwardNode struct {
	data string
	next *ForwardNode
}

type ForwardList struct {
	head *ForwardNode
	size int
}

func NewForwardList() *ForwardList {
	return &ForwardList{
		head: nil,
		size: 0,
	}
}

func (l *ForwardList) PushFront(value string) {
	newNode := &ForwardNode{
		data: value,
		next: l.head,
	}
	l.head = newNode
	l.size++
}

func (l *ForwardList) PopFront() (string, bool) {
	if l.head == nil {
		return "", false
	}
	value := l.head.data
	l.head = l.head.next
	l.size--
	return value, true
}

func (l *ForwardList) Get(index int) (string, error) {
	if index < 0 || index >= l.size {
		return "", fmt.Errorf("index out of range")
	}
	
	current := l.head
	for i := 0; i < index; i++ {
		current = current.next
	}
	return current.data, nil
}

func (l *ForwardList) Size() int {
	return l.size
}

func (l *ForwardList) IsEmpty() bool {
	return l.head == nil
}

func (l *ForwardList) ToJSON() ([]byte, error) {
	var elements []string
	current := l.head
	for current != nil {
		elements = append(elements, current.data)
		current = current.next
	}
	return json.Marshal(elements)
}

func (l *ForwardList) FromJSON(data []byte) error {
	var elements []string
	if err := json.Unmarshal(data, &elements); err != nil {
		return err
	}
	
	l.head = nil
	l.size = 0
	
	for i := len(elements) - 1; i >= 0; i-- {
		l.PushFront(elements[i])
	}
	return nil
}

func (l *ForwardList) Print() {
	fmt.Print("ForwardList: ")
	current := l.head
	for current != nil {
		fmt.Print(current.data + " ")
		current = current.next
	}
	fmt.Println()
}
