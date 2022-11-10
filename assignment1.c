#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <string.h>

int main(void){

	void sigint_handler(int sig);
	if(signal(SIGINT, sigint_handler)== SIG_ERR){
		perror("SIGINT ERROR");
		exit(1);
	}

	int pipefds1[2];
	int pipefds2[2];

	char bio[] = "\nThis is my bio";
	char input[100];
	pid_t p;

	printf("Please enter your name: ");
	if(pipe(pipefds1) == -1){
		perror("Pipe failed");
		return (1);
	}

	if(pipe(pipefds2) == -1){
		perror("Pipe failed");
		return (1);
	}

	scanf("%s", bio);
	p =fork();

	if(p < 0){
		perror("Fork failed");
		return (1);
	}

	else if (p > 0){
		char concat_str[100];
		close(pipefds1[0]);
		write(pipefds1[1], bio, strlen(bio) +1);
		close(pipefds1[1]);
		wait(NULL);
		close(pipefds2[1]);
		read(pipefds2[0],concat_str, 100);
		printf("Your name is %s\n", concat_str);
		close(pipefds2[0]);
	}

	else{
		close(pipefds1[1]);
		char concat_str[100];
		read(pipefds1[0], concat_str, 100);
		int k = strlen(concat_str);
		int i;
		for(i  = 0; i < strlen(bio); i++)
			concat_str[k++] = bio[i];
		concat_str[k] = '\0';

		close(pipefds1[0]);
		close(pipefds2[0]);

		write(pipefds2[1], concat_str, strlen(concat_str) +1);
		close(pipefds2[1]);
	exit(0);
	}

}

void sigint_handler(int sig){
	printf("You just terminate the program using the SIGINT command");
}

