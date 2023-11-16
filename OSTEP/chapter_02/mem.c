#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	int *p = malloc(sizeof(int)); // a1 assert(p != NULL);
	printf("(%d) memory address of p: 0x%08x\n", getpid(), (unsigned) p); // a2 *p = 0; // a3
	while (1)
	{
		sleep(1);
		*p = *p + 1;
		printf("(%d) p : %d\n", getpid(), *p); // a4 }
	}
	return (0);
}
