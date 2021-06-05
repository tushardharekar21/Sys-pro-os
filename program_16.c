//Q) Write a program to implement a DFA Driver for any given language. Accept number of states, number of
//  input symbols, set of input symbols, number of final states, set of final states and transition table as input. 
//  (Input language should be given by examiner). Write menu driven program that will have options as:
// Read DFA 
// Show Transition Table
// Check Acceptance of the Given String
// Exit

#include<stdio.h>
#include<stdlib.h>
#define MAX 10

int nos,noi,nof,finals[MAX],trans[MAX][MAX];
char input_symb[MAX],input_str[100];

void read_dfa()
{
 int i,j;

 printf("Enter no.of states:");
 scanf("%d",&nos);

 printf("Enter no.of input symbols:");
 scanf("%d",&noi);

 printf("Enter input symbols:");

 scanf("%s",input_symb);

 printf("Enter no.of finals:");
 scanf("%d",&nof);

 printf("Enter finals states:");
 for(i=0;i<nof;i++)
  scanf("%d",&finals[i]);

 printf("Enter transition table:\n");

 for(i=0;i<nos;i++)
 {
  for(j=0;j<noi;j++)
  {
   printf("d(q%d,%c)=",
    i,input_symb[j]);
   scanf("%d",&trans[i][j]);
  }
 }
}

void show_trans()
{
 int i,j;

 printf("M=(Q,E,d,q0,F)\n");

 printf("Q={");
 for(i=0;i<nos;i++)
  printf("q%d,",i);
 printf("\b}\nE={");
 for(i=0;i<noi;i++)
  printf("%c,",input_symb[i]);
 printf("\b}\nq0=q0\nF={");
 for(i=0;i<nof;i++)
  printf("q%d,",finals[i]);
 printf("\b}\nd:\n\t");

 for(i=0;i<noi;i++)
  printf("%c\t",input_symb[i]);

 printf("\n");

 for(i=0;i<nos;i++)
 {
  printf("q%d\t",i);
  for(j=0;j<noi;j++)
   printf("q%d\t",trans[i][j]);
  printf("\n");
 }
}

void check()
{
 int i,j,curr;

 printf("Enter input string:");
 scanf("%s",input_str);

 curr = 0;
 for(i=0;input_str[i]!='\0';i++)
 {
  printf("d(q%d,%s)\n",curr,input_str+i);
  curr = trans[curr][input_str[i]-input_symb[0]];
 }

 printf("q%d\n",curr);

 for(i=0;i<nof;i++)
 {
  if(finals[i]==curr)
  {
   printf("Accept\n");
   return;
  }
 }

 printf("Reject\n");
}

int main()
{
 int ch;
 while(1)
 {
  printf("1.Read DFA\n2.Show Transition Table\n3.Check acceptance of given string\n4.Exit\n");
  printf("Enter choice (1-4):");
  scanf("%d",&ch);

  switch(ch)
  {
  case 1:
   read_dfa();
   break;
  case 2:
   show_trans();
   break;
  case 3:
   check();
   break;
  case 4:
   exit(0);
  }
 }

 return 0;
}
