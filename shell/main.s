	.file	"main.c"
	.globl	MAXLENGTH
	.section	.rodata
	.align 4
	.type	MAXLENGTH, @object
	.size	MAXLENGTH, 4
MAXLENGTH:
	.long	100
	.globl	MATE
	.align 4
	.type	MATE, @object
	.size	MATE, 4
MATE:
	.zero	4
	.globl	SNACKCMD
.LC0:
	.string	"garfield-snacks"
	.data
	.align 8
	.type	SNACKCMD, @object
	.size	SNACKCMD, 8
SNACKCMD:
	.quad	.LC0
	.comm	login,16,16
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
	movl	$100, %eax
	cltq
	movq	%rax, %rdi
	call	malloc
	movq	%rax, login(%rip)
	movl	$100, %eax
	cltq
	movq	%rax, %rdi
	call	malloc
	movq	%rax, login+8(%rip)
	cmpl	$0, -4(%rbp)
	jle	.L2
	movq	-16(%rbp), %rdx
	movl	-4(%rbp), %eax
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	parseArguments
.L2:
	movl	$0, %eax
	call	shell
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.section	.rodata
.LC1:
	.string	"Invalid arguments."
.LC2:
	.string	"u:p:h"
	.text
	.globl	parseArguments
	.type	parseArguments, @function
parseArguments:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$-1, -4(%rbp)
	movl	$0, opterr(%rip)
	jmp	.L5
.L13:
	movl	-4(%rbp), %eax
	cmpl	$104, %eax
	je	.L7
	cmpl	$104, %eax
	jg	.L8
	cmpl	$63, %eax
	je	.L9
	jmp	.L4
.L8:
	cmpl	$112, %eax
	je	.L10
	cmpl	$117, %eax
	je	.L11
	jmp	.L4
.L11:
	movq	optarg(%rip), %rax
	movq	%rax, %rdi
	call	setUser
	jmp	.L5
.L10:
	movq	optarg(%rip), %rax
	movq	%rax, %rdi
	call	setPassword
	jmp	.L5
.L7:
	movl	$0, %eax
	call	printHelp
	jmp	.L5
.L9:
	movl	$.LC1, %edi
	call	puts
	movl	$0, %eax
	call	printHelp
	nop
.L5:
	movq	-32(%rbp), %rcx
	movl	-20(%rbp), %eax
	movl	$.LC2, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	getopt
	movl	%eax, -4(%rbp)
	cmpl	$-1, -4(%rbp)
	jne	.L13
.L4:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	parseArguments, .-parseArguments
	.globl	printHelp
	.type	printHelp, @function
printHelp:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, %edi
	call	exit
	.cfi_endproc
.LFE4:
	.size	printHelp, .-printHelp
	.section	.rodata
.LC3:
	.string	"exit"
.LC4:
	.string	"%s>"
.LC5:
	.string	"set "
.LC6:
	.string	"list "
.LC7:
	.string	"search "
.LC8:
	.string	"mate "
.LC9:
	.string	"buy "
.LC10:
	.string	"help"
.LC11:
	.string	"Don't know what you mean..."
	.text
	.globl	shell
	.type	shell, @function
shell:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$72, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movq	%rsp, %rsi
	movq	%rsi, -104(%rbp)
	movl	$100, %esi
	movslq	%esi, %rsi
	subq	$1, %rsi
	movq	%rsi, -56(%rbp)
	movl	$100, %esi
	movslq	%esi, %rsi
	movq	%rsi, %rcx
	movl	$0, %ebx
	movl	$100, %ecx
	movslq	%ecx, %rcx
	movq	%rcx, %rax
	movl	$0, %edx
	movl	$100, %eax
	cltq
	movl	$16, %edx
	subq	$1, %rdx
	addq	%rdx, %rax
	movl	$16, %ebx
	movl	$0, %edx
	divq	%rbx
	imulq	$16, %rax, %rax
	subq	%rax, %rsp
	movq	%rsp, %rax
	addq	$0, %rax
	movq	%rax, -64(%rbp)
	movq	$.LC3, -72(%rbp)
	movl	%edi, %ebx
.L27:
	movq	%rsp, %rax
	movq	%rax, -112(%rbp)
	movq	login(%rip), %rax
	movq	%rax, %rsi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	printf
	movq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	read_line
	movl	$100, %eax
	cltq
	subq	$1, %rax
	movq	%rax, -80(%rbp)
	movl	$100, %eax
	cltq
	movq	%rax, %r12
	movl	$0, %r13d
	movl	$100, %eax
	cltq
	movq	%rax, %r14
	movl	$0, %r15d
	movl	$100, %eax
	cltq
	movl	$16, %edx
	subq	$1, %rdx
	addq	%rdx, %rax
	movl	$16, %ecx
	movl	$0, %edx
	divq	%rcx
	imulq	$16, %rax, %rax
	subq	%rax, %rsp
	movq	%rsp, %rax
	addq	$0, %rax
	movq	%rax, -88(%rbp)
	movq	-64(%rbp), %rax
	movl	$.LC3, %esi
	movq	%rax, %rdi
	call	sequals
	testb	%al, %al
	je	.L16
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %ebx
	movl	$0, %eax
	jmp	.L17
.L16:
	movq	-64(%rbp), %rax
	movl	$.LC5, %esi
	movq	%rax, %rdi
	call	begins
	testb	%al, %al
	je	.L18
	movq	-88(%rbp), %rcx
	movq	-64(%rbp), %rax
	movl	$4, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	sFirstCut
	movq	-88(%rbp), %rax
	movq	%rax, %rdi
	call	parseSet
	jmp	.L19
.L18:
	movq	-64(%rbp), %rax
	movl	$.LC6, %esi
	movq	%rax, %rdi
	call	begins
	testb	%al, %al
	je	.L20
	movq	-88(%rbp), %rcx
	movq	-64(%rbp), %rax
	movl	$5, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	sFirstCut
	movq	-88(%rbp), %rax
	movq	%rax, %rdi
	call	parseList
	jmp	.L19
.L20:
	movq	-64(%rbp), %rax
	movl	$.LC7, %esi
	movq	%rax, %rdi
	call	begins
	testb	%al, %al
	je	.L21
	movq	-88(%rbp), %rcx
	movq	-64(%rbp), %rax
	movl	$7, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	sFirstCut
	jmp	.L19
.L21:
	movq	-64(%rbp), %rax
	movl	$.LC8, %esi
	movq	%rax, %rdi
	call	begins
	testb	%al, %al
	je	.L22
	movq	-88(%rbp), %rcx
	movq	-64(%rbp), %rax
	movl	$5, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	sFirstCut
	jmp	.L19
.L22:
	movq	-64(%rbp), %rax
	movl	$.LC9, %esi
	movq	%rax, %rdi
	call	begins
	testb	%al, %al
	je	.L23
	movq	-88(%rbp), %rcx
	movq	-64(%rbp), %rax
	movl	$4, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	sFirstCut
	movq	-88(%rbp), %rax
	movq	%rax, %rdi
	call	buy
	jmp	.L19
.L23:
	movq	-64(%rbp), %rax
	movl	$.LC10, %esi
	movq	%rax, %rdi
	call	begins
	testb	%al, %al
	je	.L24
	movl	$0, %eax
	call	printInternHelp
	jmp	.L19
.L24:
	movl	$.LC11, %edi
	call	puts
.L19:
	movl	$1, %eax
.L17:
	movq	-112(%rbp), %rsp
	cmpl	$1, %eax
	jne	.L30
	jmp	.L27
.L30:
	movq	-104(%rbp), %rsp
	movl	%ebx, %eax
	leaq	-40(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	shell, .-shell
	.section	.rodata
.LC12:
	.string	"HELP:"
.LC13:
	.string	"List of commands:"
.LC14:
	.string	"\t set"
	.align 8
.LC15:
	.string	"\t\t user <user>\t - sets the user"
	.align 8
.LC16:
	.string	"\t\t password <pass>\t - sets the password,"
.LC17:
	.string	"\t\t\t\t ask if no argument"
.LC18:
	.string	"\t list"
	.align 8
.LC19:
	.string	"\t\t user <select>\t - prints all user,"
	.align 8
.LC20:
	.string	"\t\t\t\t if we have a select, search"
.LC21:
	.string	"\t search"
	.align 8
.LC22:
	.string	"\t\t user <select>\t - search a user in database"
	.align 8
.LC23:
	.string	"\t\t snack <select>\t - search a snack in database"
.LC24:
	.string	"\t buy"
	.align 8
.LC25:
	.string	"\t\t snack <select>\t - buy a snack,"
	.align 8
.LC26:
	.string	"\t\t\t\t select is the snack id (find it with search)"
.LC27:
	.string	"\t\t mate\t\t - buy a mate^^"
	.text
	.globl	printInternHelp
	.type	printInternHelp, @function
printInternHelp:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$.LC12, %edi
	call	puts
	movl	$.LC13, %edi
	call	puts
	movl	$.LC14, %edi
	call	puts
	movl	$.LC15, %edi
	call	puts
	movl	$.LC16, %edi
	call	puts
	movl	$.LC17, %edi
	call	puts
	movl	$.LC18, %edi
	call	puts
	movl	$.LC19, %edi
	call	puts
	movl	$.LC20, %edi
	call	puts
	movl	$.LC21, %edi
	call	puts
	movl	$.LC22, %edi
	call	puts
	movl	$.LC23, %edi
	call	puts
	movl	$.LC24, %edi
	call	puts
	movl	$.LC25, %edi
	call	puts
	movl	$.LC26, %edi
	call	puts
	movl	$.LC27, %edi
	call	puts
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	printInternHelp, .-printInternHelp
	.section	.rodata
.LC28:
	.string	""
	.text
	.globl	sFirstCut
	.type	sFirstCut, @function
sFirstCut:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, -36(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	strlen
	movl	-36(%rbp), %edx
	movslq	%edx, %rdx
	cmpq	%rdx, %rax
	jbe	.L33
	movl	-36(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcpy
	jmp	.L32
.L33:
	movq	$.LC28, -32(%rbp)
.L32:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	sFirstCut, .-sFirstCut
	.section	.rodata
.LC29:
	.string	"user "
.LC30:
	.string	"pass "
.LC31:
	.string	"Don't know what you want..."
	.text
	.globl	parseSet
	.type	parseSet, @function
parseSet:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$32, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -40(%rbp)
	movq	%rsp, %rsi
	movq	%rsi, %r12
	movl	$100, %esi
	movslq	%esi, %rsi
	subq	$1, %rsi
	movq	%rsi, -24(%rbp)
	movl	$100, %esi
	movslq	%esi, %rsi
	movq	%rsi, %rcx
	movl	$0, %ebx
	movl	$100, %ecx
	movslq	%ecx, %rcx
	movq	%rcx, %rax
	movl	$0, %edx
	movl	$100, %eax
	cltq
	movl	$16, %edx
	subq	$1, %rdx
	addq	%rdx, %rax
	movl	$16, %ebx
	movl	$0, %edx
	divq	%rbx
	imulq	$16, %rax, %rax
	subq	%rax, %rsp
	movq	%rsp, %rax
	addq	$0, %rax
	movq	%rax, -32(%rbp)
	movq	-40(%rbp), %rax
	movl	$.LC29, %esi
	movq	%rax, %rdi
	call	begins
	testb	%al, %al
	je	.L36
	movq	-32(%rbp), %rcx
	movq	-40(%rbp), %rax
	movl	$5, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	sFirstCut
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	setUser
	movl	$0, %eax
	jmp	.L37
.L36:
	movq	-40(%rbp), %rax
	movl	$.LC30, %esi
	movq	%rax, %rdi
	call	begins
	testb	%al, %al
	je	.L38
	movq	-32(%rbp), %rcx
	movq	-40(%rbp), %rax
	movl	$5, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	sFirstCut
	movq	-32(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L39
	movl	$0, %eax
	call	askPassword
	movl	$0, %eax
	jmp	.L37
.L39:
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	setPassword
	movl	$0, %eax
	jmp	.L37
.L38:
	movl	$.LC31, %edi
	call	puts
	movl	$1, %eax
.L37:
	movq	%r12, %rsp
	cmpl	$1, %eax
	leaq	-16(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	parseSet, .-parseSet
	.section	.rodata
.LC32:
	.string	"snack "
.LC33:
	.string	"mate"
	.text
	.globl	buy
	.type	buy, @function
buy:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$32, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -40(%rbp)
	movq	%rsp, %rsi
	movq	%rsi, %r12
	movl	$100, %esi
	movslq	%esi, %rsi
	subq	$1, %rsi
	movq	%rsi, -24(%rbp)
	movl	$100, %esi
	movslq	%esi, %rsi
	movq	%rsi, %rcx
	movl	$0, %ebx
	movl	$100, %ecx
	movslq	%ecx, %rcx
	movq	%rcx, %rax
	movl	$0, %edx
	movl	$100, %eax
	cltq
	movl	$16, %edx
	subq	$1, %rdx
	addq	%rdx, %rax
	movl	$16, %ebx
	movl	$0, %edx
	divq	%rbx
	imulq	$16, %rax, %rax
	subq	%rax, %rsp
	movq	%rsp, %rax
	addq	$0, %rax
	movq	%rax, -32(%rbp)
	movq	-40(%rbp), %rax
	movl	$.LC32, %esi
	movq	%rax, %rdi
	call	begins
	testb	%al, %al
	je	.L43
	movq	-32(%rbp), %rcx
	movq	-40(%rbp), %rax
	movl	$5, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	sFirstCut
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	buySnacks
	jmp	.L44
.L43:
	movq	-40(%rbp), %rax
	movl	$.LC33, %esi
	movq	%rax, %rdi
	call	begins
	testb	%al, %al
	je	.L44
	movl	$0, %eax
	call	buyMate
.L44:
	movq	%r12, %rsp
	leaq	-16(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	buy, .-buy
	.section	.rodata
.LC34:
	.string	" "
.LC35:
	.string	"%d"
	.text
	.globl	buySnacks
	.type	buySnacks, @function
buySnacks:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	$100, %eax
	cltq
	movq	%rax, %rdi
	call	malloc
	movq	%rax, -8(%rbp)
	movq	-24(%rbp), %rax
	movl	$.LC34, %esi
	movq	%rax, %rdi
	call	strtok
	movq	%rax, -8(%rbp)
	movl	$0, -12(%rbp)
	jmp	.L46
.L47:
	movl	-12(%rbp), %edx
	movq	-8(%rbp), %rax
	movl	$.LC35, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_sscanf
	cmpl	$1, %eax
	jne	.L46
	movl	-12(%rbp), %eax
	movl	%eax, %edi
	call	execBuy
.L46:
	cmpq	$0, -8(%rbp)
	jne	.L47
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	buySnacks, .-buySnacks
	.globl	buyMate
	.type	buyMate, @function
buyMate:
.LFB11:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, %eax
	movl	%eax, %edi
	call	execBuy
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	buyMate, .-buyMate
	.section	.rodata
.LC36:
	.string	"We need a user: "
.LC37:
	.string	"We need a password: "
.LC38:
	.string	"Buy snack with id: %d\n"
	.text
	.globl	execBuy
	.type	execBuy, @function
execBuy:
.LFB12:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movl	%edi, -68(%rbp)
	movq	login(%rip), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L50
	movq	%rsp, %rax
	movq	%rax, %rbx
	movl	$.LC36, %edi
	movl	$0, %eax
	call	printf
	movl	$100, %eax
	cltq
	subq	$1, %rax
	movq	%rax, -56(%rbp)
	movl	$100, %eax
	cltq
	movq	%rax, %r14
	movl	$0, %r15d
	movl	$100, %eax
	cltq
	movq	%rax, %r12
	movl	$0, %r13d
	movl	$100, %eax
	cltq
	movl	$16, %edx
	subq	$1, %rdx
	addq	%rdx, %rax
	movl	$16, %ecx
	movl	$0, %edx
	divq	%rcx
	imulq	$16, %rax, %rax
	subq	%rax, %rsp
	movq	%rsp, %rax
	addq	$0, %rax
	movq	%rax, -64(%rbp)
	movq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	read_line
	movq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	setUser
	movq	%rbx, %rsp
.L50:
	movq	login+8(%rip), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L51
	movl	$.LC37, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
	call	askPassword
.L51:
	movl	-68(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC38, %edi
	movl	$0, %eax
	call	printf
	movq	login+8(%rip), %rcx
	movq	login(%rip), %rax
	movl	-68(%rbp), %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	execBuyCmd
	leaq	-40(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	execBuy, .-execBuy
	.globl	askPassword
	.type	askPassword, @function
askPassword:
.LFB13:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	askPassword, .-askPassword
	.section	.rodata
.LC39:
	.string	"user"
.LC40:
	.string	"user: "
	.text
	.globl	parseList
	.type	parseList, @function
parseList:
.LFB14:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$32, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -40(%rbp)
	movq	%rsp, %rsi
	movq	%rsi, %r12
	movl	$100, %esi
	movslq	%esi, %rsi
	subq	$1, %rsi
	movq	%rsi, -24(%rbp)
	movl	$100, %esi
	movslq	%esi, %rsi
	movq	%rsi, %rcx
	movl	$0, %ebx
	movl	$100, %ecx
	movslq	%ecx, %rcx
	movq	%rcx, %rax
	movl	$0, %edx
	movl	$100, %eax
	cltq
	movl	$16, %edx
	subq	$1, %rdx
	addq	%rdx, %rax
	movl	$16, %ebx
	movl	$0, %edx
	divq	%rbx
	imulq	$16, %rax, %rax
	subq	%rax, %rsp
	movq	%rsp, %rax
	addq	$0, %rax
	movq	%rax, -32(%rbp)
	movq	-40(%rbp), %rax
	movl	$.LC39, %esi
	movq	%rax, %rdi
	call	begins
	testb	%al, %al
	je	.L54
	movl	$.LC40, %edi
	movl	$0, %eax
	call	printf
	movq	login(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf
	movl	$10, %edi
	call	putchar
.L54:
	movq	%r12, %rsp
	leaq	-16(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE14:
	.size	parseList, .-parseList
	.globl	setUser
	.type	setUser, @function
setUser:
.LFB15:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf
	movl	$10, %edi
	call	putchar
	movq	login(%rip), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcpy
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE15:
	.size	setUser, .-setUser
	.globl	setPassword
	.type	setPassword, @function
setPassword:
.LFB16:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	login+8(%rip), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcpy
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE16:
	.size	setPassword, .-setPassword
	.globl	begins
	.type	begins, @function
begins:
.LFB17:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$56, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movq	%rdi, -88(%rbp)
	movq	%rsi, -96(%rbp)
	movq	%rsp, %rax
	movq	%rax, %rbx
	movq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	strlen
	movl	%eax, -52(%rbp)
	movl	-52(%rbp), %eax
	addl	$1, %eax
	movslq	%eax, %rdx
	subq	$1, %rdx
	movq	%rdx, -64(%rbp)
	movslq	%eax, %rdx
	movq	%rdx, %r14
	movl	$0, %r15d
	movslq	%eax, %rdx
	movq	%rdx, %r12
	movl	$0, %r13d
	cltq
	movl	$16, %edx
	subq	$1, %rdx
	addq	%rdx, %rax
	movl	$16, %ecx
	movl	$0, %edx
	divq	%rcx
	imulq	$16, %rax, %rax
	subq	%rax, %rsp
	movq	%rsp, %rax
	addq	$0, %rax
	movq	%rax, -72(%rbp)
	movl	-52(%rbp), %eax
	movslq	%eax, %rdx
	movq	-72(%rbp), %rax
	movq	-88(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	strncpy
	movq	-72(%rbp), %rdx
	movl	-52(%rbp), %eax
	cltq
	movb	$0, (%rdx,%rax)
	movq	-72(%rbp), %rax
	movq	-96(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	sequals
	movq	%rbx, %rsp
	leaq	-40(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE17:
	.size	begins, .-begins
	.section	.rodata
.LC41:
	.string	"%[^\n]"
	.text
	.globl	read_line
	.type	read_line, @function
read_line:
.LFB18:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$32, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -40(%rbp)
	movq	%rsp, %rsi
	movq	%rsi, %r12
	movl	$100, %esi
	addl	$1, %esi
	movslq	%esi, %rsi
	subq	$1, %rsi
	movq	%rsi, -24(%rbp)
	movl	$100, %esi
	addl	$1, %esi
	movslq	%esi, %rsi
	movq	%rsi, %rcx
	movl	$0, %ebx
	movl	$100, %ecx
	addl	$1, %ecx
	movslq	%ecx, %rcx
	movq	%rcx, %rax
	movl	$0, %edx
	movl	$100, %eax
	addl	$1, %eax
	cltq
	movl	$16, %edx
	subq	$1, %rdx
	addq	%rdx, %rax
	movl	$16, %ebx
	movl	$0, %edx
	divq	%rbx
	imulq	$16, %rax, %rax
	subq	%rax, %rsp
	movq	%rsp, %rax
	addq	$0, %rax
	movq	%rax, -32(%rbp)
	movq	stdin(%rip), %rdx
	movl	$100, %ecx
	movq	-32(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	fgets
	movq	-32(%rbp), %rax
	movq	-40(%rbp), %rdx
	movl	$.LC41, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_sscanf
	cmpl	$1, %eax
	je	.L60
	movq	$.LC28, -40(%rbp)
.L60:
	movq	%r12, %rsp
	leaq	-16(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE18:
	.size	read_line, .-read_line
	.globl	sequals
	.type	sequals, @function
sequals:
.LFB19:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	je	.L62
	movq	-32(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	je	.L62
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	strlen
	movq	%rax, %rbx
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	strlen
	cmpq	%rax, %rbx
	je	.L63
.L62:
	movl	$0, %eax
	jmp	.L64
.L63:
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp
	testl	%eax, %eax
	jne	.L65
	movl	$1, %eax
	jmp	.L64
.L65:
	movl	$0, %eax
.L64:
	addq	$24, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE19:
	.size	sequals, .-sequals
	.ident	"GCC: (GNU) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
