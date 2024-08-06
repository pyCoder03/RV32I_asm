#include "../lib/asm_lib.h"

// void write_bits(struct Instruction *p)
// {
//     int i=0;
//     char Ins[20];
//     strcpy(Ins,p->arg[0]);
//     if(strcmp(Ins,"org"))
//     for(i=0;i<p->narg;i++)
//     {

//     }
// }

void process_args(FILE *fp,struct Instruction *Ins)
{
    int i,pc,nums,len;
    char ch;
    struct Machine_Instruction insM;
    if(strcmp(Ins->arg[0],"org")==0)
    {
        if(Ins->narg!=1)
        {
            fprintf(stderr,"Incorrect use of \"org\" directive");
            fprintf(fp,"\n// Writing stopped due to error in Assembly file");
            exit(1);
        }
        else
        {
            nums=sscanf(Ins->arg[1],"%xh",&Program_Counter);
            if(!nums)
            {
                fprintf(stderr,"Incorrect use of \"org\" directive");
                fprintf(fp,"\n// Writing stopped due to error in Assembly file");
                exit(1);
            }   
        }
    }
    else if(strcmp(Ins->arg[0],"addi")==0)
    {
        insM.opcode=OP_IMM;
        sscanf(Ins->arg[1],"x%d",&insM.rd);
        sscanf(Ins->arg[2],"x%d",&insM.rs1);
        len=strlen(Ins->arg[3]);
        ch=Ins->arg[3][len-1];
        switch(ch)
        {
            case 'h':
                sscanf(Ins->arg[3],"%xh",&insM.immediate);
                break;
            default:
                sscanf(Ins->arg[3],"%i",&insM.immediate);   // Since C doesn't have format specifiers for binary, %i can be used, 
                                                            // but while writing assembly code, 0b prefix must be used  
                break;
        }
        insM.funct3=ADDI;
        write_bits_I(&insM);
    }
    else if(strcmp(Ins->arg[0],"nop")==0)
    {
        
    }

}

void write_bits_R(struct Machine_Instruction *p)
{
    p->machine_code=p->opcode;
    p->machine_code|=(p->rd << 7);
    p->machine_code|=(p->funct3 << 12);
    p->machine_code|=(p->rs1 << 15);
    p->machine_code|=(p->rs2 << 20);
    p->machine_code|=(p->funct7 << 25);    
}

void write_bits_I(struct Machine_Instruction *p)
{
    p->machine_code=p->opcode;
    p->machine_code|=(p->rd << 7);
    p->machine_code|=(p->funct3 << 12);
    p->machine_code|=(p->rs1 << 15);
    p->machine_code|=(p->immediate << 20);    
}

void write_bits_S(struct Machine_Instruction *p)
{
    p->machine_code=p->opcode;
    p->machine_code|=((p->immediate & 0x1f) << 7);
    p->machine_code|=(p->funct3 << 12);
    p->machine_code|=(p->rs1 << 15);
    p->machine_code|=(p->rs2 << 20);
    p->machine_code|=((p->immediate & 0xfe0) << 20);    
}

void write_bits_B(struct Machine_Instruction *p)
{
    p->machine_code=p->opcode;
    p->machine_code|=((p->immediate & 0x800) >> 4);
    p->machine_code|=((p->immediate & 0x1e) >> 7);
    p->machine_code|=(p->funct3 << 12);
    p->machine_code|=(p->rs1 << 15);
    p->machine_code|=(p->rs2 << 20);
    p->machine_code|=((p->immediate & 0x7e0) << 20);
    p->machine_code|=((p->machine_code & 0x1000) << 19);    
}

void write_bits_U(struct Machine_Instruction *p)
{
    p->machine_code=p->opcode;
    p->machine_code|=(p->rd << 7);
    p->machine_code|=(p->immediate & 0xfffff000);
}

void write_bits_J(struct Machine_Instruction *p)
{
    p->machine_code=p->opcode;
    p->machine_code|=(p->rd << 7);
    p->machine_code|=(p->immediate & 0xff000);
    p->machine_code|=((p->immediate & 0x800) << 9);
    p->machine_code|=((p->immediate & 0x7fe) << 19);
    p->machine_code|=((p->immediate & 0x100000) << 11);
}

