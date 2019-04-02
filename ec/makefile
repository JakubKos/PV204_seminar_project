all: eckeygen encdec-sidechannel

measure-sidechannel: encdec-sidechannel
	./encdec-sidechannel 0 0
	./encdec-sidechannel 1 0
	./encdec-sidechannel 2 0
	./encdec-sidechannel 3 0
	./encdec-sidechannel 4 0
	./encdec-sidechannel 5 0
	./encdec-sidechannel 6 0
	./encdec-sidechannel 0 1
	./encdec-sidechannel 1 1
	./encdec-sidechannel 2 1
	./encdec-sidechannel 3 1
	./encdec-sidechannel 4 1
	./encdec-sidechannel 5 1
	./encdec-sidechannel 6 1
	./encdec-sidechannel 0 2
	./encdec-sidechannel 1 2
	./encdec-sidechannel 2 2
	./encdec-sidechannel 3 2
	./encdec-sidechannel 4 2
	./encdec-sidechannel 5 2
	./encdec-sidechannel 6 2
	./encdec-sidechannel 0 3
	./encdec-sidechannel 1 3
	./encdec-sidechannel 2 3
	./encdec-sidechannel 3 3
	./encdec-sidechannel 4 3
	./encdec-sidechannel 5 3
	./encdec-sidechannel 6 3
	./encdec-sidechannel 0 4
	./encdec-sidechannel 1 4
	./encdec-sidechannel 2 4
	./encdec-sidechannel 3 4
	./encdec-sidechannel 4 4
	./encdec-sidechannel 5 4
	./encdec-sidechannel 6 4
	./encdec-sidechannel 0 5
	./encdec-sidechannel 1 5
	./encdec-sidechannel 2 5
	./encdec-sidechannel 3 5
	./encdec-sidechannel 4 5
	./encdec-sidechannel 5 5
	./encdec-sidechannel 6 5

eckeygen: eckeygen.c
	clang $^ -lwolfssl -o $@

encdec-sidechannel: encdec-sidechannel.c
	clang $^ -lwolfssl -o $@

clean:
	rm -rf eckeygen encdec-sidechannel
