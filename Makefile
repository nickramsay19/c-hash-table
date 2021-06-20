all: main

main: build/main.o build/HashTable.o build
	gcc -o main build/main.o build/HashTable.o

build:
	mkdir build

build/main.o: main.c build
	gcc -o build/main.o -c main.c

build/HashTable.o: HashTable.c build
	gcc -o build/HashTable.o -c HashTable.c

clean: 
	rm -R build/* main