# Flags
CC?=cc
AS?=as
LD?=ld 
CFLAGS=-Wall -Wextra -Wpedantic -c -m32 -ffreestanding -Isrc/include
LDFLAGS=-m elf_i386 -Tsrc/linker.ld -nostdlib

OBJC=$(shell find src -type f -name '*.c' | sed 's/\b.c\b/.o/g')
OBJS=$(shell find src -type f -name '*.s' | sed 's/\b.s\b/.o/g')
OBJ=$(OBJC) $(OBJS) 

all: $(OBJ) kernel.com

# Rules
%.o: %.c
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.s # do wyrzucenia
	$(AS) --32 -o $@ $^

kernel.com: $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $^

clean:
	rm -f $(OBJ) kernel.com

.PHONY: clean
