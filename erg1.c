#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
int main(){ 
	int child[4],i,status;
	child[0]=fork();
	if (child[0]<0) 
	{
		printf ( "error");
	}
	if (child[0]==0)
	{
		child[1]=fork();
		if (child[1]<0) 
	{
		printf ( "error");
	}
		if (child[1]==0)
		{
			printf("Process %d is executed,my father is %d\n",getpid(),getppid());
			sleep(1);
			
		exit(0);
		}
		child[2]=fork();
		if (child[2]<0) 
	{
		printf ( "error");
	}
		if (child[2]==0)
		{
			printf("Process %d is executed,my father is %d\n",getpid(),getppid());
			sleep(1);
		exit(0);
		}
			printf("Process %d is executed,my father is %d\n",getpid(),getppid());
			sleep(1);
		wait(&status);
		exit(0);
	}
	child[3]=fork();
	if (child[3]<0) 
	{
		printf ( "error");
	}
	if (child[3]==0)
	{
		child[4]=fork();
		if (child[4]<0) 
	{
		printf ( "error");
	}
		if (child[4]==0)
		{
			
			printf("Process %d is executed,my father is %d\n",getpid(),getppid());
			sleep(1);
		exit(0);
		}
			printf("Process %d is executed,my father is %d\n",getpid(),getppid());
			sleep(1);
		wait(&status);
		exit(0);
	}
	wait(&status);
return 0;
}
