# Grazielle Batista de Almeida - RA: 00351193
# Isabela Nunes dos Santos - RA: 00352519
# Sthefany Viveiros Cordeiro - RA: 00347631

# Medidor imaginário de radiação. O programa deverá receber o número inteiro do usuário e, com base no valor deste número, tomar diferentes decisões.
# Tipo 1: Caso o valor de radiação esteja entre 1 e 50 (1 e 50 inclusos)
# Tipo 2: Caso o valor de radiação esteja entre 51 e 99 (51 e 99 inclusos)
# Tipo 3: Caso o valor de radiação seja 100.
# Se o número estiver na classificação "Tipo 1", deverá ser armazenado o número 1 em $t5.
# Se o número estiver na classificação "Tipo 2", deverá ser armazenado o número 2 em $t5.
# Se o número estiver na classificação "Tipo 3", deverá ser armazenado o número 3 em $t5.

.data
    radiacao: .asciiz "Digite um numero inteiro positivo menor ou igual a 100: "

.text
    # Imprimir a mensagem
    addi $v0, $zero, 4        # Código de syscall para imprimir string
    la $a0, radiacao          # Carregar o endereço da string
    syscall
    
    # Ler o número do usuário
    addi $v0, $zero, 5        # Código de syscall para ler um inteiro
    syscall
    move $t0, $v0             # Armazenar o número em $t0
    
    # Comparar o número e definir o valor de $t5
    li $t1, 51                # Limite inferior (51)
    li $t2, 99                # Limite superior (99)
    li $t3, 100               # Limite para tipo3
    
    # Verificar se o número é menor que 51
    slt $t4, $t0, $t1         # $t4 = 1 se $t0 < 51
    beq $t4, $zero, tipo2     # Se não for menor que 51, vai para tipo2
    
    # Se o número for menor que 51, armazena 1 em $t5
    li $t5, 1
    j end
    
tipo2:
    # Verificar se o número está entre 51 e 99 (inclusive)
    slt $t4, $t0, $t3        # $t4 = 1 se $t0 < 99
    beq $t0,$t3,tipo3        #se t0 = 100, vai para tipo3
    bge $t0, $t1, tipo2_valid # Se $t0 >= 51, continua para tipo2_valid
    j end
    
tipo2_valid:
    # Se o número for entre 51 e 99 (inclusive), armazena 2 em $t5
    li $t5, 2
    j end
    
tipo3:
    # Se o número for exatamente 100
    li $t5, 3     # Verificar se o número é 100
    j end                      # Se não for 100, vai para o final do programa

end:
    # Finaliza o programa
    li $a0, 0                 # Código de saída 0
    li $v0, 10                # Código de syscall para sair
    syscall