//Q)Write a command line program for line editor. The file to be edited is taken as command line argument.
//  An empty file is opened for editing if no argument is supplied. It should display „$‟ prompt to accept the
//   line editing commands. Implement the following commands:
// a - Append
// d n- Delete Nth Line
//  p - Print all Lines
// e - Exit

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct node
{
 char line[80];
 struct node *next;
}NODE;

NODE *first,*last;
int len,changed;

NODE * get_node(char *s)
{
 NODE *p;
 p=(NODE*)malloc(sizeof(NODE));
 strcpy(p->line,s);
 p->next=NULL;
 return p;
}

void create(char fname[])
{
 NODE *p;
 FILE *fp;
 char buff[80];

 fp = fopen(fname,"r");
 if(fp==NULL)
 {
  printf("File %s not found.\n",fname);
  exit(1);
 }

 while(fgets(buff,80,fp)!=NULL)
 {
  p = get_node(buff);
  
  if(first==NULL)
   first = p;
  else
   last->next = p;

  last = p;
  len++;
 }

 fclose(fp);
}

void append()
{
 NODE *p;
 char buff[80];

 printf("Enter text (type END to stop):");
 
 fflush(stdin);
 fgets(buff,80,stdin);

 while(strcmp(buff,"END\n")!=0)
 {
  p = get_node(buff);
  if(first==NULL)
   first = p;
  else
   last->next = p;
  last=p;
  len++;

  fflush(stdin);
  fgets(buff,80,stdin);
 }

 changed=1;
}

void print()
{
 NODE *p;
 int i=1;
 
 p=first;
 while(p!=NULL)
 {
  printf("%d:%s",i,p->line);
  i++;
  p=p->next;
 }
}

void del(int pos)
{
 NODE *p,*q;
 int i=1;
 
 p = q = first;
 while(i<pos)
 {
  q = p;
  p = p->next;
  i++;
 }

 if(p==first)
 {
  first = p->next;
 }
 else if(p==last)
 {
  q->next=NULL;
  last=q;
 }
 else
 {
  q->next=p->next;
 }
 
 free(p);
 len--;
 changed=1;
} 

int main(int argc, char *argv[])
{
 char buff[80],ch,fname[30]="";
 int n;

 if(argc==2)
 {
  strcpy(fname,argv[1]);
  create(fname);
 }

 while(1)
 {
  printf("$");
  fflush(stdin);
  fgets(buff,80,stdin);

  sscanf(buff,"%c %d",&ch,&n);

  switch(ch)
  {
  case 'a':
   append();
   break;
  case 'p':
   print();
   break;
  case 'd':
   if(n>=1 && n<=len)
    del(n);
   else
    printf("Invalid position: %d\n",n);
   break;
  case 'e':
   exit(0);
  default:
   printf("Invalid command.\n");
  }
 }

 return 0;
}