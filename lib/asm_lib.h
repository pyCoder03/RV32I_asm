#ifndef STDIO_H
#include<stdio.h>
#define STDIO_H
#endif

#ifndef STDLIB_H
#include<stdlib.h>
#define STDLIB_H
#endif

#ifndef STRING_H
#include<string.h>
#define STRING_H
#endif

#ifndef CTYPE_H
#include<ctype.h>
#define CTYPE_H
#endif

int Program_Counter=0x0000,line=0;

struct Instruction{     // Instruction has the following arguments: Instruction name and operands
    int narg;           // Number of actual arguments
    char arg[20][50];   // Argument list
};

struct Machine_Instruction{
    unsigned int opcode;
    unsigned int funct7,funct3,rs1,rs2,rd;
    unsigned int immediate;
    unsigned int machine_code;
};

enum opcode_type{OP,OP_IMM,LUI,AUIPC,JAL,JALR,BRANCH,LOAD,STORE};
enum funct3_op{ADDI,SLTIU,ANDI,ORI,XORI,SLLI,SRLI,SRAI};

enum funct3_op_imm{ADD,SLT,SLTU,AND,OR,XOR,SLL,SRL,SUB,SRA};
enum funct7_op_imm{SET1=0,SET2=0b0100000};

void process_args(FILE *,struct Instruction *);

void write_bits_R(struct Machine_Instruction *);
void write_bits_I(struct Machine_Instruction *);
void write_bits_S(struct Machine_Instruction *);
void write_bits_B(struct Machine_Instruction *);
void write_bits_U(struct Machine_Instruction *);
void write_bits_J(struct Machine_Instruction *);