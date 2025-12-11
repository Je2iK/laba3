#include <gtest/gtest.h>
#include "include/ChainHashTable.hpp"
#include <sstream>

TEST(ChainHashTableTest, ConstructorAndInitialState) {
  ChainHashTable table;
  EXPECT_TRUE(table.isEmpty());
  EXPECT_EQ(table.getSize(), 0);
}

TEST(ChainHashTableTest, InsertAndFind) {
  ChainHashTable table;
  table.insertItem("key1", "value1");
  table.insertItem("key2", "value2");
  
  EXPECT_EQ(table.getSize(), 2);
  EXPECT_FALSE(table.isEmpty());
  
  std::string* val1 = table.findItem("key1");
  std::string* val2 = table.findItem("key2");
  
  ASSERT_NE(val1, nullptr);
  ASSERT_NE(val2, nullptr);
  EXPECT_EQ(*val1, "value1");
  EXPECT_EQ(*val2, "value2");
  
  EXPECT_EQ(table.findItem("nonexistent"), nullptr);
}

TEST(ChainHashTableTest, UpdateValue) {
  ChainHashTable table;
  table.insertItem("key1", "value1");
  table.insertItem("key1", "new_value");
  
  EXPECT_EQ(table.getSize(), 1);
  std::string* val = table.findItem("key1");
  ASSERT_NE(val, nullptr);
  EXPECT_EQ(*val, "new_value");
}

TEST(ChainHashTableTest, Remove) {
  ChainHashTable table;
  table.insertItem("key1", "value1");
  table.insertItem("key2", "value2");
  table.insertItem("key3", "value3");
  
  EXPECT_TRUE(table.removeItem("key1"));
  EXPECT_EQ(table.getSize(), 2);
  EXPECT_EQ(table.findItem("key1"), nullptr);
  
  EXPECT_FALSE(table.removeItem("nonexistent"));
  EXPECT_EQ(table.getSize(), 2);
}

TEST(ChainHashTableTest, HasKey) {
  ChainHashTable table;
  table.insertItem("test", "value");
  
  EXPECT_TRUE(table.hasKey("test"));
  EXPECT_FALSE(table.hasKey("missing"));
}

TEST(ChainHashTableTest, JsonSerialization) {
  ChainHashTable table;
  table.insertItem("key1", "value1");
  table.insertItem("key2", "value2");
  table.insertItem("key3", "value3");
  
  nlohmann::json j = table.toJson();
  
  ChainHashTable newTable;
  newTable.fromJson(j);
  
  EXPECT_EQ(newTable.getSize(), 3);
  EXPECT_TRUE(newTable.hasKey("key1"));
  EXPECT_TRUE(newTable.hasKey("key2"));
  EXPECT_TRUE(newTable.hasKey("key3"));
}

TEST(ChainHashTableTest, BinarySerialization) {
  ChainHashTable table;
  table.insertItem("test1", "val1");
  table.insertItem("test2", "val2");
  table.insertItem("test3", "val3");
  
  std::ostringstream oss;
  table.saveBinary(oss);
  
  ChainHashTable newTable;
  std::istringstream iss(oss.str());
  newTable.loadBinary(iss);
  
  EXPECT_EQ(newTable.getSize(), 3);
  EXPECT_TRUE(newTable.hasKey("test1"));
  EXPECT_TRUE(newTable.hasKey("test2"));
  EXPECT_TRUE(newTable.hasKey("test3"));
}

TEST(ChainHashTableTest, TextSerialization) {
  ChainHashTable table;
  table.insertItem("hello", "world");
  table.insertItem("foo", "bar");
  table.insertItem("test", "data");
  
  std::ostringstream oss;
  table.saveText(oss);
  
  ChainHashTable newTable;
  std::istringstream iss(oss.str());
  newTable.loadText(iss);
  
  EXPECT_EQ(newTable.getSize(), 3);
  EXPECT_TRUE(newTable.hasKey("hello"));
  EXPECT_TRUE(newTable.hasKey("foo"));
  EXPECT_TRUE(newTable.hasKey("test"));
}

TEST(ChainHashTableTest, EmptyTableSerialization) {
  ChainHashTable table;
  
  nlohmann::json j = table.toJson();
  ChainHashTable newTable1;
  newTable1.fromJson(j);
  EXPECT_TRUE(newTable1.isEmpty());
  
  std::ostringstream oss;
  table.saveBinary(oss);
  ChainHashTable newTable2;
  std::istringstream iss(oss.str());
  newTable2.loadBinary(iss);
  EXPECT_TRUE(newTable2.isEmpty());
  
  std::ostringstream oss2;
  table.saveText(oss2);
  ChainHashTable newTable3;
  std::istringstream iss2(oss2.str());
  newTable3.loadText(iss2);
  EXPECT_TRUE(newTable3.isEmpty());
}

TEST(ChainHashTableTest, Display) {
  ChainHashTable table;
  table.insertItem("a", "1");
  table.insertItem("b", "2");
  table.display(); // Для покрытия метода display
}

TEST(ChainHashTableTest, CollisionHandling) {
  ChainHashTable table(4); // Маленький размер для коллизий
  
  for (int i = 0; i < 20; ++i) {
    table.insertItem("key" + std::to_string(i), "value" + std::to_string(i));
  }
  
  EXPECT_EQ(table.getSize(), 20);
  
  for (int i = 0; i < 20; ++i) {
    EXPECT_TRUE(table.hasKey("key" + std::to_string(i)));
    std::string* val = table.findItem("key" + std::to_string(i));
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(*val, "value" + std::to_string(i));
  }
}
