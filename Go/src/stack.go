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

type StackNode struct {
	data string
	next *StackNode
}

type Stack struct {
	top  *StackNode
	size int
}

func NewStack() *Stack {
	return &Stack{
		top:  nil,
		size: 0,
	}
}

// Добавляет элемент в стек
func (s *Stack) Push(value string) {
	newNode := &StackNode{
		data: value,
		next: s.top,
	}
	s.top = newNode
	s.size++
}

// Удаляет и возвращает верхний элемент
func (s *Stack) Pop() (string, bool) {
	if s.top == nil {
		return "", false
	}
	value := s.top.data
	s.top = s.top.next
	s.size--
	return value, true
}

func (s *Stack) Top() (string, bool) {
	if s.top == nil {
		return "", false
	}
	return s.top.data, true
}

func (s *Stack) IsEmpty() bool {
	return s.top == nil
}

func (s *Stack) Size() int {
	return s.size
}

func (s *Stack) Contains(value string) bool {
	current := s.top
	for current != nil {
		if current.data == value {
			return true
		}
		current = current.next
	}
	return false
}

// Сериализация в JSON
func (s *Stack) ToJSON() ([]byte, error) {
	var elements []string
	current := s.top
	for current != nil {
		elements = append([]string{current.data}, elements...)
		current = current.next
	}
	return json.Marshal(elements)
}

// Десериализация из JSON
func (s *Stack) FromJSON(data []byte) error {
	var elements []string
	if err := json.Unmarshal(data, &elements); err != nil {
		return err
	}
	
	s.top = nil
	s.size = 0
	
	for _, element := range elements {
		s.Push(element)
	}
	return nil
}

func (s *Stack) SaveBinary(writer io.Writer) error {
	if err := binary.Write(writer, binary.LittleEndian, int32(s.size)); err != nil {
		return err
	}
	
	var elements []string
	current := s.top
	for current != nil {
		elements = append([]string{current.data}, elements...)
		current = current.next
	}
	
	for _, element := range elements {
		length := int32(len(element))
		if err := binary.Write(writer, binary.LittleEndian, length); err != nil {
			return err
		}
		if _, err := writer.Write([]byte(element)); err != nil {
			return err
		}
	}
	return nil
}

func (s *Stack) LoadBinary(reader io.Reader) error {
	var size int32
	if err := binary.Read(reader, binary.LittleEndian, &size); err != nil {
		return err
	}
	
	s.top = nil
	s.size = 0
	
	for i := 0; i < int(size); i++ {
		var length int32
		if err := binary.Read(reader, binary.LittleEndian, &length); err != nil {
			return err
		}
		
		data := make([]byte, length)
		if _, err := reader.Read(data); err != nil {
			return err
		}
		
		s.Push(string(data))
	}
	return nil
}

func (s *Stack) SaveText(writer io.Writer) error {
	w := bufio.NewWriter(writer)
	defer w.Flush()
	
	if _, err := w.WriteString(strconv.Itoa(s.size) + "\n"); err != nil {
		return err
	}
	
	var elements []string
	current := s.top
	for current != nil {
		elements = append([]string{current.data}, elements...)
		current = current.next
	}
	
	for _, element := range elements {
		if _, err := w.WriteString(element + "\n"); err != nil {
			return err
		}
	}
	return nil
}

func (s *Stack) LoadText(reader io.Reader) error {
	scanner := bufio.NewScanner(reader)
	
	if !scanner.Scan() {
		return fmt.Errorf("failed to read size")
	}
	
	size, err := strconv.Atoi(strings.TrimSpace(scanner.Text()))
	if err != nil {
		return err
	}
	
	s.top = nil
	s.size = 0
	
	for i := 0; i < size; i++ {
		if !scanner.Scan() {
			return fmt.Errorf("failed to read element %d", i)
		}
		s.Push(strings.TrimSpace(scanner.Text()))
	}
	
	return scanner.Err()
}

func (s *Stack) Print() {
	fmt.Print("Stack: ")
	current := s.top
	for current != nil {
		fmt.Print(current.data + " ")
		current = current.next
	}
	fmt.Println()
}
