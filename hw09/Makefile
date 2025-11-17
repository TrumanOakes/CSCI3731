CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = test_io
OBJS = FileStreamBuf.o Main.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

FileStreamBuf.o: FileStreamBuf.cc FileStreamBuf.h
	$(CXX) $(CXXFLAGS) -c FileStreamBuf.cc

Main.o: Main.cc FileStreamBuf.h
	$(CXX) $(CXXFLAGS) -c Main.cc

clean:
	rm -f $(TARGET) $(OBJS)
