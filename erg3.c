#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>



int main(int argc, char **argv) 
{
        int i,num[2],pd[2],a[10][2];
        int f=1;
        int count=1;
        pid_t pid;
        for(i=0; i<argc-1; i++)
	{
		num[i]=atoi(argv[i+1]);

	} 
        int n1=num[0];
        //printf("1 %d",num[0]);
        for(i=0; i<=num[0]; i++){
                pipe(pd); //i have as much pipes as my pids(fathers is counted in)
                a[i][0]=pd[0];
                a[i][1]=pd[1];
        }
	for(i=0; i<num[0]; i++)
	{
                pid=fork();	
	        if(pid==-1){
                    perror("fork");
                }
                else if(pid>0){
                    close(a[0][0]);
                    write(a[0][1],&f,sizeof(int));
                    write(a[0][1],&count,sizeof(int));
                    close(a[0][1]);
                }
                else{
                    if(i==0){
                      close(a[0][1]);
                      read(a[0][0],&f, sizeof(int));
                      read(a[0][0],&count, sizeof(int));
                      printf("Received number f=%d at process %d from parent %d\n", f, getpid(),getppid());
                      f=f*count;
                      count=count+1;
                      printf("f=%d\n",f);
                      close(a[1][0]);
                      write(a[1][1],&f,sizeof(int)); 
                      write(a[1][1],&count,sizeof(int));
                      while(1){
                        close(a[n1][1]);
                        read(a[n1][0],&f, sizeof(int));
                        read(a[n1][0],&count, sizeof(int));
                        printf("Received number f=%d at process %d from parent %d\n", f, getpid(),getppid());
                        f=f*count;
                        count=count+1;
                        printf("f=%d\n",f);
                        if (count>num[1]){ exit(0);}
                        close(a[1][0]);
                        write(a[1][1],&f,sizeof(int));
                        write(a[1][1],&count,sizeof(int));
                      }
                    }   
                    else{
                      while(1){
                        close(a[i][1]);
                        read(a[i][0],&f, sizeof(int));
                        read(a[i][0],&count, sizeof(int));
                        printf("Received number f=%d at process %d from parent %d\n", f, getpid(),getppid());
                        f=f*count;
                        count++;
                        printf("f=%d\n",f);
                        if (count>num[1]){ exit(0);}
                        close(a[i+1][0]);
                        write(a[i+1][1],&f,sizeof(int)); 
                        write(a[i+1][1],&count,sizeof(int)); 
                      }
                    }              
                }   
        } 
	return 0;
} 

//with sigterm terminates
