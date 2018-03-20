	.text
	.file	"string.ll"
	.globl	mul_add
	.align	16, 0x90
	.type	mul_add,@function
mul_add:                                # @mul_add
	.cfi_startproc
# BB#0:
	imull	%esi, %edi
	leal	(%rdi,%rdx), %eax
	retq
.Lfunc_end0:
	.size	mul_add, .Lfunc_end0-mul_add
	.cfi_endproc


	.section	".note.GNU-stack","",@progbits
