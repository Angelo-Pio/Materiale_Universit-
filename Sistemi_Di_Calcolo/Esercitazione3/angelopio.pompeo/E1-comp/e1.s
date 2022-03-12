.globl comp 

comp:

	movl 4(%esp),%ecx
	movl 8(%esp),%edx

	subl %edx,%ecx
	movl %ecx,%eax
	
	ret

	