# Grazielle Batista de Almeida - RA: 00351193
# Isabela Nunes dos Santos - RA: 00352519
# Sthefany Viveiros Cordeiro - RA: 00347631

#Transformacao do c�digo em linguagem C, para assembly do MIPS:
# if (x == y)
# z = 2;
# else
# z = 3;

#x deve ser armazenado em t0
# y deve ser armazenado em t1
# z deve ser armazenado em t5
# Escolha valores arbitr�rios para x e y, e n�o se esque�a de testar ambos os casos

li $t0, 11             #$t0 recebe 11 (x)
li $t1, 11             #$t1 recebe 11 (y)

beq $t0, $t1, achaZ    #compara $t0 == $t1, csso sejam iguais vai para label achaZ caso contr�rio vai para fim
	li $t5, 3      #$t5 recebe 3 (z)
	j fim          #Salta para o fim do programa
	
#Se x == y, executa esta parte (z = 2)
achaZ:
	li $t5, 2      #$t5 recebe 2 (z)
	
# Fim do programa
fim: