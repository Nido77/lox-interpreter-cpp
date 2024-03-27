CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -Wpedantic

SRCS := main.cpp $(wildcard src/*.cpp)
OBJS := $(SRCS:.cpp=.o)
EXEC := cpp-lox

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
	