NDK=/home/xiangzhc/android-ndk-r10d
CC=${NDK}/toolchains/arm-linux-androideabi-4.8/prebuilt/linux-x86/arm-linux-androideabi/bin/gcc
SYSROOT=${NDK}/platforms/android-21/arch-arm
CFLAGS=-I. -g -Wall -DDEBUG -std=gnu99 --sysroot=${SYSROOT}  -fPIE
LDFLAGS=-lm --sysroot=${SYSROOT} -fPIE -pie

ARCH=arm_v7a
