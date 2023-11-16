// 프로세스를 중단하고 이후에 재개하기 위해
// xv6가 저장하고 복원하는 레지스터

#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

struct context
{
	int eip;
	int esp;
	int ebx;
	int ecx;
	int edx;
	int esi;
	int edi;
	int ebp;
};

// 가능한 프로세스 상태
enum proc_state
{
	UNUSED,
	EMBRYO,
	SLEEPING,
	RUNNABLE,
	RUNNING,
	ZOMBIE
};

// 레지스터 문맥과 상태를 포함하여
// 각 프로세스에 대하여 xv6가 추적하는 정보

struct proc
{
	char *mem;									// 프로세스 메모리 시작 주소
	uint sz;										// 프로세스 메모리 크기
	char *kstack;								// 이 프로세스의 커널 스택의 바닥 주소
	enum proc_state state;			// 프로세스 상태
	int pid;										// 프로세스 ID
	struct proc *parent;				// 부모 프로세스
	void *chan;									// 0이 아니면, chan에서 수면
	int killed;									// 0이 아니면 종료됨
	struct file *ofile[NOFILE]; // 열린 파일
	struct inode *cwd;					// 현재 디렉토리
	struct context context;			// 프로세스를 실행시키려면 여기로 교환
	struct trapframe *tf;				// 현재 인터럽트에 해당하는 트랩 프레임
};
