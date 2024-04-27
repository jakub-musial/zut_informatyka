all: lab7

lab7 : main.o timer.o
	gcc -o lab7 main.o timer.o

main.o : main.c
	gcc -c main.c

timer.o : timer.c
	gcc -c timer.c

clean:
	rm -f lab7 main.o timer.o