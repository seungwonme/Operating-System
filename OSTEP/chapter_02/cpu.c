// ./cpu A & ; ./cpu B & ; ./cpu C & ; ./cpu D &
// 프로세서가 하나임에도 4개의 프로그램이 동시에 실행되는 것처럼 보인다.

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>
#include <unistd.h>

int	main(int argc , char *argv[])
{
	if(argc!=2)
	{
		fprintf(stderr,"usage: cpu <string>\n");
		exit(1);
	}
	char *str = argv[1];
	while (1)
	{
		sleep(1);
		printf("%s\n", str);
	}
	return 0;
}
