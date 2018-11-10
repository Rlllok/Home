	.file	"splab2.cpp"
	.text
	.globl	A
	.bss
	.align 32
	.type	A, @object
	.size	A, 44
A:
	.zero	44
	.section	.rodata
.LC0:
	.string	"%d "
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$2, -8(%rbp)
	movl	$0, -4(%rbp)
	movb	$0, -9(%rbp)
.L10:
	cmpb	$10, -9(%rbp)
	jg	.L2
	movsbl	-9(%rbp), %eax
	movl	%eax, -4(%rbp)
	addl	$8, -8(%rbp)
	addl	$1, -4(%rbp)
	movsbl	-9(%rbp), %eax
	cmpl	$3, %eax
	je	.L4
	cmpl	$3, %eax
	jg	.L5
	cmpl	$1, %eax
	je	.L6
	jmp	.L3
.L5:
	cmpl	$5, %eax
	je	.L7
	cmpl	$6, %eax
	je	.L8
	jmp	.L3
.L6:
	movl	$0, -4(%rbp)
	jmp	.L9
.L4:
	addl	$1, -4(%rbp)
	jmp	.L9
.L7:
	subl	$1, -4(%rbp)
	jmp	.L9
.L8:
	movl	-8(%rbp), %eax
	addl	%eax, %eax
	subl	-4(%rbp), %eax
	movl	%eax, -4(%rbp)
	jmp	.L9
.L3:
	subl	$1, -4(%rbp)
.L9:
	movsbl	-9(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rcx
	leaq	A(%rip), %rax
	movl	-4(%rbp), %edx
	movl	%edx, (%rcx,%rax)
	movzbl	-9(%rbp), %eax
	addl	$1, %eax
	movb	%al, -9(%rbp)
	jmp	.L10
.L2:
	movb	$0, -9(%rbp)
.L12:
	cmpb	$10, -9(%rbp)
	jg	.L11
	movsbl	-9(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	A(%rip), %rax
	movl	(%rdx,%rax), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movzbl	-9(%rbp), %eax
	addl	$1, %eax
	movb	%al, -9(%rbp)
	jmp	.L12
.L11:
	movl	$10, %edi
	call	putchar@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
