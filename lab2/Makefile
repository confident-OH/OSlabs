main_1: thread_main.o sem.o 
		cc -o main thread_main.o sem.o -lpthread

sem.o: sem.c
		cc -c sem.c -lpthread

thread_main.o: thread_main.c sem.o
		cc -c thread_main.c sem.o -lpthread

main_2: print_main.o sem.o
		cc -o main print_main.o sem.o -lpthread

print_main.o: print_main.c sem.o
		cc -c print_main.c sem.o -lpthread

clean1: 
		rm sem.o thread_main.o main

clean2:
		rm sem.o main print_main.o