#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>



/**
 * main - Control will enter this program from here
 * 
 */

int main(int argc, char* argv[], char** env)
{
	char *prompt = "dohardthings$ ";
	char *bufflptr=NULL;
	ssize_t bufferSize=0;
	ssize_t gtlninput;
	pid_t pid=fork();
	pid_t result;

	while(1)
	{
		//Prompt to take input
		write(STDOUT_FILENO,prompt,14);


		//Getiing input from standard input
		gtlninput=getline(&bufflptr,&bufferSize,stdin);
		if(gtlninput == -1)
		{
		perror("Error (Getline failed)");
		free(bufflptr);
		exit(EXIT_FAILURE);
		}
		
		
		//EOF condition
		if(gtlninput == 1)
		{
			break;
		}

		if(bufflptr[gtlninput-1]=='\n')
		{
			bufflptr[gtlninput-1]='\0';
		} //this is for me to handle the newline

		else
		{
			if(pid <0)
			{
				perror("the fork failed");
				free(bufflptr);
				exit(EXIT_FAILURE);
		
				char * argu[]={bufflptr,NULL};
				execve(bufflptr,argu, NULL);

				perror("execve failed");
				free(bufflptr);
				exit(EXIT_FAILURE);
			}
			else
			{
				int status;
				result=waitpid(pid,&status,0);
				if(result ==-1)
				{
					perror("waitpid failed");
				}
			}
		}
	}

	free(bufflptr);
	return (0);
}

