#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

void wait2(int pd[])
{
  int s;
  read(pd[0],&s,sizeof(int));
}

void signal2(int pd[])
{
  int s=1;
  write(pd[1],&s,sizeof(int));
  return;
}

void crit(int *i, int pd[]){
  wait2(pd);
 for (int j=1; j<=5; j++){
 sleep(1);
 printf("Child%d executes a critical section\n",*i);
 }
  signal2(pd);
}

void non_crit(int *i){
 for (int j=1; j<=7; j++){
 sleep(1);
 printf("Child%d executes a non_critical section\n",*i);
 }
}
   
int main() 
{ 
    int pid, pid1, pid2,pd[2], i; 
    pipe(pd);
    pid = fork(); 
    if(pid>0){
    signal2(pd);
    }
    if (pid == 0) { 
    i=1; 
    crit(&i,pd);
    non_crit(&i); 
    non_crit(&i);
    crit(&i,pd);;
    non_crit(&i);
    crit(&i,pd);
    } 
    else if (pid<0) 
    {
      printf ( "error");
    }
    else { 
        pid1 = fork(); 
        if (pid1 == 0) { 
            i=2; 
            non_crit(&i);
            crit(&i,pd);
            non_crit(&i);
            crit(&i,pd);
            non_crit(&i);
            crit(&i,pd);
        } 
        else if (pid1<0) 
	{
            printf ( "error");
	}
        else { 
            pid2 = fork(); 
            if (pid2 == 0) {
                i=3;
                crit(&i,pd);
                non_crit(&i);
                crit(&i,pd);
                non_crit(&i);
                crit(&i,pd);
                non_crit(&i);
            } 
            else if (pid2<0) 
	    {
                printf ( "error");
	    } 
        } 
    } 
  
    return 0; 
} 
