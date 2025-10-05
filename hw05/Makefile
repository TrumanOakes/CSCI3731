CXX      = g++
CXXFLAGS = -Wall -std=c++11

SRCS   = main.cc MandelBrotSet.cc
OBJS   = $(SRCS:.cc=.o)
TARGET = mandelbrot_img.exe

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cc Mandelbrot.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
