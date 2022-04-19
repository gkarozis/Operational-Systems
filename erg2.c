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
	raise(SIGSTOP); //stamata thn diergasia mexris otou na dothei kapoio allo shma apo thn allarm_handler
	i+=1;
	while(1){
		printf("Child%d %d is executed goneas(%d) (%d) \n",i,getpid(),getppid(),count);
		count+=1;
		sleep(1);
		}
}	

void alarm_handler (int sig)
{
	kill(IDnew[i],SIGSTOP); //sou stamataei thn diergasia tou i-ostou orismatos
	
	if(i==j-2) //ean to i-osto orisma mas einai to teleutaio
	{ 
		i=0; //paei ksana sto prwto orisma
		check+=1; //auksanei se poia ektelesh ths diergasias briskomaste
		if(check==4) //ean prokeitai gia thn 4+1=5h tote stamata oles tis diergasies kai tupwnei terminated
		{
			for(i=0; i<j-1; i++)
			{
				kill(IDnew[i],SIGTERM);
			}
			printf("terminated\n");
			exit(0); //bgainei apo oles tis diergasies
		}
		alarm(3);
		kill(IDnew[i],SIGCONT); //tou dinei shmashma na paei sto epomeno orisma
	}
	else //se allh periptwsh phgainei sto epomeno orisma-diergasia
	{
		i+=1;
		alarm(3);
		kill(IDnew[i],SIGCONT); //kai tou leei na sunexisei
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




		


	

