#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>

void	print_us(struct timeval start, struct timeval end)
{
	long long	diff;

	diff = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
	printf("diff: %lld\n", diff);
}

int	main(void)
{
	struct timeval	start;
	struct timeval	end;

	// sleep 시스템콜 딜레이
	gettimeofday(&start, NULL);
	sleep(1);
	gettimeofday(&end, NULL);
	print_us(start, end);

	// write 시스템콜 딜레이
	gettimeofday(&start, NULL);
	write(1, "hello\n", 6);
	gettimeofday(&end, NULL);
	print_us(start, end);

	return (0);
}
