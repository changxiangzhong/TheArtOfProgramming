# specify the TARGET in make commandline
include ${TARGET}

DEPS=dispatcher.h util.h array.h
OBJ=dispatcher.o main.o util.o array.o
EXECUTABLE=find_prime_nbr

build_x86:
	$(MAKE)  TARGET=x86.mk build

all:
	$(MAKE) -B TARGET=x86.mk build
	$(MAKE) -B TARGET=arm_v7a.mk build

build: $(OBJ)
	$(CC) -o $(EXECUTABLE).${ARCH} $(OBJ) $(LDFLAGS)
	ctags ./*.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $<  $(CFLAGS)

clean:
	rm -rf *.o  a.out $(EXECUTABLE).* tags 
