all: eckeygen

eckeygen: eckeygen.c
	clang $^ -g -lwolfssl -o $@

clean:
	rm -rf eckeygen
