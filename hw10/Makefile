CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wall

TARGET = textgen
OBJS = main.o TextModel.o Pattern.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cc TextModel.h Pattern.h
	$(CXX) $(CXXFLAGS) -c main.cc

TextModel.o: TextModel.cc TextModel.h Pattern.h
	$(CXX) $(CXXFLAGS) -c TextModel.cc

Pattern.o: Pattern.cc Pattern.h
	$(CXX) $(CXXFLAGS) -c Pattern.cc

clean:
	rm -f $(OBJS) $(TARGET)
