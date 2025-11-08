CXX = g++
CXXFLAGS = -std=c++11 -Wall

TARGET = ExerciseBook
OBJS = ExerciseBook.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

ExerciseBook.o: ExerciseBook.cc
	$(CXX) $(CXXFLAGS) -c ExerciseBook.cc

clean:
	rm -f $(OBJS) $(TARGET)