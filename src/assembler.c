#include"../lib/asm_lib.h"

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

#define MAX_BUF_SIZE 50

void check_delim()
{

}
void process_args1(struct Instruction *Inst)
{
    // if(strcmp(Inst->arg[0],""))
    int i;
    printf("Args: ");
    for(i=0;i<=Inst->narg;i++)
    {
        printf("%s ",Inst->arg[i]);
        // puts(Inst->arg[i]);
    }
    printf("\n");
}
int main(int argc,char *argv[])
{
    FILE *fp_in,*fp_out;
    int line=1,nums;
    size_t len;
    char asm_filename[20],op_filename[20],str[50],sep,flag=0; // flag: To indicate valid instruction, to filter processing, incase of empty ones
    char req_comma=0,newline=0;      // Indicates that an argument is required currently, without which error is raised
    struct Instruction Ins;
    switch(argc)
    {
        case 1:
            fprintf(stderr,"Error: Input Assembly Language file not specified!\n");
            exit(1);
        case 2:         // Input file specified
            strcpy(op_filename,"a.txt");
            break;
        case 3:
            strcpy(op_filename,argv[2]);
    }
    strcpy(asm_filename,argv[1]);
    fp_in=fopen(asm_filename,"r");
    if(ferror(fp_in))
    {
        fprintf(stderr,"Input File opening error!\n");
        exit(1);
    }
    fp_out=fopen(op_filename,"w");
    if(ferror(fp_out))
    {
        fprintf(stderr,"Output File opening error!\n");
        exit(1);
    }
    fprintf(fp_out,"// RV32-I Machine code for Assembly File \"%s\"",asm_filename);
    Ins.narg=-1;
    while(!feof(fp_in))
    {
        nums=fscanf(fp_in," %[^ ,#\n]%c",str,&sep);   // Stop when newline, comma, hash or space is encountered
        switch(nums)
        {
            case EOF:               // The case of a line ending with comma is not addressed
                sep='\n';
                break;
            case 0:                 // Case where a comma or hash is encountered first
                fscanf(fp_in," %c",&sep);
                break;
            // 1 is the case when File ends with a string
            // 2 is the case when both string and character get scanned successfully
            case 1:
                sep='\n';
            default:
                if(req_comma)
                {
                    fprintf(stderr,"Line %d: Unexpected space separation between two literals, Narg: %d\n",line,Ins.narg);
                    exit(1);
                }
                flag=1;
                req_comma=(Ins.narg!=-1);
                Ins.narg++;
                strcpy(Ins.arg[Ins.narg],str);
        }
        switch(sep)
        {
            case ',':
                if(!req_comma)
                {
                    fprintf(stderr,"Error: Line %d: Unexpected ',' after \"%s\"\n",line,str);
                    exit(1);
                }
                req_comma=0;
                break;
            case ' ':
                continue;
            case '#':
                fscanf(fp_in,"%*[^\n]");
            case '\n':
                line++;
                if(flag)
                    process_args1(&Ins);
                flag=0;
                Ins.narg=-1;
                req_comma=0;
        }
    }
    fclose(fp_in);
    fclose(fp_out);
    return 0; 
}
