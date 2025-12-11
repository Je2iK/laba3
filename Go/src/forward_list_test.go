package main

import "testing"

func TestForwardListConstructorAndInitialState(t *testing.T) {
	list := NewForwardList()
	
	if !list.IsEmpty() {
		t.Error("New list should be empty")
	}
	
	if list.Size() != 0 {
		t.Errorf("New list size should be 0, got %d", list.Size())
	}
}

func TestForwardListPushFront(t *testing.T) {
	list := NewForwardList()
	
	list.PushFront("first")
	if list.IsEmpty() {
		t.Error("List should not be empty after push")
	}
	
	if list.Size() != 1 {
		t.Errorf("List size should be 1, got %d", list.Size())
	}
	
	if val, err := list.Get(0); err != nil || val != "first" {
		t.Errorf("Get(0) should return 'first', got '%s'", val)
	}
	
	list.PushFront("second")
	if list.Size() != 2 {
		t.Errorf("List size should be 2, got %d", list.Size())
	}
	
	if val, err := list.Get(0); err != nil || val != "second" {
		t.Errorf("Get(0) should return 'second', got '%s'", val)
	}
}

func TestForwardListPopFront(t *testing.T) {
	list := NewForwardList()
	list.PushFront("first")
	list.PushFront("second")
	
	if val, ok := list.PopFront(); !ok || val != "second" {
		t.Errorf("PopFront should return 'second', got '%s'", val)
	}
	
	if list.Size() != 1 {
		t.Errorf("List size should be 1, got %d", list.Size())
	}
	
	list.PopFront()
	if !list.IsEmpty() {
		t.Error("List should be empty after popping all elements")
	}
	
	if _, ok := list.PopFront(); ok {
		t.Error("PopFront on empty list should return false")
	}
}

func TestForwardListGet(t *testing.T) {
	list := NewForwardList()
	list.PushFront("test")
	
	if val, err := list.Get(0); err != nil || val != "test" {
		t.Errorf("Get(0) should return 'test', got '%s'", val)
	}
	
	if _, err := list.Get(10); err == nil {
		t.Error("Get(10) should return error")
	}
}

func TestForwardListJSONSerialization(t *testing.T) {
	list := NewForwardList()
	list.PushFront("z")
	list.PushFront("y")
	list.PushFront("x")
	
	data, err := list.ToJSON()
	if err != nil {
		t.Fatalf("ToJSON failed: %v", err)
	}
	
	newList := NewForwardList()
	if err := newList.FromJSON(data); err != nil {
		t.Fatalf("FromJSON failed: %v", err)
	}
	
	if newList.Size() != 3 {
		t.Errorf("Deserialized list size should be 3, got %d", newList.Size())
	}
	
	if val, err := newList.Get(0); err != nil || val != "x" {
		t.Errorf("Get(0) should return 'x', got '%s'", val)
	}
}

func TestForwardListPrint(t *testing.T) {
	list := NewForwardList()
	list.PushFront("test")
	
	list.Print()
}
