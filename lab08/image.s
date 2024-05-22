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
    
    mv t1, a1
    # set canvas size
    jal set_canvas_size
    mv a1, t1

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

set_canvas_size:
    mv a0, t1
    mv a1, t1
    li a7, 2200
    ret

    
iterate_heading:
    # iterar cabecalho do arquivo salvo em s0
    # devolve numero de colunas e linhas em a1 e ponteiro para inicio da matriz em s0
    addi s0, s0, 3

    lbu a1, 0(s0)
    lbu a2, 1(s0)
    lbu a3, 2(s0)
    li t1, 10
    
    beq a2, t1, if # se o valor de colunas só possui um digito
    bne a2, t1, else # se o valor de colunas possui pelo menos dois digitos

    if:
        # é preciso somar 7 em s0
        addi s0,s0, 7
        # numero de linhas e colunas salvos em a1
        addi a1, a1, -48

    else:
        beq a3, t1, dois_digitos # o valor so possui dois digitos
        bne a3, t1, tres_digitos # o valor possui tres digitos
        dois_digitos:
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
        tres_digitos:
            # converter numero de string para int
            addi a1, a1, -48
            addi a2, a2, -48
            addi a3, a3, -48
            li t1, 100 
            mul a1, a1, t1
            li t1, 10
            mul a2, a2, t1  
            li t1, 1
            mul a1, a1, t1
            
            add a1, a1, a2
            add a1, a1, a3

            # é preciso somar 9 em s0
            addi s0, s0, 11            
    ret

iterate_matrix:
    # iterar matriz a partir do ponteiro salvo em s0, numero de linhas e colunas salvo em a1
    # 

    mul a1, a1, a1 # obter numero de elementos

    la t5, a2_input
    li t1, 0 # i
    li t2, 0 # x
    li t3, 0 # y
    li t6, 255 # alfa

    loop_matrix:
        beq t1, a1, endloop
        lb t4, 0(s0) # salvei o valor rgb da matriz
        # set pixel 
            # x e y
        mv a0, t2 
        mv a1, t3
            # salvar RGB e ALFA     
        lb t4, 0(t5)
        lb t4, 1(t5)
        lb t4, 2(t5)
        lb t6, 3(t5) 
        LW a2, a2_input

        li a7, 2200

        j loop_matrix

    endloop:
    ret

    


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
a2_input: .skip 0x32

