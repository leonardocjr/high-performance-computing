// create-many-processes.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NUMPROCS 20000

int main()
{
 pid_t pid;

 for (int i=0; i<NUMPROCS; i++) {
   pid=fork();
   if (pid==0) { exit(0); }
   else if (pid==-1) {
     printf("Failed on the creation of process i=%d\n",i);
     perror("fork"); exit(errno);
   }
 }
	
 while(wait(NULL)!=-1);
 return(0);
}
