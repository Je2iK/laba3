package main

import (
	"bytes"
	"testing"
)

func TestRedBlackTreeConstructorAndInitialState(t *testing.T) {
	tree := NewRedBlackTree()
	
	if !tree.IsEmpty() {
		t.Error("New tree should be empty")
	}
}

func TestRedBlackTreeInsert(t *testing.T) {
	tree := NewRedBlackTree()
	
	tree.Insert("b")
	tree.Insert("a")
	tree.Insert("c")
	tree.Insert("d")
	tree.Insert("e")
	
	if tree.IsEmpty() {
		t.Error("Tree should not be empty after insertions")
	}
	
	if !tree.Search("a") {
		t.Error("Tree should contain 'a'")
	}
	
	if !tree.Search("b") {
		t.Error("Tree should contain 'b'")
	}
	
	if !tree.Search("c") {
		t.Error("Tree should contain 'c'")
	}
	
	if !tree.Search("d") {
		t.Error("Tree should contain 'd'")
	}
	
	if !tree.Search("e") {
		t.Error("Tree should contain 'e'")
	}
	
	if tree.Search("f") {
		t.Error("Tree should not contain 'f'")
	}
}

func TestRedBlackTreeSearch(t *testing.T) {
	tree := NewRedBlackTree()
	
	if tree.Search("test") {
		t.Error("Empty tree should not contain any element")
	}
	
	tree.Insert("test")
	
	if !tree.Search("test") {
		t.Error("Tree should contain 'test'")
	}
	
	if tree.Search("missing") {
		t.Error("Tree should not contain 'missing'")
	}
}

func TestRedBlackTreeJSONSerialization(t *testing.T) {
	tree := NewRedBlackTree()
	tree.Insert("zebra")
	tree.Insert("apple")
	tree.Insert("banana")
	tree.Insert("cherry")
	
	data, err := tree.ToJSON()
	if err != nil {
		t.Fatalf("ToJSON failed: %v", err)
	}
	
	newTree := NewRedBlackTree()
	if err := newTree.FromJSON(data); err != nil {
		t.Fatalf("FromJSON failed: %v", err)
	}
	
	if !newTree.Search("zebra") {
		t.Error("Deserialized tree should contain 'zebra'")
	}
	
	if !newTree.Search("apple") {
		t.Error("Deserialized tree should contain 'apple'")
	}
	
	if !newTree.Search("banana") {
		t.Error("Deserialized tree should contain 'banana'")
	}
	
	if !newTree.Search("cherry") {
		t.Error("Deserialized tree should contain 'cherry'")
	}
}

func TestRedBlackTreeBinarySerialization(t *testing.T) {
	tree := NewRedBlackTree()
	tree.Insert("test1")
	tree.Insert("test2")
	tree.Insert("test3")
	
	var buf bytes.Buffer
	if err := tree.SaveBinary(&buf); err != nil {
		t.Fatalf("SaveBinary failed: %v", err)
	}
	
	newTree := NewRedBlackTree()
	if err := newTree.LoadBinary(&buf); err != nil {
		t.Fatalf("LoadBinary failed: %v", err)
	}
	
	if !newTree.Search("test1") {
		t.Error("Deserialized tree should contain 'test1'")
	}
	
	if !newTree.Search("test2") {
		t.Error("Deserialized tree should contain 'test2'")
	}
	
	if !newTree.Search("test3") {
		t.Error("Deserialized tree should contain 'test3'")
	}
}

func TestRedBlackTreeTextSerialization(t *testing.T) {
	tree := NewRedBlackTree()
	tree.Insert("hello")
	tree.Insert("world")
	tree.Insert("test")
	
	var buf bytes.Buffer
	if err := tree.SaveText(&buf); err != nil {
		t.Fatalf("SaveText failed: %v", err)
	}
	
	newTree := NewRedBlackTree()
	if err := newTree.LoadText(&buf); err != nil {
		t.Fatalf("LoadText failed: %v", err)
	}
	
	if !newTree.Search("hello") {
		t.Error("Deserialized tree should contain 'hello'")
	}
	
	if !newTree.Search("world") {
		t.Error("Deserialized tree should contain 'world'")
	}
	
	if !newTree.Search("test") {
		t.Error("Deserialized tree should contain 'test'")
	}
}

func TestRedBlackTreeEmptySerialization(t *testing.T) {
	tree := NewRedBlackTree()
	
	data, err := tree.ToJSON()
	if err != nil {
		t.Fatalf("ToJSON failed: %v", err)
	}
	
	newTree1 := NewRedBlackTree()
	if err := newTree1.FromJSON(data); err != nil {
		t.Fatalf("FromJSON failed: %v", err)
	}
	
	if !newTree1.IsEmpty() {
		t.Error("Deserialized empty tree should be empty")
	}
	
	var buf bytes.Buffer
	if err := tree.SaveBinary(&buf); err != nil {
		t.Fatalf("SaveBinary failed: %v", err)
	}
	
	newTree2 := NewRedBlackTree()
	if err := newTree2.LoadBinary(&buf); err != nil {
		t.Fatalf("LoadBinary failed: %v", err)
	}
	
	if !newTree2.IsEmpty() {
		t.Error("Deserialized empty tree should be empty")
	}
}

func TestRedBlackTreeComplexOperations(t *testing.T) {
	tree := NewRedBlackTree()
	
	elements := []string{"m", "f", "s", "c", "h", "p", "x", "a", "d", "g", "j", "n", "r", "u", "z"}
	for _, element := range elements {
		tree.Insert(element)
	}
	
	for _, element := range elements {
		if !tree.Search(element) {
			t.Errorf("Tree should contain '%s'", element)
		}
	}
	
	missing := []string{"b", "e", "i", "k", "l", "o", "q", "t", "v", "w", "y"}
	for _, element := range missing {
		if tree.Search(element) {
			t.Errorf("Tree should not contain '%s'", element)
		}
	}
}

func TestRedBlackTreePrint(t *testing.T) {
	tree := NewRedBlackTree()
	tree.Insert("x")
	tree.Insert("y")
	
	tree.Print()
}
