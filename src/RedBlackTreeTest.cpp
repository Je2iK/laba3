#include <gtest/gtest.h>
#include "include/RedBlackTree.hpp"
#include <sstream>

TEST(RedBlackTreeTest, ConstructorAndInitialState) {
  RedBlackTree tree;
  EXPECT_TRUE(tree.empty());
}

TEST(RedBlackTreeTest, Insert) {
  RedBlackTree tree;
  tree.insert("b");
  tree.insert("a");
  tree.insert("c");
  tree.insert("d");
  tree.insert("e");
  
  EXPECT_FALSE(tree.empty());
  EXPECT_TRUE(tree.search("a"));
  EXPECT_TRUE(tree.search("b"));
  EXPECT_TRUE(tree.search("c"));
  EXPECT_TRUE(tree.search("d"));
  EXPECT_TRUE(tree.search("e"));
  EXPECT_FALSE(tree.search("f"));
}

TEST(RedBlackTreeTest, Remove) {
  RedBlackTree tree;
  tree.insert("b");
  tree.insert("a");
  tree.insert("c");
  tree.insert("d");
  
  EXPECT_TRUE(tree.remove("b"));
  EXPECT_FALSE(tree.search("b"));
  EXPECT_TRUE(tree.search("a"));
  EXPECT_TRUE(tree.search("c"));
  EXPECT_TRUE(tree.search("d"));
  
  EXPECT_FALSE(tree.remove("nonexistent"));
  
  EXPECT_TRUE(tree.remove("a"));
  EXPECT_TRUE(tree.remove("c"));
  EXPECT_TRUE(tree.remove("d"));
  EXPECT_TRUE(tree.empty());
}

TEST(RedBlackTreeTest, SerializeDeserialize) {
  RedBlackTree tree;
  tree.insert("zebra");
  tree.insert("apple");
  tree.insert("banana");
  tree.insert("cherry");
  
  nlohmann::json j = tree.serialize();
  RedBlackTree newTree;
  newTree.deserialize(j);
  
  EXPECT_TRUE(newTree.search("zebra"));
  EXPECT_TRUE(newTree.search("apple"));
  EXPECT_TRUE(newTree.search("banana"));
  EXPECT_TRUE(newTree.search("cherry"));
}

TEST(RedBlackTreeTest, BinarySerialization) {
  RedBlackTree tree;
  tree.insert("test1");
  tree.insert("test2");
  tree.insert("test3");
  
  std::ostringstream oss;
  tree.serializeBinary(oss);
  
  RedBlackTree newTree;
  std::istringstream iss(oss.str());
  newTree.deserializeBinary(iss);
  
  EXPECT_TRUE(newTree.search("test1"));
  EXPECT_TRUE(newTree.search("test2"));
  EXPECT_TRUE(newTree.search("test3"));
}

TEST(RedBlackTreeTest, TextSerialization) {
  RedBlackTree tree;
  tree.insert("hello");
  tree.insert("world");
  tree.insert("test");
  
  std::ostringstream oss;
  tree.serializeText(oss);
  
  RedBlackTree newTree;
  std::istringstream iss(oss.str());
  newTree.deserializeText(iss);
  
  EXPECT_TRUE(newTree.search("hello"));
  EXPECT_TRUE(newTree.search("world"));
  EXPECT_TRUE(newTree.search("test"));
}

TEST(RedBlackTreeTest, EmptyTreeSerialization) {
  RedBlackTree tree;
  
  nlohmann::json j = tree.serialize();
  RedBlackTree newTree1;
  newTree1.deserialize(j);
  EXPECT_TRUE(newTree1.empty());
  
  std::ostringstream oss;
  tree.serializeBinary(oss);
  RedBlackTree newTree2;
  std::istringstream iss(oss.str());
  newTree2.deserializeBinary(iss);
  EXPECT_TRUE(newTree2.empty());
  
  std::ostringstream oss2;
  tree.serializeText(oss2);
  RedBlackTree newTree3;
  std::istringstream iss2(oss2.str());
  newTree3.deserializeText(iss2);
  EXPECT_TRUE(newTree3.empty());
}

TEST(RedBlackTreeTest, Print) {
  RedBlackTree tree;
  tree.insert("x");
  tree.insert("y");
  tree.print(); // Для покрытия метода print
}

TEST(RedBlackTreeTest, ComplexOperations) {
  RedBlackTree tree;
  
  for (int i = 0; i < 10; ++i) {
    tree.insert("item" + std::to_string(i));
  }
  
  for (int i = 0; i < 10; ++i) {
    EXPECT_TRUE(tree.search("item" + std::to_string(i)));
  }
  
  for (int i = 0; i < 5; ++i) {
    EXPECT_TRUE(tree.remove("item" + std::to_string(i)));
  }
  
  for (int i = 5; i < 10; ++i) {
    EXPECT_TRUE(tree.search("item" + std::to_string(i)));
  }
}
