STD=c99
GDB=-ggdb
WALL=-Wall


exec: main.o input.o fork_exec.o variables.o
	gcc $(WALL) -std=c99 $(GDB) main.o input.o fork_exec.o variables.o -o exec

main.o: main.c main.h variables.h
	gcc $(WALL) -std=$(STD) $(GDB) -c main.c

input.o: input.c input.h fork_exec.h variables.h variables.c
	gcc $(WALL) -std=$(STD) $(GDB) -c input.c

fork_exec.o: fork_exec.c fork_exec.h variables.h variables.c input.h input.c
	gcc $(WALL) -std=$(STD) $(GDB) -c fork_exec.c

variables.o: variables.c variables.h
	gcc $(WALL) -std=$(STD) $(GDB) -c variables.c

clean:
	rm *.o exec

