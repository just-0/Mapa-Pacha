CXX = g++
CXXFLAGS = -std=c++11 -Wall -g
TARGET = main.exe
OBJS = main.o QuadTree.o BTree.o

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp QuadTree.h BTree.h
	$(CXX) $(CXXFLAGS) -c main.cpp

QuadTree.o: QuadTree.cpp QuadTree.h
	$(CXX) $(CXXFLAGS) -c QuadTree.cpp

BTree.o: BTree.cpp BTree.h QuadTree.h
	$(CXX) $(CXXFLAGS) -c BTree.cpp

clean:
	rm -f $(TARGET) $(OBJS)
