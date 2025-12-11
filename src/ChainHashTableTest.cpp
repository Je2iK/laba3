#include <gtest/gtest.h>
#include "include/ChainHashTable.hpp"
#include <sstream>

TEST(ChainHashTableTest, ConstructorAndInitialState) {
  ChainHashTable table;
  EXPECT_EQ(table.size(), 0);
  EXPECT_TRUE(table.isEmpty());
}

TEST(ChainHashTableTest, InsertAndFind) {
  ChainHashTable table;
  table.insert("key1", "value1");
  table.insert("key2", "value2");
  
  EXPECT_EQ(table.size(), 2);
  EXPECT_FALSE(table.isEmpty());
  
  EXPECT_EQ(table.find("key1"), "value1");
  EXPECT_EQ(table.find("key2"), "value2");
  EXPECT_EQ(table.find("nonexistent"), "");
}

TEST(ChainHashTableTest, UpdateValue) {
  ChainHashTable table;
  table.insert("key1", "value1");
  table.insert("key1", "new_value");
  
  EXPECT_EQ(table.size(), 1);
  EXPECT_EQ(table.find("key1"), "new_value");
}

TEST(ChainHashTableTest, Remove) {
  ChainHashTable table;
  table.insert("key1", "value1");
  table.insert("key2", "value2");
  table.insert("key3", "value3");
  
  table.remove("key1");
  EXPECT_EQ(table.size(), 2);
  EXPECT_EQ(table.find("key1"), "");
  
  table.remove("nonexistent");
  EXPECT_EQ(table.size(), 2);
}

TEST(ChainHashTableTest, HasKey) {
  ChainHashTable table;
  table.insert("test", "value");
  
  EXPECT_TRUE(table.hasKey("test"));
  EXPECT_FALSE(table.hasKey("nonexistent"));
}

TEST(ChainHashTableTest, JsonSerialization) {
  ChainHashTable table;
  table.insert("key1", "value1");
  table.insert("key2", "value2");
  table.insert("key3", "value3");
  
  nlohmann::json j = table.serialize();
  ChainHashTable newTable;
  newTable.deserialize(j);
  
  EXPECT_EQ(newTable.size(), 3);
  EXPECT_EQ(newTable.find("key1"), "value1");
  EXPECT_EQ(newTable.find("key2"), "value2");
  EXPECT_EQ(newTable.find("key3"), "value3");
}

TEST(ChainHashTableTest, BinarySerialization) {
  ChainHashTable table;
  table.insert("test1", "val1");
  table.insert("test2", "val2");
  table.insert("test3", "val3");
  
  std::ostringstream oss;
  table.serializeBinary(oss);
  
  std::istringstream iss(oss.str());
  ChainHashTable newTable;
  newTable.deserializeBinary(iss);
  
  EXPECT_EQ(newTable.size(), 3);
  EXPECT_EQ(newTable.find("test1"), "val1");
  EXPECT_EQ(newTable.find("test2"), "val2");
  EXPECT_EQ(newTable.find("test3"), "val3");
}

TEST(ChainHashTableTest, TextSerialization) {
  ChainHashTable table;
  table.insert("hello", "world");
  table.insert("foo", "bar");
  table.insert("test", "data");
  
  std::ostringstream oss;
  table.serializeText(oss);
  
  std::istringstream iss(oss.str());
  ChainHashTable newTable;
  newTable.deserializeText(iss);
  
  EXPECT_EQ(newTable.size(), 3);
  EXPECT_EQ(newTable.find("hello"), "world");
  EXPECT_EQ(newTable.find("foo"), "bar");
  EXPECT_EQ(newTable.find("test"), "data");
}

TEST(ChainHashTableTest, EmptyTableSerialization) {
  ChainHashTable table;
  
  nlohmann::json j = table.serialize();
  ChainHashTable newTable1;
  newTable1.deserialize(j);
  EXPECT_TRUE(newTable1.isEmpty());
  
  std::ostringstream oss;
  table.serializeBinary(oss);
  std::istringstream iss(oss.str());
  ChainHashTable newTable2;
  newTable2.deserializeBinary(iss);
  EXPECT_TRUE(newTable2.isEmpty());
  
  std::ostringstream oss2;
  table.serializeText(oss2);
  std::istringstream iss2(oss2.str());
  ChainHashTable newTable3;
  newTable3.deserializeText(iss2);
  EXPECT_TRUE(newTable3.isEmpty());
}

TEST(ChainHashTableTest, CollisionHandling) {
  ChainHashTable table(4); // Small size to force collisions
  
  for (int i = 0; i < 20; i++) {
    table.insert("key" + std::to_string(i), "value" + std::to_string(i));
  }
  
  EXPECT_EQ(table.size(), 20);
  
  for (int i = 0; i < 20; i++) {
    EXPECT_EQ(table.find("key" + std::to_string(i)), "value" + std::to_string(i));
  }
}
