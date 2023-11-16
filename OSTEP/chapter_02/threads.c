/* ./thread 100000

예상하지 못한 결과의 원인은 명령어가 한 번에 하나씩만 실행된다는 것과 관련 있다.
앞 프로그램의 핵심 부분인 counter를 증가시키는 부분은 세 개의 명령어로 이루어진다.

1. counter 값을 메모리에서 레지스터로 탑재하는 명령어 하나
2. 레지스터를 1 증가시키는 명령어 하나
3. 레지스터의 값을 다시 메모리에 저장하는 명령어 하나

이렇게 3개의 명령어로 구성된다.
이 세 개의 명령어가 원자적(atomically)으로(한 번에 3개 모두) 실행되지 않기 때문에 이상한 일이 발생할 수 있다. */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

volatile int counter = 0;
int loops;

void *worker(void *arg)
{
	int i;
	for (i = 0; i < loops; i++)
		counter++;
	return NULL;
}

int	main(int argc , char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr,"usage: threads <value>\n");
		exit(1);
	}

	loops = atoi(argv[1]);
	pthread_t p1 , p2;

	printf("Initial value : %d\n", counter);

	pthread_create(&p1 ,NULL ,worker ,NULL);
	pthread_create(&p2 ,NULL ,worker ,NULL);

	pthread_join(p1 ,NULL);
	pthread_join(p2 ,NULL);
	printf("Final value : %d\n", counter);
	return 0;
}
