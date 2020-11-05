main: main.o sem.o
	gcc main.o sem.o -o main -lpthread

main.o: main.c
	gcc -c main.c

sem.o: sem.c
	gcc -c sem.c

clean: 
	rm main.o sem.o main
