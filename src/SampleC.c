#include<stdio.h>
int main()
{
    int i,nums;
    char str[20],ch;
    FILE *fp;
    fp=fopen("Sample.txt","r");
    // for(i=0;i<3;i++)
    // {
    //     printf("\nEnter your input: ");
    //     nums=fscanf(stdin,"%[A-Za-z0-9]%c",str,&ch);
    //     fflush(stdin);
    //     printf("%s %c %d, Scanned: %d\n",str,ch,ch,nums);
    // }
    // nums=scanf(" %[A-Za-z0-9]%c",str,&ch);           // " %s" can support n number of preceding spaces, including 0
    scanf(" ( %x h )",&i);
    printf("%d: %x\n",i,i);
    // while(!feof(fp))
    // {
    //     nums=fscanf(fp," %[^ ,#\n]%c",str,&ch);                 // Main hurdle here (maybe a loophole, not a hurdle), is when line starts with # or ,
    //     // Nothing is recorded in str (expected) and ch as well (not expected), so the format specifier expects atleast one character in str
    //     // printf("%d\n",scanf(""));
    //     // In total, each format specifier expects to scan some non empty thing into it, without which the scan fails as soon as the null condition is encountered
    //     // ... Same as told in the Linux manual
    //     if(ch=='#')
    //         fscanf(fp,"%*[^\n]");
    //     printf("%d: %s %c %d\n",nums,str,ch,ch);
    // }
    return 0;
}