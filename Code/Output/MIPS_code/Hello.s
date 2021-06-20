	.text
	.abicalls
	.option	pic0
	.section	.mdebug.abi32,"",@progbits
	.nan	legacy
	.text
	.file	"main"
	.globl	main                            # -- Begin function main
	.p2align	2
	.type	main,@function
	.set	nomicromips
	.set	nomips16
	.ent	main
main:                                   # @main
	.cfi_startproc
	.frame	$sp,24,$ra
	.mask 	0x80000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
# %bb.0:                                # %main_entry
	addiu	$sp, $sp, -24
	.cfi_def_cfa_offset 24
	sw	$ra, 20($sp)                    # 4-byte Folded Spill
	.cfi_offset 31, -4
	lui	$1, %hi($format)
	addiu	$4, $1, %lo($format)
	lui	$1, %hi($string_tmp_)
	jal	printf
	addiu	$5, $1, %lo($string_tmp_)
	lw	$ra, 20($sp)                    # 4-byte Folded Reload
	jr	$ra
	addiu	$sp, $sp, 24
	.set	at
	.set	macro
	.set	reorder
	.end	main
$func_end0:
	.size	main, ($func_end0)-main
	.cfi_endproc
                                        # -- End function
	.type	$string_tmp_,@object            # @string_tmp_
	.section	.rodata.str1.1,"aMS",@progbits,1
$string_tmp_:
	.asciz	"Hello Wolrd"
	.size	$string_tmp_, 12

	.type	$format,@object                 # @format
$format:
	.asciz	"%s\n"
	.size	$format, 4

	.section	".note.GNU-stack","",@progbits
	.text
