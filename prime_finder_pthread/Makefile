# CC=gcc
# CFLAGS=-I. -g -Wall -DDEBUG -std=gnu99
# LDFLAGS= -lm -lpthread 
# CFLAGS=-I. -g -Wall -DDEBUG -std=c99 -D_USE_SPINLOCK

NDK=/home/xiangzhc/Tools/android-ndk-r10d
CC=${NDK}/toolchains/arm-linux-androideabi-4.8/prebuilt/linux-x86_64/arm-linux-androideabi/bin/gcc
SYSROOT=${NDK}/platforms/android-21/arch-arm
CFLAGS=-I. -g -Wall -DDEBUG -std=gnu99 --sysroot=${SYSROOT}  -fPIE
LDFLAGS=-lm --sysroot=${SYSROOT} -fPIE -pie

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
