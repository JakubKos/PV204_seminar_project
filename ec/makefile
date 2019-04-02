all: eckeygen sidechannel

measure-sidechannel: sidechannel
	./sidechannel 0 0
	./sidechannel 1 0
	./sidechannel 2 0
	./sidechannel 3 0
	./sidechannel 4 0
	./sidechannel 5 0
	./sidechannel 6 0
	./sidechannel 0 1
	./sidechannel 1 1
	./sidechannel 2 1
	./sidechannel 3 1
	./sidechannel 4 1
	./sidechannel 5 1
	./sidechannel 6 1
	./sidechannel 0 2
	./sidechannel 1 2
	./sidechannel 2 2
	./sidechannel 3 2
	./sidechannel 4 2
	./sidechannel 5 2
	./sidechannel 6 2
	./sidechannel 0 3
	./sidechannel 1 3
	./sidechannel 2 3
	./sidechannel 3 3
	./sidechannel 4 3
	./sidechannel 5 3
	./sidechannel 6 3
	./sidechannel 0 4
	./sidechannel 1 4
	./sidechannel 2 4
	./sidechannel 3 4
	./sidechannel 4 4
	./sidechannel 5 4
	./sidechannel 6 4
	./sidechannel 0 5
	./sidechannel 1 5
	./sidechannel 2 5
	./sidechannel 3 5
	./sidechannel 4 5
	./sidechannel 5 5
	./sidechannel 6 5

eckeygen: eckeygen.c
	clang $^ -lwolfssl -o $@

sidechannel: sidechannel.c
	clang $^ -lwolfssl -o $@

clean:
	rm -rf eckeygen sidechannel
