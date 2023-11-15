CXX = g++
CXXFLAGS = -std=c++11 -Wall -g
TARGET = main
OBJS = main.o QuadTree.o

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp QuadTree.h
	$(CXX) $(CXXFLAGS) -c main.cpp

QuadTree.o: QuadTree.cpp QuadTree.h
	$(CXX) $(CXXFLAGS) -c QuadTree.cpp

clean:
	rm -f $(TARGET) $(OBJS)

