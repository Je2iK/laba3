#include <gtest/gtest.h>
#include "include/RedBlackTree.hpp"
#include <sstream>

TEST(RedBlackTreeTest, ConstructorAndInitialState) {
  RedBlackTree tree;
  EXPECT_TRUE(tree.isEmpty());
}

TEST(RedBlackTreeTest, Insert) {
  RedBlackTree tree;
  tree.insert("b");
  tree.insert("a");
  tree.insert("c");
  tree.insert("d");
  tree.insert("e");
  
  EXPECT_FALSE(tree.isEmpty());
  EXPECT_TRUE(tree.search("a"));
  EXPECT_TRUE(tree.search("b"));
  EXPECT_TRUE(tree.search("c"));
  EXPECT_TRUE(tree.search("d"));
  EXPECT_TRUE(tree.search("e"));
  EXPECT_FALSE(tree.search("f"));
}

TEST(RedBlackTreeTest, RotationCoverage) {
  RedBlackTree tree;
  // Покрытие левых и правых ротаций
  tree.insert("m");
  tree.insert("f");
  tree.insert("s");
  tree.insert("c");
  tree.insert("h");
  tree.insert("p");
  tree.insert("w");
  tree.insert("a");
  tree.insert("d");
  tree.insert("g");
  tree.insert("j");
  tree.insert("n");
  tree.insert("r");
  tree.insert("u");
  tree.insert("z");
  tree.insert("b");
  tree.insert("e");
  tree.insert("i");
  tree.insert("k");
  tree.insert("l");
  tree.insert("o");
  tree.insert("q");
  tree.insert("t");
  tree.insert("v");
  tree.insert("x");
  tree.insert("y");
}

TEST(RedBlackTreeTest, ComplexInsertions) {
  RedBlackTree tree;
  // Последовательные вставки для покрытия всех случаев fixup
  for (int i = 1; i <= 30; i++) {
    tree.insert(std::to_string(i));
  }
  for (int i = 1; i <= 30; i++) {
    EXPECT_TRUE(tree.search(std::to_string(i)));
  }
}

TEST(RedBlackTreeTest, SerializeDeserialize) {
  RedBlackTree tree;
  tree.insert("zebra");
  tree.insert("apple");
  tree.insert("banana");
  tree.insert("cherry");
  tree.insert("date");
  
  nlohmann::json json = tree.serialize();
  RedBlackTree newTree;
  newTree.deserialize(json);
  
  EXPECT_TRUE(newTree.search("zebra"));
  EXPECT_TRUE(newTree.search("apple"));
  EXPECT_TRUE(newTree.search("banana"));
  EXPECT_TRUE(newTree.search("cherry"));
  EXPECT_TRUE(newTree.search("date"));
  EXPECT_FALSE(newTree.search("elderberry"));
}

TEST(RedBlackTreeTest, BinarySerialization) {
  RedBlackTree tree;
  tree.insert("gamma");
  tree.insert("alpha");
  tree.insert("beta");
  tree.insert("delta");
  tree.insert("epsilon");
  
  std::ostringstream oss;
  tree.serializeBinary(oss);
  
  std::istringstream iss(oss.str());
  RedBlackTree newTree;
  newTree.deserializeBinary(iss);
  
  EXPECT_TRUE(newTree.search("gamma"));
  EXPECT_TRUE(newTree.search("alpha"));
  EXPECT_TRUE(newTree.search("beta"));
  EXPECT_TRUE(newTree.search("delta"));
  EXPECT_TRUE(newTree.search("epsilon"));
  EXPECT_FALSE(newTree.search("zeta"));
}

TEST(RedBlackTreeTest, TextSerialization) {
  RedBlackTree tree;
  tree.insert("lambda");
  tree.insert("kappa");
  tree.insert("mu");
  tree.insert("nu");
  tree.insert("xi");
  
  std::ostringstream oss;
  tree.serializeText(oss);
  
  std::istringstream iss(oss.str());
  RedBlackTree newTree;
  newTree.deserializeText(iss);
  
  EXPECT_TRUE(newTree.search("lambda"));
  EXPECT_TRUE(newTree.search("kappa"));
  EXPECT_TRUE(newTree.search("mu"));
  EXPECT_TRUE(newTree.search("nu"));
  EXPECT_TRUE(newTree.search("xi"));
  EXPECT_FALSE(newTree.search("omicron"));
}

TEST(RedBlackTreeTest, EmptyTreeSerialization) {
  RedBlackTree tree;
  
  nlohmann::json json = tree.serialize();
  RedBlackTree newTree1;
  newTree1.deserialize(json);
  EXPECT_TRUE(newTree1.isEmpty());
  
  std::ostringstream oss1;
  tree.serializeBinary(oss1);
  std::istringstream iss1(oss1.str());
  RedBlackTree newTree2;
  newTree2.deserializeBinary(iss1);
  EXPECT_TRUE(newTree2.isEmpty());
  
  std::ostringstream oss2;
  tree.serializeText(oss2);
  std::istringstream iss2(oss2.str());
  RedBlackTree newTree3;
  newTree3.deserializeText(iss2);
  EXPECT_TRUE(newTree3.isEmpty());
}

TEST(RedBlackTreeTest, EdgeCases) {
  RedBlackTree tree;
  
  // Тестируем граничные случаи для покрытия
  tree.insert("root");
  EXPECT_TRUE(tree.search("root"));
  
  // Вставка дубликатов
  tree.insert("root");
  tree.insert("root");
  
  // Поиск несуществующих элементов
  EXPECT_FALSE(tree.search(""));
  EXPECT_FALSE(tree.search("nonexistent"));
  
  tree.print();
}

TEST(RedBlackTreeTest, ExtensiveRotations) {
  RedBlackTree tree;
  
  // Создаем сценарии для всех типов ротаций
  std::vector<std::string> values = {
    "50", "30", "70", "20", "40", "60", "80",
    "10", "25", "35", "45", "55", "65", "75", "85",
    "5", "15", "22", "27", "32", "37", "42", "47",
    "52", "57", "62", "67", "72", "77", "82", "87"
  };
  
  for (const auto& val : values) {
    tree.insert(val);
  }
  
  for (const auto& val : values) {
    EXPECT_TRUE(tree.search(val));
  }
}
