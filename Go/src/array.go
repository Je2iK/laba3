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

type Array struct {
	data     []string
	size     int
	capacity int
}

func NewArray(capacity int) *Array {
	if capacity <= 0 {
		capacity = 10
	}
	return &Array{
		data:     make([]string, capacity),
		size:     0,
		capacity: capacity,
	}
}

func (a *Array) Insert(index int, value string) error {
	if index < 0 || index > a.size {
		return fmt.Errorf("index out of range")
	}
	if a.size >= a.capacity {
		return fmt.Errorf("array is full")
	}
	
	for i := a.size; i > index; i-- {
		a.data[i] = a.data[i-1]
	}
	a.data[index] = value
	a.size++
	return nil
}

func (a *Array) Remove(index int) error {
	if index < 0 || index >= a.size {
		return fmt.Errorf("index out of range")
	}
	
	for i := index; i < a.size-1; i++ {
		a.data[i] = a.data[i+1]
	}
	a.size--
	return nil
}

func (a *Array) Get(index int) (string, error) {
	if index < 0 || index >= a.size {
		return "", fmt.Errorf("index out of range")
	}
	return a.data[index], nil
}

func (a *Array) Set(index int, value string) error {
	if index < 0 || index >= a.size {
		return fmt.Errorf("index out of range")
	}
	a.data[index] = value
	return nil
}

func (a *Array) Size() int {
	return a.size
}

func (a *Array) IsEmpty() bool {
	return a.size == 0
}

func (a *Array) ToJSON() ([]byte, error) {
	elements := make([]string, a.size)
	copy(elements, a.data[:a.size])
	return json.Marshal(elements)
}

func (a *Array) FromJSON(data []byte) error {
	var elements []string
	if err := json.Unmarshal(data, &elements); err != nil {
		return err
	}
	
	a.size = 0
	for _, element := range elements {
		if a.size < a.capacity {
			a.data[a.size] = element
			a.size++
		}
	}
	return nil
}

func (a *Array) SaveBinary(writer io.Writer) error {
	if err := binary.Write(writer, binary.LittleEndian, int32(a.size)); err != nil {
		return err
	}
	
	for i := 0; i < a.size; i++ {
		length := int32(len(a.data[i]))
		if err := binary.Write(writer, binary.LittleEndian, length); err != nil {
			return err
		}
		if _, err := writer.Write([]byte(a.data[i])); err != nil {
			return err
		}
	}
	return nil
}

func (a *Array) LoadBinary(reader io.Reader) error {
	var size int32
	if err := binary.Read(reader, binary.LittleEndian, &size); err != nil {
		return err
	}
	
	a.size = 0
	for i := 0; i < int(size) && i < a.capacity; i++ {
		var length int32
		if err := binary.Read(reader, binary.LittleEndian, &length); err != nil {
			return err
		}
		
		data := make([]byte, length)
		if _, err := reader.Read(data); err != nil {
			return err
		}
		
		a.data[a.size] = string(data)
		a.size++
	}
	return nil
}

func (a *Array) SaveText(writer io.Writer) error {
	w := bufio.NewWriter(writer)
	defer w.Flush()
	
	if _, err := w.WriteString(strconv.Itoa(a.size) + "\n"); err != nil {
		return err
	}
	
	for i := 0; i < a.size; i++ {
		if _, err := w.WriteString(a.data[i] + "\n"); err != nil {
			return err
		}
	}
	return nil
}

func (a *Array) LoadText(reader io.Reader) error {
	scanner := bufio.NewScanner(reader)
	
	if !scanner.Scan() {
		return fmt.Errorf("failed to read size")
	}
	
	size, err := strconv.Atoi(strings.TrimSpace(scanner.Text()))
	if err != nil {
		return err
	}
	
	a.size = 0
	for i := 0; i < size && i < a.capacity; i++ {
		if !scanner.Scan() {
			return fmt.Errorf("failed to read element %d", i)
		}
		a.data[a.size] = strings.TrimSpace(scanner.Text())
		a.size++
	}
	
	return scanner.Err()
}

func (a *Array) Print() {
	fmt.Print("Array: ")
	for i := 0; i < a.size; i++ {
		fmt.Print(a.data[i] + " ")
	}
	fmt.Println()
}
