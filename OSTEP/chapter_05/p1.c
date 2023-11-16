#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	int	pid;

	printf("hello world (pid:%d)\n", (int)getpid());
	pid = fork();
	if (pid < 0) // fork 실패 종료
	{
		fprintf(stderr, "fork failed\n");
		exit(1);
	}
	else if (pid == 0) // 자식 프로세스
		printf("hello, I am child (pid:%d)\n", (int)getpid());
	else // 부모 프로세스
		printf("hello, I am parent of %d (pid:%d)\n", pid, (int)getpid());
	return (0);
}
