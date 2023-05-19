CXX=g++
CXXFLAGS=-std=c++23 -Wall -fopenmp
SRCDIR=.
SRCS=$(shell find $(SRCDIR) -name '*.cpp')
OBJS=$(SRCS:.cpp=.o)
EXEC=main

make run: $(EXEC)
	python3 ./run.py

all: $(EXEC)

$(EXEC): $(filter-out main.o, $(OBJS)) main.o
	$(CXX) $(CXXFLAGS) $^ -o $(EXEC)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)