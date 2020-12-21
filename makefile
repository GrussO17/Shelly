
STD=c99



main: main.c
    gcc std=$(STD) main.c -o $(srcdir)/bin/main

