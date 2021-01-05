STD=c99
GDB=-ggdb
WALL=-Wall


exec: main.o input.o fork_exec.o variables.o
    gcc $(WALL) -std=c99 $(GDB) main.o input.o fork_exec.o variables.o -o

main.o: main.c main.h variables.h
    gcc $(WALL) -std=$(STD) $(GDB) main.c -c main.o

input.o: input.c input.h fork_exec.h variables.h variables.c
    gcc $(WALL) -std=$(STD) $(GDB) input.c -c input.o

fork_exec.o: fork_exec.c fork_exec.h
    gcc $(WALL) -std=$(STD) $(GDB) fork_exec.c -c fork_exec.o

variables.o: variables.c variables.h
    gcc $(WALL) -std=$(STD) $(GDB) variables.c -c variables.o
