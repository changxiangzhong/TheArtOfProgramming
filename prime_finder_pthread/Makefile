CC=c99
CFLAGS=-I. -g -Wall -D DEBUG
LDFLAGS= -lm -lpthread
DEPS=dispatcher.h util.h array.h
OBJ=dispatcher.o main.o util.o array.o
EXECUTABLE=find_prime_nbr

dist: $(OBJ)
	$(CC) -o $(EXECUTABLE) $(OBJ) $(LDFLAGS)
	ctags ./*.c


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $<  $(CFLAGS)

clean:
	rm -rf *.o  a.out $(EXECUTABLE) tags 
