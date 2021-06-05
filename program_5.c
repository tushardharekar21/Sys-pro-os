//Q) Implement a menu driven simulator for hypothetical Simple Instruction Computer that provides the following functionalities.
// Load – Loading of the program from file into memory 
// Print – Printing the program loaded in memory. 
// Run – Executing the loaded program

#include<stdio.h>
#include<stdlib.h>

int mem[100],reg[4],cond[]={0,0,0,0,0,1},opc,op1,op2,pc;
FILE *fp;
char fname[20];

void load()
{
 printf("Enter file name:");
 scanf("%s",fname);

 fp = fopen(fname,"r");
 if(fp==NULL)
 {
  printf("File %s not found.\n",fname);
  exit(1);
 }

 while(fscanf(fp,"%d",&mem[pc])!=-1)
  pc++;

 fclose(fp);
}

void print()
{
 int i;
 for(i=0;i<pc;i++)
  printf("%06d\n",mem[i]);
}

void run()
{
 int i;
 pc = 0;
 while(1)
 {
  opc = mem[pc]/10000;
  op1 = mem[pc]%10000/1000-1;
  op2 = mem[pc]%1000;

  switch(opc)
  {
  case 0: // STOP
   return;
  case 3: // ADD
   reg[op1]+=mem[op2];
   break;
  case 4: // SUB
   reg[op1]-=mem[op2];
   break;
  case 7: // MULT
   reg[op1]*=mem[op2];
   break;
  case 8: // DIV
   reg[op1]/=mem[op2];
   break;
  case 5: // MOVER
   reg[op1]=mem[op2];
   break;
  case 6: // MOVEM
   mem[op2]=reg[op1];
   break;
  case 10:// COMP
   if(reg[op1] < mem[op2])
    cond[0]=1;
   if(reg[op1] <= mem[op2])
    cond[1]=1;
   if(reg[op1] == mem[op2])
    cond[2]=1;
   if(reg[op1] > mem[op2])
    cond[3]=1;
   if(reg[op1] >= mem[op2])
    cond[4]=1;
   break;
  case 9: // BC
   if(cond[op1]==1)
    pc = op2-1;
   
   for(i=0;i<5;i++)
    cond[i]=0;
   break;
  case 1: // READ
   scanf("%d",&mem[op2]);
   break;
  case 2:// PRINT
    printf("%d\n",mem[op2]);
  }
  pc++;
 }
}

int main()
{
 int ch;

 while(1)
 {
  printf("1.Load\n2.Print\n3.Run\n4.Exit\n");
  printf("Enter your choice (1-4):");
  scanf("%d",&ch);

  switch(ch)
  {
  case 1:
   load();
   break;
  case 2:
   print();
   break;
  case 3:
   run();
   break;
  case 4:
   exit(0);
  }
 }

 return 0;
} 
  
