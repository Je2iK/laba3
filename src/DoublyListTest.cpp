#include <gtest/gtest.h>
#include "include/DoublyList.hpp"
#include <sstream>

TEST(DoublyListTest, ConstructorAndInitialState) {
  DoublyList list;
  EXPECT_TRUE(list.isEmpty());
  EXPECT_EQ(list.size(), 0);
}

TEST(DoublyListTest, PushFrontBack) {
  DoublyList list;
  list.pushFront("middle");
  list.pushFront("first");
  list.pushBack("last");
  
  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(list.get(0), "first");
  EXPECT_EQ(list.get(1), "middle");
  EXPECT_EQ(list.get(2), "last");
}

TEST(DoublyListTest, PopFrontBack) {
  DoublyList list;
  list.pushBack("a");
  list.pushBack("b");
  list.pushBack("c");
  
  list.popFront();
  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list.get(0), "b");
  
  list.popBack();
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.get(0), "b");
  
  list.popBack();
  EXPECT_TRUE(list.isEmpty());
  
  list.popFront(); // Safe on empty
  list.popBack(); // Safe on empty
  EXPECT_TRUE(list.isEmpty());
}

TEST(DoublyListTest, Insert) {
  DoublyList list;
  list.pushBack("a");
  list.pushBack("c");
  list.insert(1, "b");
  
  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(list.get(0), "a");
  EXPECT_EQ(list.get(1), "b");
  EXPECT_EQ(list.get(2), "c");
  
  list.insert(0, "start");
  EXPECT_EQ(list.get(0), "start");
  
  list.insert(list.size(), "end");
  EXPECT_EQ(list.get(list.size()-1), "end");
  
  EXPECT_THROW(list.insert(100, "fail"), std::out_of_range);
}

TEST(DoublyListTest, Remove) {
  DoublyList list;
  list.pushBack("x");
  list.pushBack("y");
  list.pushBack("z");
  
  list.remove(1);
  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list.get(0), "x");
  EXPECT_EQ(list.get(1), "z");
  
  list.remove(0); // Remove first
  EXPECT_EQ(list.get(0), "z");
  
  list.pushBack("w");
  list.remove(list.size()-1); // Remove last
  EXPECT_EQ(list.get(0), "z");
  
  EXPECT_THROW(list.remove(100), std::out_of_range);
}

TEST(DoublyListTest, Get) {
  DoublyList list;
  list.pushBack("test");
  EXPECT_EQ(list.get(0), "test");
  
  EXPECT_THROW(list.get(100), std::out_of_range);
}

TEST(DoublyListTest, Serialization) {
  DoublyList list;
  list.pushBack("1");
  list.pushBack("2");
  list.pushBack("3");
  
  nlohmann::json j = list.serialize();
  DoublyList newList;
  newList.deserialize(j);
  
  EXPECT_EQ(newList.size(), 3);
  EXPECT_EQ(newList.get(0), "1");
  EXPECT_EQ(newList.get(1), "2");
  EXPECT_EQ(newList.get(2), "3");
}

TEST(DoublyListTest, BinarySerialization) {
  DoublyList list;
  list.pushBack("test1");
  list.pushBack("test2");
  
  std::ostringstream oss;
  list.serializeBinary(oss);
  
  DoublyList newList;
  std::istringstream iss(oss.str());
  newList.deserializeBinary(iss);
  
  EXPECT_EQ(newList.size(), 2);
  EXPECT_EQ(newList.get(0), "test1");
  EXPECT_EQ(newList.get(1), "test2");
}

TEST(DoublyListTest, TextSerialization) {
  DoublyList list;
  list.pushBack("hello");
  list.pushBack("world");
  
  std::ostringstream oss;
  list.serializeText(oss);
  
  DoublyList newList;
  std::istringstream iss(oss.str());
  newList.deserializeText(iss);
  
  EXPECT_EQ(newList.size(), 2);
  EXPECT_EQ(newList.get(0), "hello");
  EXPECT_EQ(newList.get(1), "world");
}

TEST(DoublyListTest, EmptyListSerialization) {
  DoublyList list;
  
  nlohmann::json j = list.serialize();
  DoublyList newList1;
  newList1.deserialize(j);
  EXPECT_TRUE(newList1.isEmpty());
  
  std::ostringstream oss;
  list.serializeBinary(oss);
  DoublyList newList2;
  std::istringstream iss(oss.str());
  newList2.deserializeBinary(iss);
  EXPECT_TRUE(newList2.isEmpty());
}

TEST(DoublyListTest, Print) {
  DoublyList list;
  list.pushBack("hello");
  list.pushBack("world");
  list.print();
}
