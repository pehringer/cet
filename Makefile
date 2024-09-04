build:
	gcc -fPIC -shared -I ./include ./src/set.c -o set.so

test: build
	gcc -I include ./set.so ./tests/tests.c -o tests.bin
	./tests.bin
	rm tests.bin

