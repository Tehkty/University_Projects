# Grazielle Batista de Almeida - RA: 00351193
# Isabela Nunes dos Santos - RA: 00352519
# Sthefany Viveiros Cordeiro - RA: 00347631

# Implemente uma versão em assembly do MIPS do algoritmo BubbleSort.
# Inicialmente deverão ser carregados 4 números, nos registradores $t0, $t1, $t2 e $t3. 
# Após a execução do algoritmo, os valores devem estar ordenados em ordem crescente nos mesmos registradores.

.data
msg1: .asciiz "Digite o primeiro numero: "
msg2: .asciiz "Digite o segundo numero: "
msg3: .asciiz "Digite o terceiro numero: "
msg4: .asciiz "Digite o quarto numero: "

.text

#1 numero
li $v0, 4
la $a0, msg1                  #a0 recebe a mensagem1
syscall

li $v0, 5
syscall                       #Leitura do numero
move $t0, $v0                 #$t0 recebe o valor lido

#2 numero
li $v0, 4
la $a0, msg2                  #a0 recebe a mensagem2
syscall

li $v0, 5
syscall                       #Leitura do numero
move $t1, $v0                 #$t1 recebe o valor lido

#3 numero
li $v0, 4
la $a0, msg3                  #a0 recebe a mensagem3
syscall

li $v0, 5
syscall                       #Leitura do numero
move $t2, $v0                 #$t2 recebe o valor lido

#4 numero
li $v0, 4
la $a0, msg4                  #a0 recebe a mensagem4
syscall

li $v0, 5
syscall                       #Leitura do numero
move $t3, $v0                 #$t3 recebe o valor lido

jal bubble_pass               #Chama a função para deixar o maior numero no t4
jal bubble_pass               #Chama novamente para deixar o segundo maior em t3
jal bubble_pass               #Última passagem para ordenar o terceiro maior em t2 (e logo o menor em t0)

li $v0, 10                    #Código de syscall para sair
syscall

bubble_pass:                  #Compara $t0 com $t1
    slt $t5, $t1, $t0         #$t5 = 1 se $t1 < $t0
    bne $t5, $zero, troca01   #Se verdade, realiza a troca
    j prox12                  #Se não, pula para a próxima comparação

troca01:                      #Troca entre $t0 e $t1
    move $t4, $t0             #Salva $t0 temporariamente em $t4
    move $t0, $t1             #Coloca o menor valor em $t0
    move $t1, $t4             #Coloca o valor antigo de $t0 em $t1

prox12:                       #Compara $t1 com $t2
    slt $t5, $t2, $t1         #$t5 = 1 se $t2 < $t1
    bne $t5, $zero, troca12   #Se verdade, faz a troca
    j prox23                  #Se não, pula pra próxima

troca12:                      #Troca entre $t1 e $t2
    move $t4, $t1             #Salva $t1
    move $t1, $t2             #Coloca o menor valor em $t1
    move $t2, $t4             #Coloca o valor antigo em $t2

prox23:                       #Compara $t2 com $t3
    slt $t5, $t3, $t2         #$t5 = 1 se $t3 < $t2
    bne $t5, $zero, troca23   #Se verdade, faz a troca
    jr $ra                    #Retorna da função se não precisar trocar

troca23:                      #Troca entre $t2 e $t3
    move $t4, $t2             #Salva $t2
    move $t2, $t3             #Coloca o menor valor em $t2
    move $t3, $t4             #Coloca o valor antigo em $t3
    jr $ra                    #Retorna da função