# Grazielle Batista de Almeida - RA: 00351193
# Isabela Nunes dos Santos - RA: 00352519
# Sthefany Viveiros Cordeiro - RA: 00347631

# Dados dois números A e B, digitados pelo usuário, calcula o resto da divisão de A por B. 
# Este resto da divisão deverá ser armazenado em $t5

.data
	a: .asciiz "Digite o primeiro número inteiro positivo: "
	b: .asciiz "Digite o segundo número inteiro positivo: "
.text
	addi $v0,$zero,4
	la $a0,a
	syscall
	
	addi $v0,$zero,5
	syscall
	
	move $t0,$v0
	
	addi $v0,$zero,4
	la $a0,a
	syscall
	
	addi $v0,$zero,5
	syscall
	
	move $t1,$v0
	
	div $t0,$t1
	mfhi $t5 #t5 recebe o resto da divisão