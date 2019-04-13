all: bench

bench: main.c
	$(CC) -std=c99 -o $@ $^ -lwolfssl

clean:
	rm -rf bench
