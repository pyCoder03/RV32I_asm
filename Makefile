# Makefile

.PHONY: all
all:  	assembler

asm_lib:	./lib/asm_lib.c ./lib/asm_lib.h
	gcc -c ./lib/asm_lib.c -o ./lib/asm_lib.o

assembler: ./src/assembler.c ./lib/asm_lib.c ./lib/asm_lib.h
	gcc -c ./lib/asm_lib.c -o ./obj/asm_lib.o
	gcc -c ./src/assembler.c -o ./obj/assembler.o
	gcc ./obj/asm_lib.o ./obj/assembler.o -o ./build/assembler.out

SampleC:	./src/SampleC.c
	gcc ./src/SampleC.c -o ./build/SampleC.out

.PHONY: clean
clean:
	rm -f ./obj/*.o
	rm -f ./build/*.out