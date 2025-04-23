# Grazielle Batista de Almeida - RA: 00351193
# Isabela Nunes dos Santos - RA: 00352519
# Sthefany Viveiros Cordeiro - RA: 00347631

# Dados dois n�meros, armazenados em $t0 e $t1, implementa o algoritmo de multiplica��o por somas sucessivas. 
# O resultado da multiplica��o dever� ser armazenado na posi��o inicial da mem�ria de dados do MIPS.
# (Considere que os n�meros sempre ser�o n�meros positivos)

li $t0,7           #primeiro n�mero
li $t1,4           #segundo n�mero e tamb�m contador no loop
move $t2, $t0      #t2 � o resultado da soma sucessiva e come�a no primeiro n�mero 
li $t3, 1          #valor para comparar antes de come�ar o loop

while:
	beq $t1,$t3,end     # se contador = 1 acaba as somas sucessivas e vai para end onde o resultado � registrado na mem�ria
	subi $t1, $t1,1     #subtrai 1 do contador 
	add $t2,$t2,$t0	    # t2 = t2 + t0(resultado = n�mero + resultado)
	j while             #volta para o loop
end:
	addi $t0, $zero, 268500992     #t0 recebe o primeiro endere�o da mem�ria
	sw $t2, ($t0)                  # o primeiro endere�o da mem�ria recebe o resultado das somas sucessivas guardado em t2
	