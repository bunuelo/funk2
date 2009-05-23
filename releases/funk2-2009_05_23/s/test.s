	.file	"test.c"
	.text
.globl execute_bytecodes
	.type	execute_bytecodes, @function
execute_bytecodes:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	8(%ebp), %eax
	movl	%eax, -8(%ebp)
	movl	12(%ebp), %eax
	movl	%eax, -4(%ebp)
	movl	position_independent_function, %eax
	call	*%eax
	movl	-8(%ebp), %eax
	movl	-4(%ebp), %edx
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	bytecode__thread
	movl	$-1985229329, 8(%esp)
	movl	$19088743, 12(%esp)
	movl	-8(%ebp), %eax
	movl	-4(%ebp), %edx
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	bytecode__thread_arg0
	movl	$1737075661, 16(%esp)
	movl	$-285138107, 20(%esp)
	movl	$2023406814, 8(%esp)
	movl	$-267242410, 12(%esp)
	movl	-8(%ebp), %eax
	movl	-4(%ebp), %edx
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	bytecode__thread_arg0_arg1
	leave
	ret
	.size	execute_bytecodes, .-execute_bytecodes
.globl test_thread_func
	.type	test_thread_func, @function
test_thread_func:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	8(%ebp), %eax
	movl	%eax, -8(%ebp)
	movl	12(%ebp), %eax
	movl	%eax, -4(%ebp)
	movl	-8(%ebp), %eax
	leave
	ret
	.size	test_thread_func, .-test_thread_func
.globl return_if_not_eq
	.type	return_if_not_eq, @function
return_if_not_eq:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	8(%ebp), %eax
	movl	%eax, -8(%ebp)
	movl	12(%ebp), %eax
	movl	%eax, -4(%ebp)
	movl	-8(%ebp), %eax
	movl	-4(%ebp), %edx
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	test_thread_func
	testl	%eax, %eax
	je	.L9
	movl	$2, -8(%ebp)
	movl	$0, -4(%ebp)
.L9:
	leave
	ret
	.size	return_if_not_eq, .-return_if_not_eq
.globl main
	.type	main, @function
main:
	leal	4(%esp), %ecx
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ecx
	movl	$0, %eax
	popl	%ecx
	popl	%ebp
	leal	-4(%ecx), %esp
	ret
	.size	main, .-main
	.comm	counter,8,8
	.comm	position_independent_function,4,4
	.ident	"GCC: (GNU) 4.1.2 (Ubuntu 4.1.2-0ubuntu4)"
	.section	.note.GNU-stack,"",@progbits
