#include <stdio.h>
#include <unistd.h>
int main()
{
	pid_t pid1, pid2, pid3;
	printf ("Prima del fork().\n");
	
	pid1 = fork();
	pid2 = fork();
	pid3 = fork();

	printf("Dopo del fork().\n");
	
	if(pid1==0 || pid2==0 || pid3==0)
		printf("sono il processo figlio con pid %d. mio padre ha pid%d.\n", getpid(), getppid());
	else
		printf("Sono il processo padre con pid %d. \n", getpid());
	return 0;
}
