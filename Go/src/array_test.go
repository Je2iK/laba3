package main

import (
	"bytes"
	"testing"
)

func TestArrayConstructorAndInitialState(t *testing.T) {
	arr := NewArray(10)
	
	if !arr.IsEmpty() {
		t.Error("New array should be empty")
	}
	
	if arr.Size() != 0 {
		t.Errorf("New array size should be 0, got %d", arr.Size())
	}
}

func TestArrayInsert(t *testing.T) {
	arr := NewArray(10)
	
	if err := arr.Insert(0, "first"); err != nil {
		t.Fatalf("Insert failed: %v", err)
	}
	
	if arr.IsEmpty() {
		t.Error("Array should not be empty after insert")
	}
	
	if arr.Size() != 1 {
		t.Errorf("Array size should be 1, got %d", arr.Size())
	}
	
	if val, err := arr.Get(0); err != nil || val != "first" {
		t.Errorf("Get(0) should return 'first', got '%s'", val)
	}
	
	arr.Insert(1, "second")
	arr.Insert(1, "middle")
	
	if arr.Size() != 3 {
		t.Errorf("Array size should be 3, got %d", arr.Size())
	}
	
	if val, err := arr.Get(1); err != nil || val != "middle" {
		t.Errorf("Get(1) should return 'middle', got '%s'", val)
	}
	
	if val, err := arr.Get(2); err != nil || val != "second" {
		t.Errorf("Get(2) should return 'second', got '%s'", val)
	}
}

func TestArrayInsertErrors(t *testing.T) {
	arr := NewArray(2)
	
	if err := arr.Insert(1, "test"); err == nil {
		t.Error("Insert at invalid index should return error")
	}
	
	arr.Insert(0, "a")
	arr.Insert(1, "b")
	
	if err := arr.Insert(2, "c"); err == nil {
		t.Error("Insert when array is full should return error")
	}
}

func TestArrayRemove(t *testing.T) {
	arr := NewArray(10)
	arr.Insert(0, "a")
	arr.Insert(1, "b")
	arr.Insert(2, "c")
	
	if err := arr.Remove(1); err != nil {
		t.Fatalf("Remove failed: %v", err)
	}
	
	if arr.Size() != 2 {
		t.Errorf("Array size should be 2, got %d", arr.Size())
	}
	
	if val, err := arr.Get(1); err != nil || val != "c" {
		t.Errorf("Get(1) should return 'c', got '%s'", val)
	}
	
	if err := arr.Remove(5); err == nil {
		t.Error("Remove at invalid index should return error")
	}
}

func TestArraySetGet(t *testing.T) {
	arr := NewArray(10)
	arr.Insert(0, "test")
	
	if err := arr.Set(0, "modified"); err != nil {
		t.Fatalf("Set failed: %v", err)
	}
	
	if val, err := arr.Get(0); err != nil || val != "modified" {
		t.Errorf("Get(0) should return 'modified', got '%s'", val)
	}
	
	if _, err := arr.Get(5); err == nil {
		t.Error("Get at invalid index should return error")
	}
	
	if err := arr.Set(5, "fail"); err == nil {
		t.Error("Set at invalid index should return error")
	}
}

func TestArrayJSONSerialization(t *testing.T) {
	arr := NewArray(10)
	arr.Insert(0, "x")
	arr.Insert(1, "y")
	
	data, err := arr.ToJSON()
	if err != nil {
		t.Fatalf("ToJSON failed: %v", err)
	}
	
	newArr := NewArray(10)
	if err := newArr.FromJSON(data); err != nil {
		t.Fatalf("FromJSON failed: %v", err)
	}
	
	if newArr.Size() != 2 {
		t.Errorf("Deserialized array size should be 2, got %d", newArr.Size())
	}
	
	if val, err := newArr.Get(0); err != nil || val != "x" {
		t.Errorf("Get(0) should return 'x', got '%s'", val)
	}
	
	if val, err := newArr.Get(1); err != nil || val != "y" {
		t.Errorf("Get(1) should return 'y', got '%s'", val)
	}
}

func TestArrayBinarySerialization(t *testing.T) {
	arr := NewArray(10)
	arr.Insert(0, "test1")
	arr.Insert(1, "test2")
	
	var buf bytes.Buffer
	if err := arr.SaveBinary(&buf); err != nil {
		t.Fatalf("SaveBinary failed: %v", err)
	}
	
	newArr := NewArray(10)
	if err := newArr.LoadBinary(&buf); err != nil {
		t.Fatalf("LoadBinary failed: %v", err)
	}
	
	if newArr.Size() != 2 {
		t.Errorf("Deserialized array size should be 2, got %d", newArr.Size())
	}
	
	if val, err := newArr.Get(0); err != nil || val != "test1" {
		t.Errorf("Get(0) should return 'test1', got '%s'", val)
	}
}

func TestArrayTextSerialization(t *testing.T) {
	arr := NewArray(10)
	arr.Insert(0, "hello")
	arr.Insert(1, "world")
	
	var buf bytes.Buffer
	if err := arr.SaveText(&buf); err != nil {
		t.Fatalf("SaveText failed: %v", err)
	}
	
	newArr := NewArray(10)
	if err := newArr.LoadText(&buf); err != nil {
		t.Fatalf("LoadText failed: %v", err)
	}
	
	if newArr.Size() != 2 {
		t.Errorf("Deserialized array size should be 2, got %d", newArr.Size())
	}
	
	if val, err := newArr.Get(0); err != nil || val != "hello" {
		t.Errorf("Get(0) should return 'hello', got '%s'", val)
	}
}

func TestArrayEmptySerialization(t *testing.T) {
	arr := NewArray(10)
	
	data, err := arr.ToJSON()
	if err != nil {
		t.Fatalf("ToJSON failed: %v", err)
	}
	
	newArr := NewArray(10)
	if err := newArr.FromJSON(data); err != nil {
		t.Fatalf("FromJSON failed: %v", err)
	}
	
	if !newArr.IsEmpty() {
		t.Error("Deserialized empty array should be empty")
	}
}

func TestArrayPrint(t *testing.T) {
	arr := NewArray(10)
	arr.Insert(0, "hello")
	
	arr.Print()
}
