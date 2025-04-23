# Grazielle Batista de Almeida - RA: 00351193
# Isabela Nunes dos Santos - RA: 00352519
# Sthefany Viveiros Cordeiro - RA: 00347631

# Um número “a” é considerado um quadrado perfeito quando n2 = a. Faça um código que
# recebe um número digitado pelo usuário e verifica se o número digitado é um quadrado perfeito.
# Caso seja, deverá ser apresentada na tela a mensagem “Quadrado Perfeito”;
# caso contrário, deverá ser apresentada na tela a mensagem “Não é Quadrado Perfeito".

.data
    prompt:  .asciiz "Digite um numero: "
    msg_s:   .asciiz "Quadrado Perfeito\n"
    msg_n:   .asciiz "Nao e Quadrado Perfeito\n"
    
.text

addi $v0, $zero, 4    #v0 = 4  
la $a0, prompt        #a0 recebe a mensagem  
syscall               #Primeira mensagem (syscall codigo 4)  

addi $v0, $zero, 5    #v0 = 5  (input do numero inteiro do usuario em v0 (syscall codigo 5))
syscall  

add $t0, $v0, $zero   #t0 = v0  

addi $t1, $zero, 0    #t1 = 0  (contador)

loop:
    mul $t2, $t1, $t1   #i*i  
    beq $t2, $t0, sim   #Se i*i == numero, pula para 'sim'  
    bgt $t2, $t0, nao   #Se i*i > numero, pula para 'nao'  
    addi $t1, $t1, 1    #i = i+1  
    j loop              #Volta para o início do loop  

sim:
    addi $v0, $zero, 4  #Apresentacao da mensagem (syscall codigo 4)  
    la $a0, msg_s       #a0 recebe a mensagem 
    syscall  
    j fim  

nao:
    addi $v0, $zero, 4  #Apresentacao da mensagem (syscall codigo 4)  
    la $a0, msg_n       #a0 recebe a mensagem  
    syscall  

fim:
    addi $v0, $zero, 10 #Código de syscall para sair
syscall