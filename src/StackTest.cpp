#include <gtest/gtest.h>
#include "include/Stack.hpp"
#include <nlohmann/json.hpp>
#include <sstream>

TEST(StackTest, ConstructorAndInitialState) {
  Stack stack;
  EXPECT_TRUE(stack.empty());
  EXPECT_EQ(stack.size(), 0);
  EXPECT_THROW(stack.top(), std::runtime_error);
}

TEST(StackTest, Push) {
  Stack stack;
  stack.push("first");
  EXPECT_FALSE(stack.empty());
  EXPECT_EQ(stack.size(), 1);
  EXPECT_EQ(stack.top(), "first");
  stack.push("second");
  EXPECT_EQ(stack.size(), 2);
  EXPECT_EQ(stack.top(), "second");
  stack.pop();
  EXPECT_EQ(stack.top(), "first");
}

TEST(StackTest, Pop) {
  Stack stack;
  stack.push("first");
  stack.push("second");
  stack.pop();
  EXPECT_EQ(stack.size(), 1);
  EXPECT_EQ(stack.top(), "first");
  stack.pop();
  EXPECT_TRUE(stack.empty());
  stack.pop();
  EXPECT_TRUE(stack.empty());
}

TEST(StackTest, Contains) {
  Stack stack;
  EXPECT_FALSE(stack.contains("test"));
  stack.push("first");
  stack.push("second");
  EXPECT_TRUE(stack.contains("first"));
  EXPECT_TRUE(stack.contains("second"));
  EXPECT_FALSE(stack.contains("third"));
}

TEST(StackTest, SerializeDeserialize) {
  Stack stack;
  stack.push("bottom");
  stack.push("middle");
  stack.push("top");
  
  nlohmann::json j = stack.serialize();
  Stack newStack;
  newStack.deserialize(j);
  
  EXPECT_EQ(newStack.size(), 3);
  EXPECT_EQ(newStack.top(), "top");
}

TEST(StackTest, BinarySerialization) {
  Stack stack;
  stack.push("test1");
  stack.push("test2");
  stack.push("test3");
  
  std::ostringstream oss;
  stack.serializeBinary(oss);
  
  Stack newStack;
  std::istringstream iss(oss.str());
  newStack.deserializeBinary(iss);
  
  EXPECT_EQ(newStack.size(), 3);
  EXPECT_EQ(newStack.top(), "test3");
  newStack.pop();
  EXPECT_EQ(newStack.top(), "test2");
}

TEST(StackTest, TextSerialization) {
  Stack stack;
  stack.push("hello");
  stack.push("world");
  stack.push("test");
  
  std::ostringstream oss;
  stack.serializeText(oss);
  
  Stack newStack;
  std::istringstream iss(oss.str());
  newStack.deserializeText(iss);
  
  EXPECT_EQ(newStack.size(), 3);
  EXPECT_EQ(newStack.top(), "test");
}

TEST(StackTest, EmptyStackSerialization) {
  Stack stack;
  
  nlohmann::json j = stack.serialize();
  Stack newStack1;
  newStack1.deserialize(j);
  EXPECT_TRUE(newStack1.empty());
  
  std::ostringstream oss;
  stack.serializeBinary(oss);
  Stack newStack2;
  std::istringstream iss(oss.str());
  newStack2.deserializeBinary(iss);
  EXPECT_TRUE(newStack2.empty());
  
  std::ostringstream oss2;
  stack.serializeText(oss2);
  Stack newStack3;
  std::istringstream iss2(oss2.str());
  newStack3.deserializeText(iss2);
  EXPECT_TRUE(newStack3.empty());
}

TEST(StackTest, Print) {
  Stack stack;
  stack.push("a");
  stack.push("b");
  stack.print(); // Для покрытия метода print
}
