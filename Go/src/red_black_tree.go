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

type Color bool

const (
	RED   Color = false
	BLACK Color = true
)

type TreeNode struct {
	data   string
	color  Color
	left   *TreeNode
	right  *TreeNode
	parent *TreeNode
}

type RedBlackTree struct {
	root *TreeNode
	nil  *TreeNode
}

func NewRedBlackTree() *RedBlackTree {
	nilNode := &TreeNode{color: BLACK}
	return &RedBlackTree{
		root: nilNode,
		nil:  nilNode,
	}
}

func (t *RedBlackTree) leftRotate(x *TreeNode) {
	y := x.right
	x.right = y.left
	if y.left != t.nil {
		y.left.parent = x
	}
	y.parent = x.parent
	if x.parent == t.nil {
		t.root = y
	} else if x == x.parent.left {
		x.parent.left = y
	} else {
		x.parent.right = y
	}
	y.left = x
	x.parent = y
}

func (t *RedBlackTree) rightRotate(x *TreeNode) {
	y := x.left
	x.left = y.right
	if y.right != t.nil {
		y.right.parent = x
	}
	y.parent = x.parent
	if x.parent == t.nil {
		t.root = y
	} else if x == x.parent.right {
		x.parent.right = y
	} else {
		x.parent.left = y
	}
	y.right = x
	x.parent = y
}

func (t *RedBlackTree) Insert(data string) {
	z := &TreeNode{
		data:   data,
		color:  RED,
		left:   t.nil,
		right:  t.nil,
		parent: t.nil,
	}
	
	y := t.nil
	x := t.root
	
	for x != t.nil {
		y = x
		if z.data < x.data {
			x = x.left
		} else {
			x = x.right
		}
	}
	
	z.parent = y
	if y == t.nil {
		t.root = z
	} else if z.data < y.data {
		y.left = z
	} else {
		y.right = z
	}
	
	t.insertFixup(z)
}

func (t *RedBlackTree) insertFixup(z *TreeNode) {
	for z.parent.color == RED {
		if z.parent == z.parent.parent.left {
			y := z.parent.parent.right
			if y.color == RED {
				z.parent.color = BLACK
				y.color = BLACK
				z.parent.parent.color = RED
				z = z.parent.parent
			} else {
				if z == z.parent.right {
					z = z.parent
					t.leftRotate(z)
				}
				z.parent.color = BLACK
				z.parent.parent.color = RED
				t.rightRotate(z.parent.parent)
			}
		} else {
			y := z.parent.parent.left
			if y.color == RED {
				z.parent.color = BLACK
				y.color = BLACK
				z.parent.parent.color = RED
				z = z.parent.parent
			} else {
				if z == z.parent.left {
					z = z.parent
					t.rightRotate(z)
				}
				z.parent.color = BLACK
				z.parent.parent.color = RED
				t.leftRotate(z.parent.parent)
			}
		}
	}
	t.root.color = BLACK
}

func (t *RedBlackTree) Search(data string) bool {
	x := t.root
	for x != t.nil && data != x.data {
		if data < x.data {
			x = x.left
		} else {
			x = x.right
		}
	}
	return x != t.nil
}

func (t *RedBlackTree) IsEmpty() bool {
	return t.root == t.nil
}

func (t *RedBlackTree) inorderTraversal(node *TreeNode, result *[]string) {
	if node != t.nil {
		t.inorderTraversal(node.left, result)
		*result = append(*result, node.data)
		t.inorderTraversal(node.right, result)
	}
}

func (t *RedBlackTree) ToJSON() ([]byte, error) {
	var result []string
	t.inorderTraversal(t.root, &result)
	return json.Marshal(result)
}

func (t *RedBlackTree) FromJSON(data []byte) error {
	var elements []string
	if err := json.Unmarshal(data, &elements); err != nil {
		return err
	}
	
	t.root = t.nil
	
	for _, element := range elements {
		t.Insert(element)
	}
	return nil
}

func (t *RedBlackTree) SaveBinary(writer io.Writer) error {
	var result []string
	t.inorderTraversal(t.root, &result)
	
	if err := binary.Write(writer, binary.LittleEndian, int32(len(result))); err != nil {
		return err
	}
	
	for _, element := range result {
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

func (t *RedBlackTree) LoadBinary(reader io.Reader) error {
	var size int32
	if err := binary.Read(reader, binary.LittleEndian, &size); err != nil {
		return err
	}
	
	t.root = t.nil
	
	for i := 0; i < int(size); i++ {
		var length int32
		if err := binary.Read(reader, binary.LittleEndian, &length); err != nil {
			return err
		}
		
		data := make([]byte, length)
		if _, err := reader.Read(data); err != nil {
			return err
		}
		
		t.Insert(string(data))
	}
	return nil
}

func (t *RedBlackTree) SaveText(writer io.Writer) error {
	var result []string
	t.inorderTraversal(t.root, &result)
	
	w := bufio.NewWriter(writer)
	defer w.Flush()
	
	if _, err := w.WriteString(strconv.Itoa(len(result)) + "\n"); err != nil {
		return err
	}
	
	for _, element := range result {
		if _, err := w.WriteString(element + "\n"); err != nil {
			return err
		}
	}
	return nil
}

func (t *RedBlackTree) LoadText(reader io.Reader) error {
	scanner := bufio.NewScanner(reader)
	
	if !scanner.Scan() {
		return fmt.Errorf("failed to read size")
	}
	
	size, err := strconv.Atoi(strings.TrimSpace(scanner.Text()))
	if err != nil {
		return err
	}
	
	t.root = t.nil
	
	for i := 0; i < size; i++ {
		if !scanner.Scan() {
			return fmt.Errorf("failed to read element %d", i)
		}
		t.Insert(strings.TrimSpace(scanner.Text()))
	}
	
	return scanner.Err()
}

func (t *RedBlackTree) Print() {
	var result []string
	t.inorderTraversal(t.root, &result)
	
	fmt.Print("RedBlackTree: ")
	for _, element := range result {
		fmt.Print(element + " ")
	}
	fmt.Println()
}
