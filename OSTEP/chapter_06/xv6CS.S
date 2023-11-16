# void switch(struct context **old, struct context *new);
#
# Save current register context in old
# and then load register context from new.
.globl switch
switch:
	# Save old registers
	movl 4(%esp) , %eax		# old포인터를 eax에 넣는다.
	popl 0(%eax)					# old IP를 저장한다.
	movl %esp, 4(%eax)		# 그리고 스택
	movl %ebx, 8(%eax)		# 그리고 다른 레지스터
	movl %ecx, 12(%eax)
	movl %edx, 16(%eax)
	movl %esi, 20(%eax)
	movl %edi, 24(%eax)
	movl %ebp, 28(%eax)

	# Load new registers
	movl 4(%esp) , %eax		# new포인터를 eax에 넣는다.
	movl 28(%eax) , %ebp	# 다른 레지스터를 복원한다.
	movl 24(%eax) , %edi
	movl 20(%eax) , %esi
	movl 16(%eax) , %edx
	movl 12(%eax) , %ecx
	movl 8(%eax) , %ebx
	movl 4(%eax) , %esp		# 스택은 이 지점에서 전환된다.
	pushl 0(%eax)					# 리턴 주소를 지정된 장소에 넣는다.
	ret										# 마지막으로 new문맥으로 리턴한다.
