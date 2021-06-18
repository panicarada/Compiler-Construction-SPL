	.text
	.abicalls
	.option	pic0
	.section	.mdebug.abi32,"",@progbits
	.nan	legacy
	.text
	.file	"main"
	.section	.rodata.cst8,"aM",@progbits,8
	.p2align	3                               # -- Begin function main
$CPI0_0:
	.8byte	0x400921fb4d12d84a              # double 3.1415926000000001
	.text
	.p2align	2
	.type	main,@function
	.set	nomicromips
	.set	nomips16
	.ent	main
main:                                   # @main
	.cfi_startproc
	.frame	$sp,40,$ra
	.mask 	0x80000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
# %bb.0:                                # %main_entry
	addiu	$sp, $sp, -40
	.cfi_def_cfa_offset 40
	sw	$ra, 36($sp)                    # 4-byte Folded Spill
	.cfi_offset 31, -4
	lui	$1, %hi($__unnamed_1)
	jal	printf
	addiu	$4, $1, %lo($__unnamed_1)
	lui	$1, %hi($__unnamed_2)
	addiu	$4, $1, %lo($__unnamed_2)
	jal	scanf
	addiu	$5, $sp, 24
	lui	$1, %hi($CPI0_0)
	ldc1	$f0, %lo($CPI0_0)($1)
	ldc1	$f2, 24($sp)
	c.ult.d	$f2, $f0
	bc1t	$BB0_2
	nop
# %bb.1:                                # %if
	ldc1	$f0, 24($sp)
	lui	$1, 19730
	ori	$1, $1, 55370
	sw	$1, 20($sp)
	lui	$1, 16393
	ori	$1, $1, 8699
	sw	$1, 16($sp)
	lui	$1, %hi($__unnamed_3)
	addiu	$4, $1, %lo($__unnamed_3)
	mfc1	$6, $f1
	jal	printf
	mfc1	$7, $f0
	j	$BB0_3
	nop
$BB0_2:                                 # %else
	ldc1	$f0, 24($sp)
	lui	$1, 19730
	ori	$1, $1, 55370
	sw	$1, 20($sp)
	lui	$1, 16393
	ori	$1, $1, 8699
	sw	$1, 16($sp)
	lui	$1, %hi($__unnamed_4)
	addiu	$4, $1, %lo($__unnamed_4)
	mfc1	$6, $f1
	jal	printf
	mfc1	$7, $f0
$BB0_3:                                 # %after
	lui	$1, %hi($__unnamed_5)
	jal	printf
	addiu	$4, $1, %lo($__unnamed_5)
	lw	$ra, 36($sp)                    # 4-byte Folded Reload
	jr	$ra
	addiu	$sp, $sp, 40
	.set	at
	.set	macro
	.set	reorder
	.end	main
$func_end0:
	.size	main, ($func_end0)-main
	.cfi_endproc
                                        # -- End function
	.type	$__unnamed_1,@object            # @0
	.section	.rodata.str1.1,"aMS",@progbits,1
$__unnamed_1:
	.asciz	"Input your value: "
	.size	$__unnamed_1, 19

	.type	$__unnamed_2,@object            # @1
$__unnamed_2:
	.asciz	"%lf"
	.size	$__unnamed_2, 4

	.type	$__unnamed_3,@object            # @2
$__unnamed_3:
	.asciz	"%lf >= %lf\n"
	.size	$__unnamed_3, 12

	.type	$__unnamed_4,@object            # @3
$__unnamed_4:
	.asciz	"%lf < %lf\n"
	.size	$__unnamed_4, 11

	.type	$__unnamed_5,@object            # @4
$__unnamed_5:
	.asciz	"ending!\n"
	.size	$__unnamed_5, 9

	.section	".note.GNU-stack","",@progbits
	.text
