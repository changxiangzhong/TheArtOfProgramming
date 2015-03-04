CC=c99
CFLAGS=-I. -g -Wall -D DEBUG
LDFLAGS=
DEPS=binary_tree.h stack.h
OBJ=binary_tree.o main.o stack.o
EXECUTABLE=tree

dist: $(OBJ)
	$(CC) -o $(EXECUTABLE) $(OBJ) $(LDFLAGS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $<  $(CFLAGS)

clean:
	rm -rf *.o  a.out $(EXECUTABLE)
