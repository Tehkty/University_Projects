# Grazielle Batista de Almeida - RA: 00351193
# Isabela Nunes dos Santos - RA: 00352519
# Sthefany Viveiros Cordeiro - RA: 00347631

#L�gica do programa: o contador come�a do n�mero dado e vai at� 0, quando chegar em 0 
#sai do loop while onde calcula-se o fatorial e vai �para o final do programa

li $t0, 8 #numero n 
li $t1, 8 #contador i
li $t2, 1 #resultado do fatoria l fat = fat * i

while:
	beq $t1,$zero, end   #verifica se o contador � igual a 0, se sim pula para o end sen�o executa os comandos do while
	mul $t2, $t2,$t1     # fat = fat*i
	subi $t1,$t1,1       # i = i - 1
	j while              #volta para o loop while
	
end:
	move $t5,$t2 # t5 = t2