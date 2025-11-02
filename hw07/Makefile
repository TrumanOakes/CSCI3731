CXX      ?= g++
CXXFLAGS ?= -std=c++17 -O2 -Wall -Wextra -pedantic

ifeq ($(OS),Windows_NT)
EXE := test_image.exe
else
EXE := test_image
endif

all: $(EXE)

$(EXE): TestImageClass.cc ImageClass.cc
	$(CXX) $(CXXFLAGS) TestImageClass.cc -o $(EXE)

run: $(EXE)
	./$(EXE) $(ARGS)

clean:
	$(RM) $(EXE)

.PHONY: all run clean