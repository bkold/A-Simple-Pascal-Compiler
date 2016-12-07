.data
NEW_LINE_CONSTANT: .asciiz "  \n"
XRay: .space 16
YRay: .space 16
ZRay: .space 336
BObject: .word 0 #24
 


.text
.globl main

main:
# Allocate 24 blocks for BObject
	li $v0, 9
	li $a0, 24
	syscall
	sw $v0, BObject
# temp_1 := (BObject + 16).All
	lw $t0, BObject
	addi $t0, $t0, 16
	addi $sp, $sp, -4
	sw $t0, 0($sp)
# Allocate 20 blocks for temp_1
	li $v0, 9
	li $a0, 20
	syscall
	lw $t1, 0($sp)
	addi $sp, $sp, 4
	sw $v0, 0($t1)
# temp_2 := (BObject + 20).All
	lw $t0, BObject
	addi $t0, $t0, 20
	addi $sp, $sp, -4
	sw $t0, 0($sp)
# temp_9223372036854775807.All := 5
	li $t0, 5
	lw $t1, 0($sp)
	addi $sp, $sp, 4
	sw $t0, 0($t1)
# temp_4 := (BObject + 20).All
	lw $t0, BObject
	addi $t0, $t0, 20
	addi $sp, $sp, -4
	sw $t0, 0($sp)
# PRINT(temp_4)
	li $v0, 1
	lw $t0, 0($sp)
	addi $sp, $sp, 4
	lw $a0, 0($t0)
	syscall
	li $v0, 4
	la $a0, NEW_LINE_CONSTANT
	syscall
# temp_6 := (BObject + 16).All
	lw $t0, BObject
	addi $t0, $t0, 16
	addi $sp, $sp, -4
	sw $t0, 0($sp)
# temp_7 := (temp_6 + 4).All
	lw $t0, 0($sp)
	addi $sp, $sp, 4
	lw $t0, 0($t0)
	addi $sp, $sp, -4
	sw $t0, 0($sp)
# temp_8 := 2 :: 9223372036854775798
	li $t0, 2
	addi $sp, $sp, -4
	sw $t0, 0($sp)
# temp_9 := temp_8 - 1
	li $t1, 1
	lw $t0, 0($sp)
	addi $sp, $sp, 4
	sub $t0, $t0, $t1
	addi $sp, $sp, -4
	sw $t0, 0($sp)
# temp_10 := temp_9 * 4
	li $t1, 4
	lw $t0, 0($sp)
	addi $sp, $sp, 4
	mult $t0, $t1
	mflo $t0
	addi $sp, $sp, -4
	sw $t0, 0($sp)
# temp_11 := temp_7'Address + temp_10
	lw $t1, 0($sp)
	addi $sp, $sp, 4
	lw $t0, 0($sp)
	addi $sp, $sp, 4
	add $t0, $t0, $t1
	addi $sp, $sp, -4
	sw $t0, 0($sp)
# temp_9223372036854775807.All := 4
	li $t0, 4
	lw $t1, 0($sp)
	addi $sp, $sp, 4
	sw $t0, 0($t1)
# temp_13 := (BObject + 16).All
	lw $t0, BObject
	addi $t0, $t0, 16
	addi $sp, $sp, -4
	sw $t0, 0($sp)
# temp_14 := (temp_13 + 4).All
	lw $t0, 0($sp)
	addi $sp, $sp, 4
	lw $t0, 0($t0)
	addi $sp, $sp, -4
	sw $t0, 0($sp)
# temp_15 := 2 :: 9223372036854775791
	li $t0, 2
	addi $sp, $sp, -4
	sw $t0, 0($sp)
# temp_16 := temp_15 - 1
	li $t1, 1
	lw $t0, 0($sp)
	addi $sp, $sp, 4
	sub $t0, $t0, $t1
	addi $sp, $sp, -4
	sw $t0, 0($sp)
# temp_17 := temp_16 * 4
	li $t1, 4
	lw $t0, 0($sp)
	addi $sp, $sp, 4
	mult $t0, $t1
	mflo $t0
	addi $sp, $sp, -4
	sw $t0, 0($sp)
# temp_18 := temp_14'Address + temp_17
	lw $t1, 0($sp)
	addi $sp, $sp, 4
	lw $t0, 0($sp)
	addi $sp, $sp, 4
	add $t0, $t0, $t1
	addi $sp, $sp, -4
	sw $t0, 0($sp)
# PRINT(temp_18)
	li $v0, 1
	lw $t0, 0($sp)
	addi $sp, $sp, 4
	lw $a0, 0($t0)
	syscall
	li $v0, 4
	la $a0, NEW_LINE_CONSTANT
	syscall
# Exit
	li	$v0, 10
	syscall
