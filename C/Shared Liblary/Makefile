all: zad2 lib.so

zad2: main.c lib.so
	gcc main.c -o zad2 -ldl

lib.so: lib.o
	gcc -shared -fPIC lib.o -o lib.so

lib.o: lib.c
	gcc -c -fPIC lib.c -o lib.o
