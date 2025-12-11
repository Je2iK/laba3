#include <gtest/gtest.h>
#include "include/ForwardList.hpp"
#include <sstream>

TEST(ForwardListTest, ConstructorAndInitialState) {
  ForwardList list;
  EXPECT_TRUE(list.empty());
  EXPECT_EQ(list.size(), 0);
}

TEST(ForwardListTest, PushFront) {
  ForwardList list;
  list.pushFront("first");
  EXPECT_FALSE(list.empty());
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.get(0), "first");
  
  list.pushFront("second");
  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list.get(0), "second");
  EXPECT_EQ(list.get(1), "first");
}

TEST(ForwardListTest, PopFront) {
  ForwardList list;
  list.pushFront("a");
  list.pushFront("b");
  
  list.popFront();
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.get(0), "a");
  
  list.popFront();
  EXPECT_TRUE(list.empty());
  
  list.popFront(); // Safe on empty
  EXPECT_TRUE(list.empty());
}

TEST(ForwardListTest, Insert) {
  ForwardList list;
  list.pushFront("a");
  list.pushFront("c");
  list.insert(1, "b");
  
  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(list.get(0), "c");
  EXPECT_EQ(list.get(1), "b");
  EXPECT_EQ(list.get(2), "a");
  
  EXPECT_THROW(list.insert(10, "fail"), std::out_of_range);
}

TEST(ForwardListTest, Remove) {
  ForwardList list;
  list.pushFront("a");
  list.pushFront("b");
  list.pushFront("c");
  
  list.remove(1);
  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list.get(0), "c");
  EXPECT_EQ(list.get(1), "a");
  
  EXPECT_THROW(list.remove(10), std::out_of_range);
}

TEST(ForwardListTest, Get) {
  ForwardList list;
  list.pushFront("test");
  EXPECT_EQ(list.get(0), "test");
  
  EXPECT_THROW(list.get(10), std::out_of_range);
}

TEST(ForwardListTest, Serialization) {
  ForwardList list;
  list.pushFront("z");
  list.pushFront("y");
  list.pushFront("x");
  
  nlohmann::json j = list.serialize();
  ForwardList newList;
  newList.deserialize(j);
  
  EXPECT_EQ(newList.size(), 3);
  EXPECT_EQ(newList.get(0), "x");
  EXPECT_EQ(newList.get(1), "y");
  EXPECT_EQ(newList.get(2), "z");
}

TEST(ForwardListTest, BinarySerialization) {
  ForwardList list;
  list.pushFront("test2");
  list.pushFront("test1");
  
  std::ostringstream oss;
  list.serializeBinary(oss);
  
  ForwardList newList;
  std::istringstream iss(oss.str());
  newList.deserializeBinary(iss);
  
  EXPECT_EQ(newList.size(), 2);
  EXPECT_EQ(newList.get(0), "test1");
  EXPECT_EQ(newList.get(1), "test2");
}

TEST(ForwardListTest, TextSerialization) {
  ForwardList list;
  list.pushFront("world");
  list.pushFront("hello");
  
  std::ostringstream oss;
  list.serializeText(oss);
  
  ForwardList newList;
  std::istringstream iss(oss.str());
  newList.deserializeText(iss);
  
  EXPECT_EQ(newList.size(), 2);
  EXPECT_EQ(newList.get(0), "hello");
  EXPECT_EQ(newList.get(1), "world");
}

TEST(ForwardListTest, EmptyListSerialization) {
  ForwardList list;
  
  nlohmann::json j = list.serialize();
  ForwardList newList1;
  newList1.deserialize(j);
  EXPECT_TRUE(newList1.empty());
  
  std::ostringstream oss;
  list.serializeBinary(oss);
  ForwardList newList2;
  std::istringstream iss(oss.str());
  newList2.deserializeBinary(iss);
  EXPECT_TRUE(newList2.empty());
}

TEST(ForwardListTest, Print) {
  ForwardList list;
  list.pushFront("test");
  list.print();
}
