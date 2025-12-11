package main

import (
	"os"
	"testing"
)

func TestChainHashTableBasic(t *testing.T) {
	ht := NewChainHashTable(8)

	ht.Insert("key1", "value1")
	ht.Insert("key2", "value2")
	
	if val, ok := ht.Get("key1"); !ok || val != "value1" {
		t.Errorf("Expected value1, got %s", val)
	}
	
	if val, ok := ht.Get("key2"); !ok || val != "value2" {
		t.Errorf("Expected value2, got %s", val)
	}
	
	if ht.Size() != 2 {
		t.Errorf("Expected size 2, got %d", ht.Size())
	}
	
	if !ht.Remove("key1") {
		t.Error("Failed to remove key1")
	}
	
	if _, ok := ht.Get("key1"); ok {
		t.Error("key1 should not exist after removal")
	}
	
	if ht.Size() != 1 {
		t.Errorf("Expected size 1 after removal, got %d", ht.Size())
	}
	
	ht.Remove("key2")
	if !ht.IsEmpty() {
		t.Error("Hash table should be empty")
	}
}

func TestChainHashTableJSON(t *testing.T) {
	ht := NewChainHashTable(4)
	ht.Insert("test", "data")
	
	jsonStr, err := ht.ToJSON()
	if err != nil {
		t.Fatalf("ToJSON failed: %v", err)
	}
	
	newHt := NewChainHashTable(4)
	err = newHt.FromJSON(jsonStr)
	if err != nil {
		t.Fatalf("FromJSON failed: %v", err)
	}
}

func TestChainHashTableBinary(t *testing.T) {
	ht := NewChainHashTable(4)
	ht.Insert("binary", "test")
	
	filename := "test_hash.bin"
	defer os.Remove(filename)
	
	err := ht.SaveBinary(filename)
	if err != nil {
		t.Fatalf("SaveBinary failed: %v", err)
	}
	
	newHt := NewChainHashTable(4)
	err = newHt.LoadBinary(filename)
	if err != nil {
		t.Fatalf("LoadBinary failed: %v", err)
	}
}

func TestChainHashTableText(t *testing.T) {
	ht := NewChainHashTable(4)
	ht.Insert("text", "format")
	
	filename := "test_hash.txt"
	defer os.Remove(filename)
	
	err := ht.SaveText(filename)
	if err != nil {
		t.Fatalf("SaveText failed: %v", err)
	}
	
	newHt := NewChainHashTable(4)
	err = newHt.LoadText(filename)
	if err != nil {
		t.Fatalf("LoadText failed: %v", err)
	}
}

func TestChainHashTablePrint(t *testing.T) {
	ht := NewChainHashTable(4)
	ht.Insert("print", "test")
	ht.Print() // Just call to increase coverage
}

func TestChainHashTableEdgeCases(t *testing.T) {
	ht := NewChainHashTable(0)
	if len(ht.buckets) != 16 {
		t.Error("Should default to 16 buckets")
	}
	
	ht2 := NewChainHashTable(-5)
	if len(ht2.buckets) != 16 {
		t.Error("Should default to 16 buckets for negative capacity")
	}
	
	ht.Insert("same", "old")
	ht.Insert("same", "new")
	if val, _ := ht.Get("same"); val != "new" {
		t.Error("Should update existing key")
	}
	
	if ht.Remove("nonexistent") {
		t.Error("Should return false for non-existent key")
	}
}
