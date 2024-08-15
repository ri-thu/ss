#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
    FILE *optab,*input,*symtab,*inter,*len;
    int locctr,start=0;
    char mnemonic[15],opcode[25],operand[25],label[25],code[25];
    optab=fopen("OPTAB.txt","r");
    input=fopen("INPUT.txt","r");
    symtab=fopen("SYMTAB.txt","w");
    inter=fopen("INTER.txt","w");
    len=fopen("LEN.txt","w");
    if(optab==NULL||input==NULL||symtab==NULL||inter==NULL)
    {
        printf("One File is not open\n");
    }
    fscanf(input,"%s\t%s\t%s",label,opcode,operand);
    if(strcmp(opcode,"START")==0)
    {
        start=atoi(operand);
        locctr=start;
        printf("START IS %d\n",start);
        fprintf(inter,"%s\t%s\t%s\n"label,opcode,operand);
    }
    else
    {
        locctr=0;
    }
    fscanf(input,"%s\t%s\t%s",label,opcode,operand);
    while(strcmp(opcode,"END"))
    {
        fprintf(inter,"%d\t",locctr);
        if(strcmp(label,"**")!=0)
        {
            fprintf(symtab,"%s\t%d\t",label,locctr);

        }
        fscanf(optab,"%s\t%s",code,mnemonic);
        while(strcmp(code,"END")!=0)
        {
            if(strcmp(code,opcode)==0)
            {
                locctr+=3;
                rewind(optab);
                fscanf(optab,"%s\t%s",code,mnemonic)
            }
            if(strcmp(opcode,"WORD")==0)
            {
                locctr+=3;
            }
            else if(strcmp(opcode,"RESW")==0)
            {
                locctr+=3*(atoi(operand));
            }
            else if(strcmp(opcode,"RESB"))
            {
                locctr+=atoi(operand);
            }
            else if(strcmp(opcode,"BYTE"))
            {
                if(operand[0]=='C')
                {
                    locctr+=(strlen(operand)-3);
                }
                else if(operand[0]=='X')
                {
                    printf("\n##1##");
                    locctr++;
                }
            }
            fprintf(inter,"%s\t%s\t%s\n",label,opcode,operand);
            fprintf(input,"%s\t%s\t%s",label,opcode,operand);
        }
        fprintf(inter,"%s\t%s\t%s\n",label,opcode,operand);
        printf("LEngth of program is %d\n",locctr-start);
        fprintf(len,"%d",locctr-start);
        fscanf(len,"%d",locctr-start);
        fclose(len);
        fclose(optab);
        fclose(inter);
        fclose(symtab);
        fclose(input);
    }