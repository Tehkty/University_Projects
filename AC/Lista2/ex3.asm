# Grazielle Batista de Almeida - RA: 00351193
# Isabela Nunes dos Santos - RA: 00352519
# Sthefany Viveiros Cordeiro - RA: 00347631

# RA = 00351193, soma dos d�gitos = 0 + 0 + 3 + 5 + 1 + 1 + 9 + 3 = 22
# A soma dos dois �ltimos d�gitos � 9 + 3 = 12
# O offset � a soma dos d�gitos (22), mas ajustado para o pr�ximo m�ltiplo de 4, que � 24

li $t1, 12                  # Carrega a soma dos dois �ltimos d�gitos do RA (9 + 3) em $t1
addi $t0, $zero, 268500992  # Carrega o endere�o base da mem�ria em $t0

sw $t1, 24($t0)             # Armazena o valor 12 no endere�o de mem�ria (268500992 + 24)