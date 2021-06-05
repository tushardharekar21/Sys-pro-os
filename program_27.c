//Q) Write a program to implement a toy shell (Command Interpreter). It has its own prompt say “MyShell $”.
//  Any normal shell command is executed from this shell (MyShell$) by starting a child process to execute the
//   system program corresponding to the command. It should additionally interpret the following commands: 
// count c filename :- To print number of characters in the file.
// count w filename  :- To print number of words in the file. 
// count 1 filename :- To print number of lines in the file

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void make_toks(char *s, char *tok[])
{
 int i=0;
 char *p;

 p = strtok(s," ");
 while(p!=NULL)
 {
  tok[i++]=p;
  p=strtok(NULL," ");
 }

 tok[i]=NULL;
}

void count(char *fn, char op)
{
 int fh,cc=0,wc=0,lc=0;
 char c;

 fh = open(fn,O_RDONLY);
 if(fh==-1)
 {
  printf("File %s not found.\n",fn);
  return;
 }

 while(read(fh,&c,1)>0)
 {
  if(c==' ') wc++;
  else if(c=='\n')
  {
   wc++;
   lc++;
  }
  cc++;
 }

 close(fh);

 switch(op)
 {
 case 'c':
  printf("No.of characters:%d\n",cc);
  break;
 case 'w':
  printf("No.of words:%d\n",wc);
  break;
 case 'l':
  printf("No.of lines:%d\n",lc);
  break;
 }
}

int main()
{
 char buff[80],*args[10];
 int pid;

 while(1)
 {
  printf("myshell$");
  fflush(stdin);
  fgets(buff,80,stdin);
  buff[strlen(buff)-1]='\0';
  make_toks(buff,args);
  if(strcmp(args[0],"count")==0)
   count(args[2],args[1][0]);
  else
  {
   pid = fork();
   if(pid>0)
    wait();
   else
   {
    if(execvp(args[0],args)==-1)
     printf("Bad command.\n");
   }
  }
 }

 return 0;
}
 