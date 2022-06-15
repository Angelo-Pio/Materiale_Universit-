.globl comp 

comp:

	movl 4(%esp),%eax
	movl 8(%esp),%edx
	
	movl (%eax),%eax
	movl (%edx),%edx

	subl %edx,%eax

	ret
	