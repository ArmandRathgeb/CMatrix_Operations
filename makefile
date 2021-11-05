CXX := gcc
CXXFLAGS := -Wall
DIR := $(shell pwd)
export LD_LIBRARY_PATH=$(DIR)/build:$$LD_LIBRARY_PATH

matrix: library 
	$(CXX) $(CXXFLAGS) -shared build/matrix.o -o build/matrix.so 

library:
	mkdir -p build/
	$(CXX) $(CXXFLAGS) -fPIC -c src/matrix_operators.c -o build/matrix.o

test: matrix
	@echo $(LD_LIBRARY_PATH)
	$(CXX) $(CXXFLAGS) -c src/main.c -o build/main.o
	$(CXX) $(CXXFLAGS) -L$(DIR)/build build/main.o -o build/matrix_op -l:matrix.so
	./build/matrix_op
	unset LD_LIBRARY_PATH

.PHONY: clean
clean:
	rm -f build/*.o

install:
	cp src/matrix_operators.h /usr/include/matrix_operators.h
	cp build/matrix.so /usr/lib
