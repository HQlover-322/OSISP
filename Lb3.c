#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>

void DO(char name[10]){

		int N,Pid,Tm,Ts;
		time_t T = time(NULL);
		struct tm tm = *localtime(&T);
		for(int i =1;i<=3;i++)
    {
			do
      {
				FILE* f=fopen("text.txt","r");
				fscanf(f,"%d %d %d %d",&N,&Pid,&Tm,&Ts);
				fclose(f);
			}
      while(N!=i);
			printf("%s: %d %d %d %d %d %d\n",name, N,getpid(),Tm,Ts,tm.tm_min,tm.tm_sec );

		}

}

int main(int argc, char **argv)
{
	pid_t pid;
	if((pid=fork())==0){
		DO("CHILD1");
		printf("CHILD1 %d\n",getpid());
	}else if(pid!=-1){
			if((pid=fork())==0){
				DO("CHILD2");
				printf("CHILD2 %d\n",getpid());
			}else if(pid!=-1){
				if((pid=fork())==0){
					DO("CHILD3");
					printf("CHILD3 %d\n",getpid());
				}else if(pid!=-1){
						if((pid=fork())==0){
							DO("CHILD4");
							printf("CHILD4 %d\n",getpid());
						}else if(pid!=-1){
							char ch[100]="";
							for(int i=1;i<=3;i++){
								sleep(0.1);
								FILE* f=fopen("text.txt","w");
								time_t T = time(NULL);
								struct tm tm = *localtime(&T);
								sprintf(ch,"%d %d %d %d\n",i,pid,tm.tm_min,tm.tm_sec);
								fprintf(f,"%s",ch);
								printf("PARENT %s",ch);
								fclose(f);
							}
							printf("PARENT %d\n",pid);


						}
				}
			}
	}

	return 0;
}
