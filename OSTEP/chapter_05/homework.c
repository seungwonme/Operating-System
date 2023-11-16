#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// 별도의 주소 공간을 가지기 때문에 자식 프로세스에서 x의 값이 바뀌어도 부모 프로세스의 x의 값은 바뀌지 않는다.
void	prob1(void)
{
	int pid;
	int x;

	x = 100;
	pid = fork();
	if (pid < 0)
	{
		fprintf(stderr, "fork failed\n");
		exit(1);
	}
	else if (pid == 0)
	{
		printf("value of x in child: %d\n", x);
		x = 200;
		printf("value of x in child: %d\n", x);
	}
	else
	{
		printf("value of x in parent: %d\n", x);
		x = 300;
		printf("value of x in parent: %d\n", x);
	}
}

// 부모 프로세스의 fd를 자식 프로세스가 상속받기 때문에 접근이 가능하다.
void	prob2()
{
	int pid;
	int fd;

	fd = open("./prob2.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	pid = fork();
	if (pid < 0)
	{
		fprintf(stderr, "fork failed\n");
		exit(1);
	}
	else if (pid == 0)
		write(fd, "child\n", 6);
	else
		write(fd, "parent\n", 7);
}

// 비결정성으로 인해 어느 프로세스가 먼저 실행된다고 단정하기 어렵다.
void	prob3()
{
	int pid;

	pid = fork();
	if (pid < 0)
	{
		fprintf(stderr, "fork failed\n");
		exit(1);
	}
	else if (pid == 0)
		printf("hello\n");
	else
	{
		wait(NULL); // wait 없이 항상은 불가능하다(sleep, busy waiting 등으로 대체 가능하지만 보장되지 않는다).
		printf("goodbye\n");
	}
}

// 여러 함수가 존재하는 이유는 프로그램을 새로운 프로세스로 대체할 때 필요한 인수를 다르게 전달하고자 하는 유연성 때문
void	prob4()
{
	int pid;

	pid = fork();
	if (pid < 0)
	{
		fprintf(stderr, "fork failed\n");
		exit(1);
	}
	else if (pid == 0)
	{
		execve("/bin/ls", (char*[]){"/bin/ls", NULL}, NULL);
		fprintf(stderr, "execve failed\n");
	}
	else
		wait(NULL);
}

// wait은 자식 프로세스의 pid를 반환한다.
void	prob5(void)
{
	int pid;
	int res;

	pid = fork();
	if (pid < 0)
	{
		fprintf(stderr, "fork failed\n");
		exit(1);
	}
	else if (pid == 0)
		printf("child pid: %d\n", getpid());
	else
	{
		res = wait(NULL);
		// res = wait(NULL); // 자식 프로세스가 없기 때문에 -1을 반환한다.
		printf("res: %d\n", res);
	}
}

// waitpid는 특정 pid를 기다릴 때 사용한다.
void	prob6(void)
{
	int pid;
	int res;

	pid = fork();
	if (pid < 0)
	{
		fprintf(stderr, "fork failed\n");
		exit(1);
	}
	else if (pid == 0)
		printf("child pid: %d\n", getpid());
	else
	{
		res = waitpid(pid, NULL, 0);
		// res = wait(NULL); // 자식 프로세스가 없기 때문에 -1을 반환한다.
		printf("res: %d\n", res);
	}
}

// STDOUT_FILENO을 닫으면 출력되지 않는다.
void	prob7(void)
{
	int pid;

	pid = fork();
	if (pid < 0)
	{
		fprintf(stderr, "fork failed\n");
		exit(1);
	}
	else if (pid == 0)
	{
		close(STDOUT_FILENO);
		printf("after close\n");
	}
}

void	prob8(void)
{
	int pid;
	int fd[2];

	pipe(fd);
	pid = fork();
	if (pid < 0)
	{
		fprintf(stderr, "fork failed\n");
		exit(1);
	}
	else if (pid == 0)
	{
		close(fd[0]);
		write(fd[1], "hello\n", 6);
	}
	pid = fork();
	if (pid < 0)
	{
		fprintf(stderr, "fork failed\n");
		exit(1);
	}
	else if (pid == 0)
	{
		char buf[10];
		close(fd[1]);
		read(fd[0], buf, 6);
		write(STDOUT_FILENO, buf, strlen(buf));
	}
}

int	main(void)
{
	// prob1();
	// prob2();
	// prob3();
	// prob4();
	// prob5();
	// prob6();
	// prob7();
	prob8();
	return (0);
}
