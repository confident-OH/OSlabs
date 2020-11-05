main: main.o print_dir.o turnst_mode.o count_blocks.o
	gcc main.o print_dir.o turnst_mode.o count_blocks.o -o main

main.o: main.c
	gcc -c main.c

print_dir.o: print_dir.c 
	gcc -c print_dir.c

count_blocks.o: count_blocks.c
	gcc -c count_blocks.c

turnst_mode.o: turnst_mode.c
	gcc -c turnst_mode.c

clean:
	rm main.o main print_dir.o count_blocks.o turnst_mode.o