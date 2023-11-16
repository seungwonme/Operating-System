#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int	main(void)
{
	int	pid;
	char *myargs[3];

	pid = fork();
	if (pid < 0) // fork 실패함; exit
	{
		fprintf(stderr, "fork failed\n");
		exit(1);
	}
	else if (pid == 0) // 자식 프로세스
	{
		close(STDOUT_FILENO);
		open("./p4.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
		myargs[0] = strdup("wc"); // 프로그램: "wc"
		myargs[1] = strdup("p4.c"); // 인자: 단어 셀 파일
		myargs[2] = NULL;            // 배열의 끝 표시
		execvp(myargs[0], myargs);   // wc 실행
		printf("this shouldn't print out");
	}
	else // 부모 프로세스
		wait(NULL);
	return (0);
}
