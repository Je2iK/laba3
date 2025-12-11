#include <gtest/gtest.h>
#include "include/ForwardList.hpp"

TEST(ForwardListTest, ConstructorAndInitialState) {
  ForwardList list;
  EXPECT_TRUE(list.isEmpty());
}

TEST(ForwardListTest, PushFront) {
  ForwardList list;
  list.pushFront("first");
  EXPECT_FALSE(list.isEmpty());
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.get(0), "first");
}

TEST(ForwardListTest, PopFront) {
  ForwardList list;
  list.pushFront("test");
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.get(0), "test");
  
  list.popFront();
  EXPECT_TRUE(list.isEmpty());
  
  list.popFront(); // Safe on empty
  EXPECT_TRUE(list.isEmpty());
}

TEST(ForwardListTest, Insert) {
  ForwardList list;
  list.insert(0, "first");
  list.insert(1, "second");
  list.insert(0, "new_first");
  
  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(list.get(0), "new_first");
  EXPECT_EQ(list.get(1), "first");
  EXPECT_EQ(list.get(2), "second");
}

TEST(ForwardListTest, Remove) {
  ForwardList list;
  list.pushFront("third");
  list.pushFront("second");
  list.pushFront("first");
  
  list.remove(1);
  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list.get(0), "first");
  EXPECT_EQ(list.get(1), "third");
}

TEST(ForwardListTest, Serialization) {
  ForwardList list;
  list.pushFront("third");
  list.pushFront("second");
  list.pushFront("first");
  
  std::string json = list.toJSON();
  ForwardList newList;
  newList.fromJSON(json);
  
  EXPECT_EQ(newList.size(), 3);
  EXPECT_EQ(newList.get(0), "first");
  EXPECT_EQ(newList.get(1), "second");
  EXPECT_EQ(newList.get(2), "third");
}

TEST(ForwardListTest, BinarySerialization) {
  ForwardList list;
  list.pushFront("beta");
  list.pushFront("alpha");
  
  list.saveBinary("test_forward.bin");
  ForwardList newList;
  newList.loadBinary("test_forward.bin");
  
  EXPECT_EQ(newList.size(), 2);
  EXPECT_EQ(newList.get(0), "alpha");
  EXPECT_EQ(newList.get(1), "beta");
}

TEST(ForwardListTest, TextSerialization) {
  ForwardList list;
  list.pushFront("gamma");
  list.pushFront("beta");
  list.pushFront("alpha");
  
  list.saveText("test_forward.txt");
  ForwardList newList;
  newList.loadText("test_forward.txt");
  
  EXPECT_EQ(newList.size(), 3);
  EXPECT_EQ(newList.get(0), "alpha");
  EXPECT_EQ(newList.get(1), "beta");
  EXPECT_EQ(newList.get(2), "gamma");
}

TEST(ForwardListTest, EmptyListSerialization) {
  ForwardList list;
  
  std::string json = list.toJSON();
  ForwardList newList1;
  newList1.fromJSON(json);
  EXPECT_TRUE(newList1.isEmpty());
  
  list.saveBinary("empty_forward.bin");
  ForwardList newList2;
  newList2.loadBinary("empty_forward.bin");
  EXPECT_TRUE(newList2.isEmpty());
}
