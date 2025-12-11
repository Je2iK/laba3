package main

import (
	"bytes"
	"testing"
)

func TestQueueConstructorAndInitialState(t *testing.T) {
	queue := NewQueue()
	
	if !queue.IsEmpty() {
		t.Error("New queue should be empty")
	}
	
	if queue.Size() != 0 {
		t.Errorf("New queue size should be 0, got %d", queue.Size())
	}
	
	if _, ok := queue.Front(); ok {
		t.Error("Front() on empty queue should return false")
	}
}

func TestQueueEnqueue(t *testing.T) {
	queue := NewQueue()
	
	queue.Enqueue("first")
	if queue.IsEmpty() {
		t.Error("Queue should not be empty after enqueue")
	}
	
	if queue.Size() != 1 {
		t.Errorf("Queue size should be 1, got %d", queue.Size())
	}
	
	if front, ok := queue.Front(); !ok || front != "first" {
		t.Errorf("Front should be 'first', got '%s'", front)
	}
	
	queue.Enqueue("second")
	if queue.Size() != 2 {
		t.Errorf("Queue size should be 2, got %d", queue.Size())
	}
	
	if front, ok := queue.Front(); !ok || front != "first" {
		t.Errorf("Front should still be 'first', got '%s'", front)
	}
}

func TestQueueDequeue(t *testing.T) {
	queue := NewQueue()
	queue.Enqueue("first")
	queue.Enqueue("second")
	
	if val, ok := queue.Dequeue(); !ok || val != "first" {
		t.Errorf("Dequeue should return 'first', got '%s'", val)
	}
	
	if queue.Size() != 1 {
		t.Errorf("Queue size should be 1, got %d", queue.Size())
	}
	
	if front, ok := queue.Front(); !ok || front != "second" {
		t.Errorf("Front should be 'second', got '%s'", front)
	}
	
	queue.Dequeue()
	if !queue.IsEmpty() {
		t.Error("Queue should be empty after dequeuing all elements")
	}
	
	if _, ok := queue.Dequeue(); ok {
		t.Error("Dequeue on empty queue should return false")
	}
}

func TestQueueJSONSerialization(t *testing.T) {
	queue := NewQueue()
	queue.Enqueue("a")
	queue.Enqueue("b")
	queue.Enqueue("c")
	
	data, err := queue.ToJSON()
	if err != nil {
		t.Fatalf("ToJSON failed: %v", err)
	}
	
	newQueue := NewQueue()
	if err := newQueue.FromJSON(data); err != nil {
		t.Fatalf("FromJSON failed: %v", err)
	}
	
	if newQueue.Size() != 3 {
		t.Errorf("Deserialized queue size should be 3, got %d", newQueue.Size())
	}
	
	if front, ok := newQueue.Front(); !ok || front != "a" {
		t.Errorf("Front should be 'a', got '%s'", front)
	}
}

func TestQueueBinarySerialization(t *testing.T) {
	queue := NewQueue()
	queue.Enqueue("test1")
	queue.Enqueue("test2")
	
	var buf bytes.Buffer
	if err := queue.SaveBinary(&buf); err != nil {
		t.Fatalf("SaveBinary failed: %v", err)
	}
	
	newQueue := NewQueue()
	if err := newQueue.LoadBinary(&buf); err != nil {
		t.Fatalf("LoadBinary failed: %v", err)
	}
	
	if newQueue.Size() != 2 {
		t.Errorf("Deserialized queue size should be 2, got %d", newQueue.Size())
	}
	
	if front, ok := newQueue.Front(); !ok || front != "test1" {
		t.Errorf("Front should be 'test1', got '%s'", front)
	}
}

func TestQueueTextSerialization(t *testing.T) {
	queue := NewQueue()
	queue.Enqueue("hello")
	queue.Enqueue("world")
	
	var buf bytes.Buffer
	if err := queue.SaveText(&buf); err != nil {
		t.Fatalf("SaveText failed: %v", err)
	}
	
	newQueue := NewQueue()
	if err := newQueue.LoadText(&buf); err != nil {
		t.Fatalf("LoadText failed: %v", err)
	}
	
	if newQueue.Size() != 2 {
		t.Errorf("Deserialized queue size should be 2, got %d", newQueue.Size())
	}
	
	if front, ok := newQueue.Front(); !ok || front != "hello" {
		t.Errorf("Front should be 'hello', got '%s'", front)
	}
}

func TestQueueComplexOperations(t *testing.T) {
	queue := NewQueue()
	
	for i := 0; i < 5; i++ {
		queue.Enqueue("item" + string(rune('0'+i)))
	}
	
	if queue.Size() != 5 {
		t.Errorf("Queue size should be 5, got %d", queue.Size())
	}
	
	for i := 0; i < 3; i++ {
		queue.Dequeue()
	}
	
	if queue.Size() != 2 {
		t.Errorf("Queue size should be 2, got %d", queue.Size())
	}
	
	if front, ok := queue.Front(); !ok || front != "item3" {
		t.Errorf("Front should be 'item3', got '%s'", front)
	}
}

func TestQueuePrint(t *testing.T) {
	queue := NewQueue()
	queue.Enqueue("x")
	queue.Enqueue("y")
	
	queue.Print()
}
