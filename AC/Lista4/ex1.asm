# Grazielle Batista de Almeida - RA: 00351193
# Isabela Nunes dos Santos - RA: 00352519
# Sthefany Viveiros Cordeiro - RA: 00347631

# Dado um n�mero armazenado em $t0 realiza uma chamada de procedimento que verifica se o n�mero � impar ou n�o.
# Caso o n�mero seja impar, ap�s o retorno da fun��o (procedimento) deve ser armazenado o valor 3 em $t3. 
# Caso contr�rio, deve ser armazenado o valor 2 em $t3.

li $t0,15             #$t0 recebe 15
li $t1,2              #$t1 recebe 2

jal evenOrOdd         #Salta para 'evenOrOdd' e salva o endere�o de retorno no registrador $ra

evenOrOdd:
	rem $t2,$t0,$t1          #Calcula o resto da divis�o de $t0 por $t1 e armazena em $t2
	beq $t2,$zero, isEven    #Se o resto for zero, vai para 'isEven'
	j isOdd                  #Caso contr�rio, salta para 'isOdd'
	jr $ra                   #Retorna para o endere�o salvo em $ra
	
isEven:
	li $t3,2                 #Se for par, carrega 2 no registrador $t3
	j fim                    #Salta para o fim do programa
	
isOdd:
	li $t3,3                 #Se for �mpar, carrega 3 no registrador $t3
	j fim                    #Salta para o fim do programa
   
fim: