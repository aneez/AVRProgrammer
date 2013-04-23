# Makefile for Linux and QNX
#  
# For other operating systems see the build files in these subdirectories.
# Linux and QNX users just type "make" in this directory to build all 
# the demo programs for this board.
#

LIB= -lftdi 
INC=
CC=gcc
CFLAGS= -Wall -Os
TGT=MasterControl
SRCS=$(wildcard *.c)
OBJDEPS=$(patsubst %.c,%.o,$(SRCS))

.SUFFIXES : .c .o \  
.c.o: 
	$(CC) $(CFLAGS) -c $< -o $@ 
		
all: $(TGT)

$(TGT): $(OBJDEPS)  
	$(CC) -o $@ $^ $(LIB) $(INC)

clean:
	rm -f $(TGT) *.o
