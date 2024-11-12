CXX = g++
CXXFLAGS = -std=c++17 -g -Wall -O2

PROG ?= main
TEST_PROG ?= test
OBJS = File.o FileAVL.o FileTrie.o solution.o main.o

mainprog: $(PROG)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(PROG): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

clean:
	rm -rf $(PROG) $(TEST_PROG) *.o *.out

rebuild: clean all test
