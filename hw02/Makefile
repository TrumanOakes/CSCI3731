CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = mandelbrot.exe
SRCS = main.cc MandelBrotSet.cc
OBJS = $(SRCS:.cc=.o)
all: $(TARGET)
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
%.o: %.cc Mandelbrot.h
	$(CXX) $(CXXFLAGS) -c $< -o $@
clean:
	rm -f $(OBJS) $(TARGET)