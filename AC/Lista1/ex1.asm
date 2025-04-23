# Grazielle Batista de Almeida - RA: 00351193
# Isabela Nunes dos Santos - RA: 00352519
# Sthefany Viveiros Cordeiro - RA: 00347631

#Soma dos caracteres de um RA.   Ex. RA: 351193 -> Soma = 3+5+1+1+9+3 = 24

li $t0, 3             #$t0 recebe 3
addi $t1, $t0,5       #$t1 recebe 3 + 5 = 8
li $t2, 1             #$t2 recebe 1
addi $t3, $t2,1       #$t3 recebe 1 + 1
li $t4, 9             #$t4 recebe 9
addi $t5, $t4,3       #$t5 recebe 9 + 3
add $t6,$t1,$t3       #$t6 recebe 8 +2
add $t7, $t5,$t6      #$t7 recebe a soma completa do ra que é gual a 22