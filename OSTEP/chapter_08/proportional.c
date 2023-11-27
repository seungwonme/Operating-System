#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct node
{
	int ticket;
	struct node *next;
} node_t;

const int totalTickets = 1000;

int	main(void)
{
	node_t *head = NULL;
	srand(time(NULL));

	// 당첨자를 발견했는지 추적하는 데 사용됨
	int counter = 0;

	// 0부터 총 추첨권의 수 사이의 임의의 값을 얻기 위해
	// 난수 발생기를 호출함
	int winner = rand() % totalTickets;

	// 작업 목록을 탐색하는 데 사용
	node_t *current = head;

	// 티켓 값 > winner를 만족할 때까지 반복
	while (current)
	{
		counter = counter + current->ticket;
		if (counter > winner)
			break; // 당첨자 발견
		current = current->next;
	}
	// current는 당첨자를 가리킴: 당첨자가 실행될 수 있도록 준비
	return (0);
}
