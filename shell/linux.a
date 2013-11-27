	.file	"linux.c"
	.globl	SNACKCMD
	.section	.rodata
.LC0:
	.string	"garfield-snacks"
	.data
	.align 8
	.type	SNACKCMD, @object
	.size	SNACKCMD, 8
SNACKCMD:
	.quad	.LC0
	.section	.rodata
.LC1:
	.string	"--user"
.LC2:
	.string	"pid: %d"
	.text
	.globl	execBuyCmd
	.type	execBuyCmd, @function
execBuyCmd:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movl	%edx, -52(%rbp)
	movq	$.LC1, -8(%rbp)
	movq	$.LC1, -16(%rbp)
	movq	SNACKCMD(%rip), %rsi
	movq	SNACKCMD(%rip), %rax
	movq	-48(%rbp), %r9
	movq	-8(%rbp), %r8
	movq	-40(%rbp), %rcx
	movq	-16(%rbp), %rdx
	movq	$0, 8(%rsp)
	movl	-52(%rbp), %edi
	movl	%edi, (%rsp)
	movq	%rax, %rdi
	movl	$0, %eax
	call	execl
	movl	%eax, -20(%rbp)
	movl	-20(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	execBuyCmd, .-execBuyCmd
	.ident	"GCC: (GNU) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
