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
    int pc,nums;
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
            nums=sscanf(Ins->arg[1],"%xh",&pc);
            if(!nums)
            {
                fprintf(stderr,"Incorrect use of \"org\" directive");
                fprintf(fp,"\n// Writing stopped due to error in Assembly file");
                exit(1);
            }   
        }
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

