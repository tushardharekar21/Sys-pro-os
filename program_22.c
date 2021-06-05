//Q) Write a program to implement a DFA driver for the language L = “Set of all strings that containing 101 as
//  substring” over {0,1}.

#include<stdio.h>

int nos=4;
int noi=2;
char input_symb[]={'0','1'};
int nof=1,final=3;
int d[][2]={{0,1},{2,1},{0,3},{3,3}};
char input_str[100];

int main()
{
 int i,j,curr;

 printf("M=(Q,E,d,q0,F)\n");
 printf("Q={");
 for(i=0;i<nos;i++)
  printf("q%d,",i);
 printf("\b}\nE={");
 for(i=0;i<noi;i++)
  printf("%c,",input_symb[i]);
 printf("\b}\nq0=q0\nF={q%d}\nd:\n\t",final);

 for(i=0;i<noi;i++)
  printf("%c\t",input_symb[i]);
 printf("\n");

 for(i=0;i<nos;i++)
 {
  printf("q%d\t",i);
  for(j=0;j<noi;j++)
   printf("q%d\t",d[i][j]);
  printf("\n");
 }

 do
 {
  printf("Enter input string:");
  scanf("%s",input_str);

  curr = 0;
  for(i=0;input_str[i]!='\0';i++)
  {
   printf("d(q%d,%s)\n",curr,
    input_str+i);
   curr=d[curr][input_str[i]-input_symb[0]];
  }

  printf("q%d\n",curr);

  if(curr==final)
   printf("Accept\n");
  else
   printf("Reject\n");
  
  printf("Continue Y(1)/N(0)?");
  scanf("%d",&j);
 }while(j==1);

 return 0;
}
