//Q) Write a command line program for line editor. The file to be edited is taken as command line argument; an empty file is opened for editing if no argument is supplied. It should display a „$‟ prompt to accept the line editing commands. Implement the following commands.
// s - Save
// a - Append
// m n1 n2 -  Copy line from position n1 to n2
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

void copy(int n1, int n2)
{
 NODE *p,*q,*t;
 int i;

 i=1;
 p=first;
 while(i<n1)
 {
  i++;
  p=p->next;
 }

 t = get_node(p->line);

 i=1;
 p=q=first;
 while(i<n2)
 {
  i++;
  q=p;
  p=p->next;
 }
 
 if(p==first)
 {
  t->next=first;
  first=t;
 }
 else
 {
  q->next=t;
  t->next=p;
 }

 len++;
 changed=1;
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

void save(char fname[])
{
 FILE *fp;
 NODE *p;

 fp = fopen(fname,"w");

 p = first;
 while(p!=NULL)
 {
  fputs(p->line,fp);
  p=p->next;
 }

 fclose(fp);
 changed=0;
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
  case 'm':
   if(n1>=1 && n1<=len && n2>=1 && n2<=len)
   {
    copy(n1,n2);
    if(n1<=n2)
     del(n1);
    else
     del(n1+1);
   }
   else
    printf("Invalid parameter\n");
   break;
  case 's':
   if(changed==1)
   {
    if(strlen(fname)==0)
    {
     printf("Enter source file name:");
     fflush(stdin);
     fgets(fname,30,stdin);
     fname[strlen(fname)-1]='\0';
    }
    save(fname);
   }
   break;
  case 'e':
   if(changed==1)
   {
    printf("Quit without save (Y/N)?");
    fflush(stdin);
    fgets(buff,80,stdin);
    if(buff[0]=='N')
    {
     if(strlen(fname)==0)
     {
      printf("Enter file name:");
      fflush(stdin);
      fgets(fname,30,stdin);
      fname[strlen(fname)-1]='\0';
     }
     save(fname);
    }
   }
   exit(0);
  default:
   printf("Invalid command.\n");
  }
 }

 return 0;
}
