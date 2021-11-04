CXX := gcc
CXXFLAGS := -Wall

matrix: library 
	$(CXX) $(CXXFLAGS) -shared build/matrix.o -o build/matrix.so 

library:
	mkdir -p build/
	$(CXX) $(CXXFLAGS) -fPIC -c src/matrix_operators.c -o build/matrix.o

test: matrix
	$(CXX) $(CXXFLAGS) -c src/main.c -o build/main.o
	$(CXX) $(CXXFLAGS) -L build/ build/main.o -o build/matrix_op -l:matrix.so

clean:
	rm -f build/*.o

install:
	cp src/matrix_operators.h /usr/include/matrix_operators.h
	cp build/matrix.so /usr/lib
