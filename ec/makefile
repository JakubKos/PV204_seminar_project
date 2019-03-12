all: eckeygen

eckeygen: eckeygen.c
	clang $^ -lwolfssl -o $@

clean:
	rm -rf eckeygen
