all: bench

bench: main.cpp
	$(CXX) -std=c++17 -O0 -o $@ $^ -lwolfssl

clean:
	rm -rf bench
