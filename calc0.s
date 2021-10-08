	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp0:
	.cfi_def_cfa_offset 16
Ltmp1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp2:
	.cfi_def_cfa_register %rbp
	subq	$144, %rsp
	movl	$0, -4(%rbp)
	movl	%edi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rsi
	movq	8(%rsi), %rsi
	movq	%rsi, -24(%rbp)
	movb	$43, -26(%rbp)
	movl	$0, -32(%rbp)
	movl	$0, -36(%rbp)
	movl	$0, -40(%rbp)
	cmpl	$2, -8(%rbp)
	je	LBB0_2
## BB#1:
	leaq	L_.str(%rip), %rsi
	movq	___stderrp@GOTPCREL(%rip), %rax
	movq	(%rax), %rdi
	movq	-16(%rbp), %rax
	movq	(%rax), %rdx
	movb	$0, %al
	callq	_fprintf
	movl	$1, -4(%rbp)
	movl	%eax, -44(%rbp)         ## 4-byte Spill
	jmp	LBB0_44
LBB0_2:
	jmp	LBB0_3
LBB0_3:                                 ## =>This Inner Loop Header: Depth=1
	movq	-24(%rbp), %rax
	movsbl	(%rax), %ecx
	cmpl	$0, %ecx
	jne	LBB0_5
## BB#4:
	jmp	LBB0_43
LBB0_5:                                 ##   in Loop: Header=BB0_3 Depth=1
	movq	-24(%rbp), %rax
	movq	%rax, %rcx
	incq	%rcx
	movq	%rcx, -24(%rbp)
	movb	(%rax), %dl
	movb	%dl, -25(%rbp)
	movsbl	-25(%rbp), %esi
	addl	$-42, %esi
	movl	%esi, %eax
	subl	$41, %esi
	movq	%rax, -56(%rbp)         ## 8-byte Spill
	movl	%esi, -60(%rbp)         ## 4-byte Spill
	ja	LBB0_41
## BB#45:                               ##   in Loop: Header=BB0_3 Depth=1
	leaq	LJTI0_0(%rip), %rax
	movq	-56(%rbp), %rcx         ## 8-byte Reload
	movslq	(%rax,%rcx,4), %rdx
	addq	%rax, %rdx
	jmpq	*%rdx
LBB0_6:                                 ##   in Loop: Header=BB0_3 Depth=1
	cmpl	$0, -32(%rbp)
	jl	LBB0_8
## BB#7:                                ##   in Loop: Header=BB0_3 Depth=1
	imull	$10, -32(%rbp), %eax
	movsbl	-25(%rbp), %ecx
	subl	$48, %ecx
	addl	%ecx, %eax
	movl	%eax, -32(%rbp)
	jmp	LBB0_9
LBB0_8:                                 ##   in Loop: Header=BB0_3 Depth=1
	imull	$10, -32(%rbp), %eax
	movsbl	-25(%rbp), %ecx
	subl	$48, %ecx
	subl	%ecx, %eax
	movl	%eax, -32(%rbp)
LBB0_9:                                 ##   in Loop: Header=BB0_3 Depth=1
	jmp	LBB0_42
LBB0_10:                                ##   in Loop: Header=BB0_3 Depth=1
	movsbl	-26(%rbp), %eax
	addl	$-42, %eax
	movl	%eax, %ecx
	subl	$5, %eax
	movq	%rcx, -72(%rbp)         ## 8-byte Spill
	movl	%eax, -76(%rbp)         ## 4-byte Spill
	ja	LBB0_15
## BB#49:                               ##   in Loop: Header=BB0_3 Depth=1
	leaq	LJTI0_4(%rip), %rax
	movq	-72(%rbp), %rcx         ## 8-byte Reload
	movslq	(%rax,%rcx,4), %rdx
	addq	%rax, %rdx
	jmpq	*%rdx
LBB0_11:                                ##   in Loop: Header=BB0_3 Depth=1
	movl	-32(%rbp), %eax
	addl	-36(%rbp), %eax
	movl	%eax, -36(%rbp)
	jmp	LBB0_15
LBB0_12:                                ##   in Loop: Header=BB0_3 Depth=1
	movl	-32(%rbp), %eax
	movl	-36(%rbp), %ecx
	subl	%eax, %ecx
	movl	%ecx, -36(%rbp)
	jmp	LBB0_15
LBB0_13:                                ##   in Loop: Header=BB0_3 Depth=1
	movl	-32(%rbp), %eax
	imull	-36(%rbp), %eax
	movl	%eax, -36(%rbp)
	jmp	LBB0_15
LBB0_14:                                ##   in Loop: Header=BB0_3 Depth=1
	movl	-32(%rbp), %eax
	movl	-36(%rbp), %ecx
	movl	%eax, -80(%rbp)         ## 4-byte Spill
	movl	%ecx, %eax
	cltd
	movl	-80(%rbp), %ecx         ## 4-byte Reload
	idivl	%ecx
	movl	%eax, -36(%rbp)
LBB0_15:                                ##   in Loop: Header=BB0_3 Depth=1
	movl	$0, -32(%rbp)
	movb	-25(%rbp), %al
	movb	%al, -26(%rbp)
	jmp	LBB0_42
LBB0_16:                                ##   in Loop: Header=BB0_3 Depth=1
	movsbl	-26(%rbp), %eax
	addl	$-42, %eax
	movl	%eax, %ecx
	subl	$5, %eax
	movq	%rcx, -88(%rbp)         ## 8-byte Spill
	movl	%eax, -92(%rbp)         ## 4-byte Spill
	ja	LBB0_21
## BB#48:                               ##   in Loop: Header=BB0_3 Depth=1
	leaq	LJTI0_3(%rip), %rax
	movq	-88(%rbp), %rcx         ## 8-byte Reload
	movslq	(%rax,%rcx,4), %rdx
	addq	%rax, %rdx
	jmpq	*%rdx
LBB0_17:                                ##   in Loop: Header=BB0_3 Depth=1
	movl	-32(%rbp), %eax
	addl	-36(%rbp), %eax
	movl	%eax, -36(%rbp)
	jmp	LBB0_21
LBB0_18:                                ##   in Loop: Header=BB0_3 Depth=1
	movl	-32(%rbp), %eax
	movl	-36(%rbp), %ecx
	subl	%eax, %ecx
	movl	%ecx, -36(%rbp)
	jmp	LBB0_21
LBB0_19:                                ##   in Loop: Header=BB0_3 Depth=1
	movl	-32(%rbp), %eax
	imull	-36(%rbp), %eax
	movl	%eax, -36(%rbp)
	jmp	LBB0_21
LBB0_20:                                ##   in Loop: Header=BB0_3 Depth=1
	movl	-32(%rbp), %eax
	movl	-36(%rbp), %ecx
	movl	%eax, -96(%rbp)         ## 4-byte Spill
	movl	%ecx, %eax
	cltd
	movl	-96(%rbp), %ecx         ## 4-byte Reload
	idivl	%ecx
	movl	%eax, -36(%rbp)
LBB0_21:                                ##   in Loop: Header=BB0_3 Depth=1
	leaq	L_.str.1(%rip), %rdi
	movl	$0, -32(%rbp)
	movb	$43, -26(%rbp)
	movl	-36(%rbp), %esi
	movb	$0, %al
	callq	_printf
	movl	$0, -36(%rbp)
	movl	%eax, -100(%rbp)        ## 4-byte Spill
	jmp	LBB0_42
LBB0_22:                                ##   in Loop: Header=BB0_3 Depth=1
	cmpl	$0, -32(%rbp)
	je	LBB0_29
## BB#23:                               ##   in Loop: Header=BB0_3 Depth=1
	movsbl	-26(%rbp), %eax
	addl	$-42, %eax
	movl	%eax, %ecx
	subl	$5, %eax
	movq	%rcx, -112(%rbp)        ## 8-byte Spill
	movl	%eax, -116(%rbp)        ## 4-byte Spill
	ja	LBB0_28
## BB#47:                               ##   in Loop: Header=BB0_3 Depth=1
	leaq	LJTI0_2(%rip), %rax
	movq	-112(%rbp), %rcx        ## 8-byte Reload
	movslq	(%rax,%rcx,4), %rdx
	addq	%rax, %rdx
	jmpq	*%rdx
LBB0_24:                                ##   in Loop: Header=BB0_3 Depth=1
	movl	-32(%rbp), %eax
	addl	-36(%rbp), %eax
	movl	%eax, -36(%rbp)
	jmp	LBB0_28
LBB0_25:                                ##   in Loop: Header=BB0_3 Depth=1
	movl	-32(%rbp), %eax
	movl	-36(%rbp), %ecx
	subl	%eax, %ecx
	movl	%ecx, -36(%rbp)
	jmp	LBB0_28
LBB0_26:                                ##   in Loop: Header=BB0_3 Depth=1
	movl	-32(%rbp), %eax
	imull	-36(%rbp), %eax
	movl	%eax, -36(%rbp)
	jmp	LBB0_28
LBB0_27:                                ##   in Loop: Header=BB0_3 Depth=1
	movl	-32(%rbp), %eax
	movl	-36(%rbp), %ecx
	movl	%eax, -120(%rbp)        ## 4-byte Spill
	movl	%ecx, %eax
	cltd
	movl	-120(%rbp), %ecx        ## 4-byte Reload
	idivl	%ecx
	movl	%eax, -36(%rbp)
LBB0_28:                                ##   in Loop: Header=BB0_3 Depth=1
	jmp	LBB0_29
LBB0_29:                                ##   in Loop: Header=BB0_3 Depth=1
	movl	-36(%rbp), %eax
	addl	-40(%rbp), %eax
	movl	%eax, -40(%rbp)
	movl	$0, -32(%rbp)
	movl	$0, -36(%rbp)
	movb	$43, -26(%rbp)
	jmp	LBB0_42
LBB0_30:                                ##   in Loop: Header=BB0_3 Depth=1
	cmpl	$0, -32(%rbp)
	je	LBB0_37
## BB#31:                               ##   in Loop: Header=BB0_3 Depth=1
	movsbl	-26(%rbp), %eax
	addl	$-42, %eax
	movl	%eax, %ecx
	subl	$5, %eax
	movq	%rcx, -128(%rbp)        ## 8-byte Spill
	movl	%eax, -132(%rbp)        ## 4-byte Spill
	ja	LBB0_36
## BB#46:                               ##   in Loop: Header=BB0_3 Depth=1
	leaq	LJTI0_1(%rip), %rax
	movq	-128(%rbp), %rcx        ## 8-byte Reload
	movslq	(%rax,%rcx,4), %rdx
	addq	%rax, %rdx
	jmpq	*%rdx
LBB0_32:                                ##   in Loop: Header=BB0_3 Depth=1
	movl	-32(%rbp), %eax
	addl	-36(%rbp), %eax
	movl	%eax, -36(%rbp)
	jmp	LBB0_36
LBB0_33:                                ##   in Loop: Header=BB0_3 Depth=1
	movl	-32(%rbp), %eax
	movl	-36(%rbp), %ecx
	subl	%eax, %ecx
	movl	%ecx, -36(%rbp)
	jmp	LBB0_36
LBB0_34:                                ##   in Loop: Header=BB0_3 Depth=1
	movl	-32(%rbp), %eax
	imull	-36(%rbp), %eax
	movl	%eax, -36(%rbp)
	jmp	LBB0_36
LBB0_35:                                ##   in Loop: Header=BB0_3 Depth=1
	movl	-32(%rbp), %eax
	movl	-36(%rbp), %ecx
	movl	%eax, -136(%rbp)        ## 4-byte Spill
	movl	%ecx, %eax
	cltd
	movl	-136(%rbp), %ecx        ## 4-byte Reload
	idivl	%ecx
	movl	%eax, -36(%rbp)
LBB0_36:                                ##   in Loop: Header=BB0_3 Depth=1
	jmp	LBB0_37
LBB0_37:                                ##   in Loop: Header=BB0_3 Depth=1
	movl	-36(%rbp), %eax
	movl	-40(%rbp), %ecx
	subl	%eax, %ecx
	movl	%ecx, -40(%rbp)
	movl	$0, -32(%rbp)
	movl	$0, -36(%rbp)
	jmp	LBB0_42
LBB0_38:                                ##   in Loop: Header=BB0_3 Depth=1
	leaq	L_.str.1(%rip), %rdi
	movl	-40(%rbp), %eax
	movl	%eax, -32(%rbp)
	movl	-40(%rbp), %esi
	movb	$0, %al
	callq	_printf
	movl	%eax, -140(%rbp)        ## 4-byte Spill
	jmp	LBB0_42
LBB0_39:                                ##   in Loop: Header=BB0_3 Depth=1
	movl	$0, -40(%rbp)
	jmp	LBB0_42
LBB0_40:                                ##   in Loop: Header=BB0_3 Depth=1
	xorl	%eax, %eax
	subl	-32(%rbp), %eax
	movl	%eax, -32(%rbp)
	jmp	LBB0_42
LBB0_41:
	leaq	L_.str.2(%rip), %rdi
	movsbl	-25(%rbp), %esi
	movb	$0, %al
	callq	_printf
	movl	$1, -4(%rbp)
	movl	%eax, -144(%rbp)        ## 4-byte Spill
	jmp	LBB0_44
LBB0_42:                                ##   in Loop: Header=BB0_3 Depth=1
	jmp	LBB0_3
LBB0_43:
	movl	$0, -4(%rbp)
LBB0_44:
	movl	-4(%rbp), %eax
	addq	$144, %rsp
	popq	%rbp
	retq
	.cfi_endproc
	.align	2, 0x90
L0_0_set_10 = LBB0_10-LJTI0_0
L0_0_set_41 = LBB0_41-LJTI0_0
L0_0_set_6 = LBB0_6-LJTI0_0
L0_0_set_16 = LBB0_16-LJTI0_0
L0_0_set_39 = LBB0_39-LJTI0_0
L0_0_set_30 = LBB0_30-LJTI0_0
L0_0_set_22 = LBB0_22-LJTI0_0
L0_0_set_38 = LBB0_38-LJTI0_0
L0_0_set_40 = LBB0_40-LJTI0_0
LJTI0_0:
	.long	L0_0_set_10
	.long	L0_0_set_10
	.long	L0_0_set_41
	.long	L0_0_set_10
	.long	L0_0_set_41
	.long	L0_0_set_10
	.long	L0_0_set_6
	.long	L0_0_set_6
	.long	L0_0_set_6
	.long	L0_0_set_6
	.long	L0_0_set_6
	.long	L0_0_set_6
	.long	L0_0_set_6
	.long	L0_0_set_6
	.long	L0_0_set_6
	.long	L0_0_set_6
	.long	L0_0_set_41
	.long	L0_0_set_41
	.long	L0_0_set_41
	.long	L0_0_set_16
	.long	L0_0_set_41
	.long	L0_0_set_41
	.long	L0_0_set_41
	.long	L0_0_set_41
	.long	L0_0_set_41
	.long	L0_0_set_39
	.long	L0_0_set_41
	.long	L0_0_set_41
	.long	L0_0_set_41
	.long	L0_0_set_41
	.long	L0_0_set_41
	.long	L0_0_set_41
	.long	L0_0_set_41
	.long	L0_0_set_41
	.long	L0_0_set_41
	.long	L0_0_set_30
	.long	L0_0_set_41
	.long	L0_0_set_41
	.long	L0_0_set_22
	.long	L0_0_set_41
	.long	L0_0_set_38
	.long	L0_0_set_40
L0_1_set_34 = LBB0_34-LJTI0_1
L0_1_set_32 = LBB0_32-LJTI0_1
L0_1_set_36 = LBB0_36-LJTI0_1
L0_1_set_33 = LBB0_33-LJTI0_1
L0_1_set_35 = LBB0_35-LJTI0_1
LJTI0_1:
	.long	L0_1_set_34
	.long	L0_1_set_32
	.long	L0_1_set_36
	.long	L0_1_set_33
	.long	L0_1_set_36
	.long	L0_1_set_35
L0_2_set_26 = LBB0_26-LJTI0_2
L0_2_set_24 = LBB0_24-LJTI0_2
L0_2_set_28 = LBB0_28-LJTI0_2
L0_2_set_25 = LBB0_25-LJTI0_2
L0_2_set_27 = LBB0_27-LJTI0_2
LJTI0_2:
	.long	L0_2_set_26
	.long	L0_2_set_24
	.long	L0_2_set_28
	.long	L0_2_set_25
	.long	L0_2_set_28
	.long	L0_2_set_27
L0_3_set_19 = LBB0_19-LJTI0_3
L0_3_set_17 = LBB0_17-LJTI0_3
L0_3_set_21 = LBB0_21-LJTI0_3
L0_3_set_18 = LBB0_18-LJTI0_3
L0_3_set_20 = LBB0_20-LJTI0_3
LJTI0_3:
	.long	L0_3_set_19
	.long	L0_3_set_17
	.long	L0_3_set_21
	.long	L0_3_set_18
	.long	L0_3_set_21
	.long	L0_3_set_20
L0_4_set_13 = LBB0_13-LJTI0_4
L0_4_set_11 = LBB0_11-LJTI0_4
L0_4_set_15 = LBB0_15-LJTI0_4
L0_4_set_12 = LBB0_12-LJTI0_4
L0_4_set_14 = LBB0_14-LJTI0_4
LJTI0_4:
	.long	L0_4_set_13
	.long	L0_4_set_11
	.long	L0_4_set_15
	.long	L0_4_set_12
	.long	L0_4_set_15
	.long	L0_4_set_14

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"Usage: %s prob_file\n"

L_.str.1:                               ## @.str.1
	.asciz	"%d\n"

L_.str.2:                               ## @.str.2
	.asciz	"\"%c\" is wrong."


.subsections_via_symbols
