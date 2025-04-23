# Grazielle Batista de Almeida - RA: 00351193
# Isabela Nunes dos Santos - RA: 00352519
# Sthefany Viveiros Cordeiro - RA: 00347631

#Dados dois números, armazenados em t0 e t1, calculra o maior destes números e o armazena em t5.

li $t0, 4             #$t0 recebe 4
li $t1, 8             #$t1 recebe 8
li $t2, 1             #$t2 recebe 1

slt $t3,$t0,$t1       #Define $t3 como 1 se $t0 < $t1, caso contrário, define como 0
beq $t3,$t2,t1Maior   #Se $t3 for igual a 1 (ou seja, $t0 < $t1), pula para t1Maior
	move $t5,$t0  #Move o valor de $t0 para $t5 (pois $t0 é o maior)
	j end         #Salta para o fim do programa

#Se $t1 for maior, executa esta parte do código
t1Maior:
	move $t5,$t1  #Move o valor de $t1 para $t5 (pois $t1 é o maior)
	
#Fim do programa
end: