# Grazielle Batista de Almeida - RA: 00351193
# Isabela Nunes dos Santos - RA: 00352519
# Sthefany Viveiros Cordeiro - RA: 00347631

#Transformacao do código em linguagem C, para assembly do MIPS.

li $t0, 8             #$t0 recebe 8 (x)
li $t1, 4             #$t1 recebe 4 (y)
li $t2, 2             #$t2 recebe 2 (i)
li $t3, 0             #$t3 recebe 0 (usado para comparar com i)
 
while:
	beq $t2, $t3, fora     # Se $t2 (i) for igual a 0, sai do loop e vai para 'fora'
	addi $t1, $t1,2        #Incrementa $t1 (y) em 2 -> y = y + 2
	subi $t2, $t2,1        #Decrementa $t2 (i) em 1 -> i = i - 1
	j while                #Retorna para o início do loop

#Após o loop, calcula z = x + y
fora:
	add $t5, $t0,$t1       #Soma $t0 (x) e $t1 (y) e armazena o resultado em $t5 (z)