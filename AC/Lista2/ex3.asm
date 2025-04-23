# Grazielle Batista de Almeida - RA: 00351193
# Isabela Nunes dos Santos - RA: 00352519
# Sthefany Viveiros Cordeiro - RA: 00347631

# RA = 00351193, soma dos dígitos = 0 + 0 + 3 + 5 + 1 + 1 + 9 + 3 = 22
# A soma dos dois últimos dígitos é 9 + 3 = 12
# O offset é a soma dos dígitos (22), mas ajustado para o próximo múltiplo de 4, que é 24

li $t1, 12                  # Carrega a soma dos dois últimos dígitos do RA (9 + 3) em $t1
addi $t0, $zero, 268500992  # Carrega o endereço base da memória em $t0

sw $t1, 24($t0)             # Armazena o valor 12 no endereço de memória (268500992 + 24)