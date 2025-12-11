package main

import (
	"encoding/json"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type HashNode struct {
	Key   string `json:"key"`
	Value string `json:"value"`
}

type ChainHashTable struct {
	buckets [][]HashNode `json:"buckets"`
	size    int          `json:"size"`
}

func NewChainHashTable(capacity int) *ChainHashTable {
	if capacity <= 0 {
		capacity = 16
	}
	return &ChainHashTable{
		buckets: make([][]HashNode, capacity),
		size:    0,
	}
}

func (ht *ChainHashTable) hash(key string) int {
	if len(ht.buckets) == 0 {
		return 0
	}
	hash := 0
	for _, char := range key {
		hash = (hash*31 + int(char)) % len(ht.buckets)
	}
	if hash < 0 {
		hash = -hash
	}
	return hash
}

// Вставляет пару ключ-значение
func (ht *ChainHashTable) Insert(key, value string) {
	index := ht.hash(key)
	
	for i, node := range ht.buckets[index] {
		if node.Key == key {
			ht.buckets[index][i].Value = value
			return
		}
	}
	
	ht.buckets[index] = append(ht.buckets[index], HashNode{Key: key, Value: value})
	ht.size++
}

// Получает значение по ключу
func (ht *ChainHashTable) Get(key string) (string, bool) {
	index := ht.hash(key)
	
	for _, node := range ht.buckets[index] {
		if node.Key == key {
			return node.Value, true
		}
	}
	return "", false
}

// Удаляет элемент по ключу
func (ht *ChainHashTable) Remove(key string) bool {
	index := ht.hash(key)
	
	for i, node := range ht.buckets[index] {
		if node.Key == key {
			ht.buckets[index] = append(ht.buckets[index][:i], ht.buckets[index][i+1:]...)
			ht.size--
			return true
		}
	}
	return false
}

func (ht *ChainHashTable) Size() int {
	return ht.size
}

func (ht *ChainHashTable) IsEmpty() bool {
	return ht.size == 0
}

func (ht *ChainHashTable) ToJSON() (string, error) {
	data, err := json.Marshal(ht)
	return string(data), err
}

func (ht *ChainHashTable) FromJSON(jsonStr string) error {
	err := json.Unmarshal([]byte(jsonStr), ht)
	if err != nil {
		return err
	}
	
	if ht.buckets == nil {
		ht.buckets = make([][]HashNode, 16)
	}
	
	for i := range ht.buckets {
		if ht.buckets[i] == nil {
			ht.buckets[i] = []HashNode{}
		}
	}
	
	return nil
}

func (ht *ChainHashTable) SaveBinary(filename string) error {
	jsonStr, err := ht.ToJSON()
	if err != nil {
		return err
	}
	return os.WriteFile(filename, []byte(jsonStr), 0644)
}

func (ht *ChainHashTable) LoadBinary(filename string) error {
	data, err := os.ReadFile(filename)
	if err != nil {
		return err
	}
	return ht.FromJSON(string(data))
}

func (ht *ChainHashTable) SaveText(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()
	
	fmt.Fprintf(file, "%d\n", len(ht.buckets))
	fmt.Fprintf(file, "%d\n", ht.size)
	
	for _, bucket := range ht.buckets {
		fmt.Fprintf(file, "%d\n", len(bucket))
		for _, node := range bucket {
			fmt.Fprintf(file, "%s %s\n", node.Key, node.Value)
		}
	}
	return nil
}

func (ht *ChainHashTable) LoadText(filename string) error {
	data, err := os.ReadFile(filename)
	if err != nil {
		return err
	}
	
	lines := strings.Split(strings.TrimSpace(string(data)), "\n")
	if len(lines) < 2 {
		return fmt.Errorf("invalid file format")
	}
	
	capacity, err := strconv.Atoi(lines[0])
	if err != nil {
		return err
	}
	
	size, err := strconv.Atoi(lines[1])
	if err != nil {
		return err
	}
	
	ht.buckets = make([][]HashNode, capacity)
	ht.size = size
	
	lineIndex := 2
	for i := 0; i < capacity && lineIndex < len(lines); i++ {
		bucketSize, err := strconv.Atoi(lines[lineIndex])
		if err != nil {
			return err
		}
		lineIndex++
		
		for j := 0; j < bucketSize && lineIndex < len(lines); j++ {
			parts := strings.SplitN(lines[lineIndex], " ", 2)
			if len(parts) == 2 {
				ht.buckets[i] = append(ht.buckets[i], HashNode{Key: parts[0], Value: parts[1]})
			}
			lineIndex++
		}
	}
	return nil
}

func (ht *ChainHashTable) Print() {
	for _, bucket := range ht.buckets {
		for _, node := range bucket {
			fmt.Printf("%s:%s ", node.Key, node.Value)
		}
	}
}
