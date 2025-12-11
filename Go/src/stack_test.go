package main

import (
	"bytes"
	"testing"
)

func TestStackConstructorAndInitialState(t *testing.T) {
	stack := NewStack()
	
	if !stack.IsEmpty() {
		t.Error("New stack should be empty")
	}
	
	if stack.Size() != 0 {
		t.Errorf("New stack size should be 0, got %d", stack.Size())
	}
	
	if _, ok := stack.Top(); ok {
		t.Error("Top() on empty stack should return false")
	}
}

func TestStackPush(t *testing.T) {
	stack := NewStack()
	
	stack.Push("first")
	if stack.IsEmpty() {
		t.Error("Stack should not be empty after push")
	}
	
	if stack.Size() != 1 {
		t.Errorf("Stack size should be 1, got %d", stack.Size())
	}
	
	if top, ok := stack.Top(); !ok || top != "first" {
		t.Errorf("Top should be 'first', got '%s'", top)
	}
	
	stack.Push("second")
	if stack.Size() != 2 {
		t.Errorf("Stack size should be 2, got %d", stack.Size())
	}
	
	if top, ok := stack.Top(); !ok || top != "second" {
		t.Errorf("Top should be 'second', got '%s'", top)
	}
}

func TestStackPop(t *testing.T) {
	stack := NewStack()
	stack.Push("first")
	stack.Push("second")
	
	if val, ok := stack.Pop(); !ok || val != "second" {
		t.Errorf("Pop should return 'second', got '%s'", val)
	}
	
	if stack.Size() != 1 {
		t.Errorf("Stack size should be 1, got %d", stack.Size())
	}
	
	if top, ok := stack.Top(); !ok || top != "first" {
		t.Errorf("Top should be 'first', got '%s'", top)
	}
	
	stack.Pop()
	if !stack.IsEmpty() {
		t.Error("Stack should be empty after popping all elements")
	}
	
	if _, ok := stack.Pop(); ok {
		t.Error("Pop on empty stack should return false")
	}
}

func TestStackContains(t *testing.T) {
	stack := NewStack()
	
	if stack.Contains("test") {
		t.Error("Empty stack should not contain any element")
	}
	
	stack.Push("first")
	stack.Push("second")
	
	if !stack.Contains("first") {
		t.Error("Stack should contain 'first'")
	}
	
	if !stack.Contains("second") {
		t.Error("Stack should contain 'second'")
	}
	
	if stack.Contains("third") {
		t.Error("Stack should not contain 'third'")
	}
}

func TestStackJSONSerialization(t *testing.T) {
	stack := NewStack()
	stack.Push("bottom")
	stack.Push("middle")
	stack.Push("top")
	
	data, err := stack.ToJSON()
	if err != nil {
		t.Fatalf("ToJSON failed: %v", err)
	}
	
	newStack := NewStack()
	if err := newStack.FromJSON(data); err != nil {
		t.Fatalf("FromJSON failed: %v", err)
	}
	
	if newStack.Size() != 3 {
		t.Errorf("Deserialized stack size should be 3, got %d", newStack.Size())
	}
	
	if top, ok := newStack.Top(); !ok || top != "top" {
		t.Errorf("Top should be 'top', got '%s'", top)
	}
}

func TestStackBinarySerialization(t *testing.T) {
	stack := NewStack()
	stack.Push("test1")
	stack.Push("test2")
	
	var buf bytes.Buffer
	if err := stack.SaveBinary(&buf); err != nil {
		t.Fatalf("SaveBinary failed: %v", err)
	}
	
	newStack := NewStack()
	if err := newStack.LoadBinary(&buf); err != nil {
		t.Fatalf("LoadBinary failed: %v", err)
	}
	
	if newStack.Size() != 2 {
		t.Errorf("Deserialized stack size should be 2, got %d", newStack.Size())
	}
	
	if top, ok := newStack.Top(); !ok || top != "test2" {
		t.Errorf("Top should be 'test2', got '%s'", top)
	}
}

func TestStackTextSerialization(t *testing.T) {
	stack := NewStack()
	stack.Push("hello")
	stack.Push("world")
	
	var buf bytes.Buffer
	if err := stack.SaveText(&buf); err != nil {
		t.Fatalf("SaveText failed: %v", err)
	}
	
	newStack := NewStack()
	if err := newStack.LoadText(&buf); err != nil {
		t.Fatalf("LoadText failed: %v", err)
	}
	
	if newStack.Size() != 2 {
		t.Errorf("Deserialized stack size should be 2, got %d", newStack.Size())
	}
	
	if top, ok := newStack.Top(); !ok || top != "world" {
		t.Errorf("Top should be 'world', got '%s'", top)
	}
}

func TestStackEmptySerialization(t *testing.T) {
	stack := NewStack()
	
	data, err := stack.ToJSON()
	if err != nil {
		t.Fatalf("ToJSON failed: %v", err)
	}
	
	newStack1 := NewStack()
	if err := newStack1.FromJSON(data); err != nil {
		t.Fatalf("FromJSON failed: %v", err)
	}
	
	if !newStack1.IsEmpty() {
		t.Error("Deserialized empty stack should be empty")
	}
	
	var buf bytes.Buffer
	if err := stack.SaveBinary(&buf); err != nil {
		t.Fatalf("SaveBinary failed: %v", err)
	}
	
	newStack2 := NewStack()
	if err := newStack2.LoadBinary(&buf); err != nil {
		t.Fatalf("LoadBinary failed: %v", err)
	}
	
	if !newStack2.IsEmpty() {
		t.Error("Deserialized empty stack should be empty")
	}
}

func TestStackPrint(t *testing.T) {
	stack := NewStack()
	stack.Push("a")
	stack.Push("b")
	
	stack.Print()
}
