.globl _start

_start:
    jal main
    li a0, 0
    li a7, 93 # exit
    ecall

.text

main:
    addi sp,sp,-4
    sw ra, 0(sp)

    # abrir arquivo e salvar em a0
    jal open


    # ler colunas e linhas 
    jal read
    mv s0, a1 # salvar conteudo do arquivo em s0

    # iterar cabecalho
    jal iterate_heading
    
    # iterar matriz e setar pixels no canvas
    jal iterate_matrix
   
    lw ra,0(sp)
    addi sp, sp, 4
    ret

open:
    la a0, input_file    # address for the file path
    li a1, 0             # flags (0: rdonly, 1: wronly, 2: rdwr)
    li a2, 0             # mode
    li a7, 1024          # syscall open 
    ecall
    input_file: .asciz "image.pgm"


read:

    li a0, 0            # file descriptor = 0 (stdin)
    la a1, input_address
    li a2, 262159            # size - reads 262159 bytes
    li a7, 63           # syscall read (63)
    ecall
   
    ret 

write:
    li a0, 1                # file descriptor = 1 (stdout)
    la a1, result           # buffer
    li a2, 20               # size - Writes 20 bytes.
    li a7, 64               # syscall write (64)
    ecall
    ret
    
iterate_heading:
    # iterar cabecalho do arquivo salvo em s0
    # devolve numero de colunas e linhas em a1 e ponteiro para inicio da matriz em s0
    addi s0, s0, 3

    lbu a1, 0(s0)
    lbu a2, 1(s0)
    li t1, 10
    
    beq a2, t1, if # se o valor de colunas só possui um digito
    bne a2, t1, else # se o valor de colunas possui dois digitos

    if:
        # é preciso somar 7 em s0
        addi s0,s0, 7
        # numero de linhas e colunas salvos em a1
        addi a1, a1, -48

    else:
        # converter numero de string para int
        addi a1, a1, -48
        addi a2, a2, -48
        li t1, 10 
        mul a1, a1, t1
        li t1, 1
        mul a2, a2, t1  
        add a1, a1, a2

        # é preciso somar 9 em s0
        addi s0, s0, 9
    ret

iterate_matrix:
    # iterar matriz a partir do ponteiro salvo em s0, numero de linhas e colunas salvo em a1
    # 

    mul a1, a1, a1 # obter numero de elementos

    li t1, 0
    loop_matrix:
        beq t1, a1, endloop
        

    j loop_matrix
    endloop:


    


save:
    # salva um inteiro em result, como uma string no formato SDDDD
    # input: numero inteiro armazenado em a0, ponteiro para result armazenado em s1
    # output: resultado salvo em result

    li t1, 0
    li t4, 43
    bge a0, t1, menor # verificar se é maior ou igual que 0
        li t4, 45
        li t1, -1
        mul a0, a0, t1  # operar numero positivo na conversao para string
    menor:
    sb t4, 0(s1)

    
    
    li t3, 1000     # divisor
    div t4, a0, t3  # retirar um digito do numero e guardar o quociente
    rem a0, a0, t3  # guardar resto da divisao 
    addi t4, t4, 48 # converter para string
    sb t4, 1(s1)    # escrever digito em result   

    li t3, 100   
    div t4, a0, t3  # retirar um digito do numero e guardar o quociente
    rem a0, a0, t3  # guardar resto da divisao 
    addi t4, t4, 48 # converter para string
    sb t4, 2(s1)    # escrever digito em result    
    
    li t3, 10
    div t4, a0, t3  # retirar um digito do numero e guardar o quociente
    rem a0, a0, t3  # guardar resto da divisao 
    addi t4, t4, 48 # converter para string
    sb t4, 3(s1)    # escrever digito em result    
    
    li t3, 1
    div t4, a0, t3  # retirar um digito do numero e guardar o quociente
    rem a0, a0, t3  # guardar resto da divisao 
    addi t4, t4, 48 # converter para string
    sb t4, 4(s1)    # escrever digito em result 
    
    
    ret

.bss
input_address: .skip 262159  # buffer
a2_address: .skip 0x32

