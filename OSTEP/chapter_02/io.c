/* 이 system call(open, write, close)은 운영체제에서 file system이라 불리는 부분으로 전달된다.
file system은 요청을 처리하고 경우에 따라 사용자에게 에러 코드를 반환한다. */

#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/types.h>

int	main(void)
{
	int fd = open("/tmp/file", O_WRONLY | O_CREAT | O_TRUNC , S_IRWXU); // O_WRONLY : Write Only, O_CREAT : Create, O_TRUNC : Truncate, S_IRWXU : Read, Write, Execute by User
	assert(fd > -1); // assert는 C 프로그래밍 언어에서 사용되는 디버깅 도구로, 주어진 조건이 false로 평가될 경우 프로그램 실행을 중단시키는 역할을 한다.
	int rc = write(fd, "hello world\n", 13);
	assert(rc == 13);
	close(fd);
	return 0;
}
