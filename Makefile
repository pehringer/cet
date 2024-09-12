build:
	gcc -fPIC -shared -I ./include ./src/cet.c -o ./cet.so

test: build
	gcc -I ./include ./cet.so ./tests/tests.c -o ./tests.bin
	./tests.bin
	rm ./tests.bin

union: build
	gcc -I ./include ./cet.so ./examples/union.c -o ./union.bin
	./union.bin
	rm ./union.bin

intersection: build
	gcc -I ./include ./cet.so ./examples/intersection.c -o ./intersection.bin
	./intersection.bin
	rm ./intersection.bin

difference: build
	gcc -I ./include ./cet.so ./examples/difference.c -o ./difference.bin
	./difference.bin
	rm ./difference.bin

map: build
	gcc -I ./include ./cet.so ./examples/map.c -o ./map.bin
	./map.bin
	rm ./map.bin
