#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <assert.h>
#include <sys/wait.h>
#include <sys/types.h>

int i,ID[10],IDnew[10],check,j;

void child()
{
	int count=1;
	raise(SIGSTOP); //stop pid until a signal is given from allarm_handler
	i+=1;
	while(1){
		printf("Child%d %d is executed goneas(%d) (%d) \n",i,getpid(),getppid(),count);
		count+=1;
		sleep(1);
		}
}	

void alarm_handler (int sig)
{
	kill(IDnew[i],SIGSTOP); //stops the pid of the i-nth argument
	
	if(i==j-2) //if our i-nth argument is the last
	{ 
		i=0; //it goes again to the first argument
		check+=1; //raises the counter, that indicates the number of pid
		if(check==4) //if counter5 then stops every pid and output->"terminated"
		{
			for(i=0; i<j-1; i++)
			{
				kill(IDnew[i],SIGTERM);
			}
			printf("terminated\n");
			exit(0); //Exits every pid
		}
		alarm(3);
		kill(IDnew[i],SIGCONT); //gives signal to go to the next argument
	}
	else //in other case it goes to the argument-pid
	{
		i+=1;
		alarm(3);
		kill(IDnew[i],SIGCONT); //And it commands to keep going
	}
}
	
	
	

int main(int argc ,char **argv)
{
	pid_t pid;
	
	int num[10];
	signal(SIGALRM,alarm_handler);
	
	for(i=0; i<argc-1; i++)
	{
		num[i]=atoi(argv[i+1]);

	} 
	for(i=0; i<argc-1; i++)
	{
		
		pid=fork();
		if(pid<0)
		{
		    perror("fork");
		    exit(1);
		}
		if(pid==0)
		{
			child();
		}
		else
		{	
			ID[i]=pid;
			
		}
	}
	for(i=0; i<argc-1; i++)
	{
		
		IDnew[i]=ID[(num[i]-1)]; //mas dinei to orisma pou plhktrologhse o xrhsths

	}        
	sleep(3);
	j=argc; //o j sou dinei ton arithmo twn orismatwn
	check=0;
	i=0;
	alarm(3);   //The alarm() function sets a timer that generates the SIGALARM signal. If we ignore or don’t catch this signal, the process is terminated.
	kill(IDnew[0],SIGCONT);
	

	while(pause());
	
	return 0;
}




		


	

