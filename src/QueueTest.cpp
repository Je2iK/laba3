#include <gtest/gtest.h>
#include "include/Queue.hpp"
#include <sstream>

TEST(QueueTest, ConstructorAndInitialState) {
  Queue queue;
  EXPECT_TRUE(queue.empty());
  EXPECT_EQ(queue.size(), 0);
  EXPECT_THROW(queue.front(), std::runtime_error);
}

TEST(QueueTest, Enqueue) {
  Queue queue;
  queue.enqueue("first");
  EXPECT_FALSE(queue.empty());
  EXPECT_EQ(queue.size(), 1);
  EXPECT_EQ(queue.front(), "first");
  
  queue.enqueue("second");
  EXPECT_EQ(queue.size(), 2);
  EXPECT_EQ(queue.front(), "first");
}

TEST(QueueTest, Dequeue) {
  Queue queue;
  queue.enqueue("first");
  queue.enqueue("second");
  
  queue.dequeue();
  EXPECT_EQ(queue.size(), 1);
  EXPECT_EQ(queue.front(), "second");
  
  queue.dequeue();
  EXPECT_TRUE(queue.empty());
  
  queue.dequeue(); // Safe on empty
  EXPECT_TRUE(queue.empty());
}

TEST(QueueTest, Serialization) {
  Queue queue;
  queue.enqueue("a");
  queue.enqueue("b");
  queue.enqueue("c");
  
  nlohmann::json j = queue.serialize();
  Queue newQueue;
  newQueue.deserialize(j);
  
  EXPECT_EQ(newQueue.size(), 3);
  EXPECT_EQ(newQueue.front(), "a");
}

TEST(QueueTest, BinarySerialization) {
  Queue queue;
  queue.enqueue("test1");
  queue.enqueue("test2");
  
  std::ostringstream oss;
  queue.serializeBinary(oss);
  
  Queue newQueue;
  std::istringstream iss(oss.str());
  newQueue.deserializeBinary(iss);
  
  EXPECT_EQ(newQueue.size(), 2);
  EXPECT_EQ(newQueue.front(), "test1");
}

TEST(QueueTest, TextSerialization) {
  Queue queue;
  queue.enqueue("hello");
  queue.enqueue("world");
  
  std::ostringstream oss;
  queue.serializeText(oss);
  
  Queue newQueue;
  std::istringstream iss(oss.str());
  newQueue.deserializeText(iss);
  
  EXPECT_EQ(newQueue.size(), 2);
  EXPECT_EQ(newQueue.front(), "hello");
}

TEST(QueueTest, EmptyQueueSerialization) {
  Queue queue;
  
  nlohmann::json j = queue.serialize();
  Queue newQueue1;
  newQueue1.deserialize(j);
  EXPECT_TRUE(newQueue1.empty());
  
  std::ostringstream oss;
  queue.serializeBinary(oss);
  Queue newQueue2;
  std::istringstream iss(oss.str());
  newQueue2.deserializeBinary(iss);
  EXPECT_TRUE(newQueue2.empty());
}

TEST(QueueTest, Print) {
  Queue queue;
  queue.enqueue("x");
  queue.enqueue("y");
  queue.print();
}

TEST(QueueTest, ComplexOperations) {
  Queue queue;
  
  for (int i = 0; i < 5; ++i) {
    queue.enqueue("item" + std::to_string(i));
  }
  
  EXPECT_EQ(queue.size(), 5);
  
  for (int i = 0; i < 3; ++i) {
    queue.dequeue();
  }
  
  EXPECT_EQ(queue.size(), 2);
  EXPECT_EQ(queue.front(), "item3");
}
