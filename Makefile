build:
	gcc -fPIC -shared -I ./include ./src/set.c -o ./set.so

test: build
	gcc -I ./include ./set.so ./tests/tests.c -o ./tests.bin
	./tests.bin
	rm ./tests.bin

union: build
	gcc -I ./include ./set.so ./examples/union.c -o ./union.bin
	./union.bin
	rm ./union.bin

intersection: build
	gcc -I ./include ./set.so ./examples/intersection.c -o ./intersection.bin
	./intersection.bin
	rm ./intersection.bin

difference: build
	gcc -I ./include ./set.so ./examples/difference.c -o ./difference.bin
	./difference.bin
	rm ./difference.bin
