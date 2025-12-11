CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I. -Inlohmann --coverage
LDFLAGS = -lgtest -lgtest_main -pthread --coverage

SRCDIR = include
TESTDIR = src
SOURCES = $(SRCDIR)/Stack.cpp $(SRCDIR)/Queue.cpp $(SRCDIR)/Array.cpp $(SRCDIR)/ForwardList.cpp $(SRCDIR)/DoublyList.cpp $(SRCDIR)/RedBlackTree.cpp $(SRCDIR)/ChainHashTable.cpp
TEST_SOURCES = $(TESTDIR)/StackTest.cpp $(TESTDIR)/QueueTest.cpp $(TESTDIR)/ArrayTest.cpp $(TESTDIR)/ForwardListTest.cpp $(TESTDIR)/DoublyListTest.cpp $(TESTDIR)/RedBlackTreeTest.cpp $(TESTDIR)/ChainHashTableTest.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)

TARGET = bin/all_tests

all: $(TARGET)

$(TARGET): $(OBJECTS) $(TEST_OBJECTS) | bin
	$(CXX) $(OBJECTS) $(TEST_OBJECTS) -o $(TARGET) $(LDFLAGS)

bin:
	mkdir -p bin

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TEST_OBJECTS) $(TARGET) *.gcda *.gcno coverage/coverage.info coverage/coverage_filtered.info
	rm -rf coverage/html_coverage

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
