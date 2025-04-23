# Grazielle Batista de Almeida - RA: 00351193
# Isabela Nunes dos Santos - RA: 00352519
# Sthefany Viveiros Cordeiro - RA: 00347631

# Dados dois números, armazenados em $t0 e $t1, implementa o algoritmo de multiplicação por somas sucessivas. 
# O resultado da multiplicação deverá ser armazenado na posição inicial da memória de dados do MIPS.
# (Considere que os números sempre serão números positivos)

li $t0,7           #primeiro número
li $t1,4           #segundo número e também contador no loop
move $t2, $t0      #t2 é o resultado da soma sucessiva e começa no primeiro número 
li $t3, 1          #valor para comparar antes de começar o loop

while:
	beq $t1,$t3,end     # se contador = 1 acaba as somas sucessivas e vai para end onde o resultado é registrado na memória
	subi $t1, $t1,1     #subtrai 1 do contador 
	add $t2,$t2,$t0	    # t2 = t2 + t0(resultado = número + resultado)
	j while             #volta para o loop
end:
	addi $t0, $zero, 268500992     #t0 recebe o primeiro endereço da memória
	sw $t2, ($t0)                  # o primeiro endereço da memória recebe o resultado das somas sucessivas guardado em t2
	