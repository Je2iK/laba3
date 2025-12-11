#include <gtest/gtest.h>
#include "include/Array.hpp"
#include <sstream>

TEST(ArrayTest, ConstructorAndInitialState) {
  Array arr;
  EXPECT_TRUE(arr.empty());
  EXPECT_EQ(arr.size(), 0);
}

TEST(ArrayTest, Insert) {
  Array arr;
  arr.insert(0, "first");
  EXPECT_FALSE(arr.empty());
  EXPECT_EQ(arr.size(), 1);
  EXPECT_EQ(arr.get(0), "first");
  
  arr.insert(1, "second");
  arr.insert(1, "middle");
  EXPECT_EQ(arr.size(), 3);
  EXPECT_EQ(arr.get(1), "middle");
  EXPECT_EQ(arr.get(2), "second");
}

TEST(ArrayTest, InsertErrors) {
  Array arr;
  EXPECT_THROW(arr.insert(1, "test"), std::out_of_range);
  
  Array fullArr(2);
  fullArr.insert(0, "a");
  fullArr.insert(1, "b");
  EXPECT_THROW(fullArr.insert(2, "c"), std::runtime_error);
}

TEST(ArrayTest, Remove) {
  Array arr;
  arr.insert(0, "a");
  arr.insert(1, "b");
  arr.insert(2, "c");
  
  arr.remove(1);
  EXPECT_EQ(arr.size(), 2);
  EXPECT_EQ(arr.get(1), "c");
  
  EXPECT_THROW(arr.remove(5), std::out_of_range);
}

TEST(ArrayTest, SetGet) {
  Array arr;
  arr.insert(0, "test");
  arr.set(0, "modified");
  EXPECT_EQ(arr.get(0), "modified");
  
  EXPECT_THROW(arr.get(5), std::out_of_range);
  EXPECT_THROW(arr.set(5, "fail"), std::out_of_range);
}

TEST(ArrayTest, Serialization) {
  Array arr;
  arr.insert(0, "x");
  arr.insert(1, "y");
  
  nlohmann::json j = arr.serialize();
  Array newArr;
  newArr.deserialize(j);
  
  EXPECT_EQ(newArr.size(), 2);
  EXPECT_EQ(newArr.get(0), "x");
  EXPECT_EQ(newArr.get(1), "y");
}

TEST(ArrayTest, BinarySerialization) {
  Array arr;
  arr.insert(0, "test1");
  arr.insert(1, "test2");
  
  std::ostringstream oss;
  arr.serializeBinary(oss);
  
  Array newArr;
  std::istringstream iss(oss.str());
  newArr.deserializeBinary(iss);
  
  EXPECT_EQ(newArr.size(), 2);
  EXPECT_EQ(newArr.get(0), "test1");
  EXPECT_EQ(newArr.get(1), "test2");
}

TEST(ArrayTest, TextSerialization) {
  Array arr;
  arr.insert(0, "hello");
  arr.insert(1, "world");
  
  std::ostringstream oss;
  arr.serializeText(oss);
  
  Array newArr;
  std::istringstream iss(oss.str());
  newArr.deserializeText(iss);
  
  EXPECT_EQ(newArr.size(), 2);
  EXPECT_EQ(newArr.get(0), "hello");
  EXPECT_EQ(newArr.get(1), "world");
}

TEST(ArrayTest, EmptyArraySerialization) {
  Array arr;
  
  nlohmann::json j = arr.serialize();
  Array newArr1;
  newArr1.deserialize(j);
  EXPECT_TRUE(newArr1.empty());
  
  std::ostringstream oss;
  arr.serializeBinary(oss);
  Array newArr2;
  std::istringstream iss(oss.str());
  newArr2.deserializeBinary(iss);
  EXPECT_TRUE(newArr2.empty());
}

TEST(ArrayTest, Print) {
  Array arr;
  arr.insert(0, "hello");
  arr.print();
}
