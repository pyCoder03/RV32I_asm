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
    // int i;
    // printf("Args: ");
    // for(i=0;i<=Inst->narg;i++)
    // {
    //     printf("%s ",Inst->arg[i]);
    //     // puts(Inst->arg[i]);
    // }
    // printf("\n");
}
int main(int argc,char *argv[])
{
    FILE *fp_in,*fp_out;
    int line=1,nums;
    size_t len;
    char asm_filename[20],op_filename[20],str[50],sep,flag=0; // flag: To indicate valid instruction, to filter processing, incase of empty ones
    char req_comma=0,newline=0;      // Indicates that an argument is required currently, without which error is raised
    struct Instruction Ins;
    // printf("Hiii\n");
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
    // printf("Hiii\n");
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
    // printf("Hiii\n");
    fprintf(fp_out,"// RV32-I Machine code for Assembly File \"%s\"",asm_filename);
    Ins.narg=-1;
    while(!feof(fp_in))
    {
        nums=fscanf(fp_in," %[^ ,#\n]%c",str,&sep);   // Stop when newline, comma, hash or space is encountered
        printf("Nums: %d\n",nums);
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
                printf("Str: %s; Ch: %c\n",str,sep);
                if(req_comma)
                {
                    fprintf(stderr,"Line %d: Unexpected space separation between two literals, Narg: %d\n",line,Ins.narg);
                    exit(1);
                }
                flag=1;
                req_comma=(Ins.narg!=-1);
                Ins.narg++;
                strcpy(Ins.arg[Ins.narg],str);
                printf("Indha %s %s\n",Ins.arg[Ins.narg],str);
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
                // break;
            case '\n':
                printf("NEWLINE\n");
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
    // while(!feof(fp_in))
    // {
    //     sep=fgetc(fp_in);
    //     fseek(fp_in,-1,SEEK_CUR);
    //     if(sep==-1)
    //     {
    //         if(Ins.narg>0)
    //         {
    //             fprintf(stderr,"Error: Line %d: Unexpected End of Line\n",line);
    //             exit(1);
    //         }
    //         if(flag)
    //             process_args(&Ins);
    //         flag=0;
    //         continue;
    //     }
    //     else if(sep=='#')
    //     {
    //         fscanf(fp_in,"%*[^\n]");
    //         continue;
    //     }
    //     else                    // There is no empty character '' in C, NULL ('\0') can be used
    //     {    
    //         nums=fscanf(fp_in," %[A-Za-z0-9]%c",str,&sep);
    //         len=strlen(str);
    //         if(len)
    //             Ins.narg++;
    //         else if(Ins.narg==-1)       // Unexpected character
    //         {
    //             fprintf(stderr,"Error: Line %d: Unexpected Start of Line\n",line);
    //             exit(1);
    //         }
    //         fscanf(fp_in," %c",&sep);
    //         if(Ins.narg)
    //         {
    //             if(sep==',' || sep==',\n')
    //                 continue;
    //             else if(sep=='#')
    //                 fscanf(fp_in,"%*[^\n]");
    //             else
    //             {
    //                 fprintf(stderr,"Error: Line %d: Unexpected Character %c\n",line,sep);
    //                 exit(1);
    //             }
    //         }
    //     }
    // }
    // while(!feof(fp_in))
    // {
    //     printf("\n\nFTELL: %ld\n",ftell(fp_in));
    //     // printf("Hiii\n");
    //     sep=fgetc(fp_in);
    //     printf("\nSappu %d\n",sep);
    //     if(sep==-1 && !req_arg)                 // Note that last character sep for this one-word case is \n, if scanned past that, sep becomes -1
    //     {
    //         break;
    //     }    
    //     fseek(fp_in,-1,SEEK_CUR);
    //     if(sep==' ' || sep=='\n')
    //         nums=fscanf(fp_in," %[A-Za-z0-9]%c",str,&sep);
    //     // else if(sep=='\n' ||)
    //     else
    //         nums=fscanf(fp_in,"%[A-Za-z0-9]%c",str,&sep);
    //     printf("\n\nAhhhahahaha Ippo FTELL: %ld\n",ftell(fp_in));
    //     if(!nums)
    //     {
    //         printf("Scan seri illa\n");
    //         if(req_arg)
    //         {
    //             fprintf(stderr,"Line %d: Unexpected End of Line\n",line);
    //             exit(1);
    //         }
    //         printf("\n\nIppo FTELL: %ld\n",ftell(fp_in));
    //         Ins.narg=-1;
    //         continue;
    //     }
    //     len=strlen(str);
    //     printf("Display %lu %s %d, Scanned: %d\n",len,str,sep,nums);
    //     // if(Ins.narg==-1)         // && sep!='#' && sep!='\n' && sep!=' ')
    //     //     req_arg=1;
    //         // fprintf(stderr,"Line %d: Unexpected character %c\n",line,sep);
    //     (feof(fp_in))?printf("\nEOF"):printf("\nNot EOF");
    //     printf(" ftell: %lu\n",ftell(fp_in));
    //     if(Ins.narg==-1)
    //         req_arg=1;
    //     if(!req_arg && Ins.narg && len)
    //     {
    //         fprintf(stderr,"Line %d: Unexpected space separation between two literals, Narg: %d\n",line,Ins.narg);
    //         exit(1);
    //     }
    //     if(len)
    //         Ins.narg++;
    //     printf("Narg: %d\n",Ins.narg);
    //     newline=(sep=='#' || sep=='\n');
    //     if(!sep)
    //         sep='#';
    //     // printf("Hiii\n");
    //     switch(sep)
    //     {
    //         // case '\n':
    //         // case ',':
    //         //     if(Ins.narg==0)
    //         //     {
    //         //         fprintf(stderr,"Line %d: Unexpected ',' after instruction\n",line);
    //         //         exit(1);
    //         //     }
    //         //     if(strlen(str)==0)
    //         //     {

    //         //     }
    //         //     break;
    //         case ' ':
    //             req_arg=0;
    //             break;
    //         case ',':
    //             if(req_arg)
    //             {
    //                 fprintf(stderr,"Line %d: Unexpected ','\n",line);
    //                 exit(1);
    //             }
    //             req_arg=1;    
    //             break;
    //         case '#':                     // '#' is being used as a comment line
    //             printf("\nComment daaaa\n");
    //             fscanf(fp_in,"%*[^\n]");
    //             // fgets(discard,MAX_BUF_SIZE,fp_in);
    //         case '\n':
    //             if(req_arg && Ins.narg)
    //             {
    //                 fprintf(stderr,"Line %d: Unexpected End of Line\n",line);
    //                 exit(1);
    //             }
    //             req_arg=0;
    //             break;
    //     }
    //     // printf("Hiii\n");
    //     strcpy(Ins.arg[Ins.narg],str);
    //     printf("Arg: %s\n",Ins.arg[Ins.narg]);
    //     if(newline && Ins.narg)
    //     {
    //         for(int i=0;i<=Ins.narg;i++)
    //             printf("%s ",Ins.arg[i]);
    //         printf("\nPrint panniten\n");
    //         Ins.narg=-1;
    //         // break;
    //     }
    //     // break;
    // }
    // } 
    return 0; 
}
