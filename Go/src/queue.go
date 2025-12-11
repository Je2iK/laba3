package main

import (
	"bufio"
	"encoding/binary"
	"encoding/json"
	"fmt"
	"io"
	"strconv"
	"strings"
)

type QueueNode struct {
	data string
	next *QueueNode
}

type Queue struct {
	front *QueueNode
	rear  *QueueNode
	size  int
}

func NewQueue() *Queue {
	return &Queue{
		front: nil,
		rear:  nil,
		size:  0,
	}
}

func (q *Queue) Enqueue(value string) {
	newNode := &QueueNode{
		data: value,
		next: nil,
	}
	
	if q.rear != nil {
		q.rear.next = newNode
	} else {
		q.front = newNode
	}
	q.rear = newNode
	q.size++
}

func (q *Queue) Dequeue() (string, bool) {
	if q.front == nil {
		return "", false
	}
	
	value := q.front.data
	q.front = q.front.next
	if q.front == nil {
		q.rear = nil
	}
	q.size--
	return value, true
}

func (q *Queue) Front() (string, bool) {
	if q.front == nil {
		return "", false
	}
	return q.front.data, true
}

func (q *Queue) IsEmpty() bool {
	return q.front == nil
}

func (q *Queue) Size() int {
	return q.size
}

func (q *Queue) ToJSON() ([]byte, error) {
	var elements []string
	current := q.front
	for current != nil {
		elements = append(elements, current.data)
		current = current.next
	}
	return json.Marshal(elements)
}

func (q *Queue) FromJSON(data []byte) error {
	var elements []string
	if err := json.Unmarshal(data, &elements); err != nil {
		return err
	}
	
	q.front = nil
	q.rear = nil
	q.size = 0
	
	for _, element := range elements {
		q.Enqueue(element)
	}
	return nil
}

func (q *Queue) SaveBinary(writer io.Writer) error {
	if err := binary.Write(writer, binary.LittleEndian, int32(q.size)); err != nil {
		return err
	}
	
	current := q.front
	for current != nil {
		length := int32(len(current.data))
		if err := binary.Write(writer, binary.LittleEndian, length); err != nil {
			return err
		}
		if _, err := writer.Write([]byte(current.data)); err != nil {
			return err
		}
		current = current.next
	}
	return nil
}

func (q *Queue) LoadBinary(reader io.Reader) error {
	var size int32
	if err := binary.Read(reader, binary.LittleEndian, &size); err != nil {
		return err
	}
	
	q.front = nil
	q.rear = nil
	q.size = 0
	
	for i := 0; i < int(size); i++ {
		var length int32
		if err := binary.Read(reader, binary.LittleEndian, &length); err != nil {
			return err
		}
		
		data := make([]byte, length)
		if _, err := reader.Read(data); err != nil {
			return err
		}
		
		q.Enqueue(string(data))
	}
	return nil
}

func (q *Queue) SaveText(writer io.Writer) error {
	w := bufio.NewWriter(writer)
	defer w.Flush()
	
	if _, err := w.WriteString(strconv.Itoa(q.size) + "\n"); err != nil {
		return err
	}
	
	current := q.front
	for current != nil {
		if _, err := w.WriteString(current.data + "\n"); err != nil {
			return err
		}
		current = current.next
	}
	return nil
}

func (q *Queue) LoadText(reader io.Reader) error {
	scanner := bufio.NewScanner(reader)
	
	if !scanner.Scan() {
		return fmt.Errorf("failed to read size")
	}
	
	size, err := strconv.Atoi(strings.TrimSpace(scanner.Text()))
	if err != nil {
		return err
	}
	
	q.front = nil
	q.rear = nil
	q.size = 0
	
	for i := 0; i < size; i++ {
		if !scanner.Scan() {
			return fmt.Errorf("failed to read element %d", i)
		}
		q.Enqueue(strings.TrimSpace(scanner.Text()))
	}
	
	return scanner.Err()
}

func (q *Queue) Print() {
	fmt.Print("Queue: ")
	current := q.front
	for current != nil {
		fmt.Print(current.data + " ")
		current = current.next
	}
	fmt.Println()
}
