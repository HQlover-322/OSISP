
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char **argv)
{
	char com[20];
	do{
		scanf("%s",com);
		printf("%s: %d\n",com,strcmp(com,"exit"));
		pid_t pid=fork();
		if(pid==0){
				if(com[0]!='\n'){
					execvp(com,argv);}
				return 0;
		}else if(pid==-1){
				perror("Compl");
		}
	}while(strcmp(com,"exit"));
	return 0;
}

