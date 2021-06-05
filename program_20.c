//Q) Write a command line program for line editor. The file to be edited is taken as command line arguments. 
// An empty file is opened for editing if no argument is supplied. It should display a „$‟ prompt to accept the
//  line editing commands. Implement the following commands: 
// a - Append 
// p m n - Print range of lines from m to n 
// i n  - Insert line at position n
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

void insert(int pos)
{
 NODE *first1=NULL,*last1,*p,*q;
 int i=0;
 char buff[80];

 printf("Enter text to insert (type END to stop):");
 
 fflush(stdin);
 fgets(buff,80,stdin);

 while(strcmp(buff,"END\n")!=0)
 {
  p = get_node(buff);
  if(first1==NULL)
   first1=p;
  else
   last1->next=p;
  last1=p;
  i++;
  
  fflush(stdin);
  fgets(buff,80,stdin);
 }
 len+=i;
 p = q = first;
 i=1;
 while(i<pos)
 {
  i++;
  q=p;
  p=p->next;
 }

 if(p==first)
 {
  last1->next=first;
  first=first1;
 }
 else
 {
  q->next=first1;
  last1->next=p;
 }

 changed=1;
}

void print(int n1, int n2)
{
 int i;
 NODE *p;

 i=1;
 p=first;
 while(i<n1)
 {
  i++;
  p=p->next;
 }

 i=n1;
 while(i<=n2)
 {
  printf("%d: %s",i,p->line);
  i++;
  p=p->next;
 }
}
  
int main(int argc, char *argv[])
{
 char buff[80],ch,fname[30]="";
 int n1,n2;

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

  sscanf(buff,"%c %d %d",&ch,&n1,&n2);

  switch(ch)
  {
  case 'a':
   append();
   break;
  case 'p':
   if(n1>=1 && n2<=len && n1<=n2)
    print(n1,n2);
   else
    printf("Invalid parameter\n");
   break;
  case 'i':
   if(n1>=1 && n1<=len)
    insert(n1);
   else
    printf("Invalid parameter\n");
   break;
  case 'e':
   exit(0);
  default:
   printf("Invalid command.\n");
  }
 }

 return 0;
}