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
    addi s0, s0, 3
    lbu a1, 0(s0)
    lbu a2, 1(s0)
    lbu a3, 2(s0)
    jal iterate_heading
    mv s1, a1

    lbu a1, 0(s0)
    lbu a2, 1(s0)
    lbu a3, 2(s0)
    jal iterate_heading
    mv s2, a1
    
        # ponteiro apontando para o alfa
    jal read_alfa
    mv s3, a0
    
   
    # set canvas size
    jal set_canvas_size
   
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


read:

    la a1, input_address
    li a2, 262159      # size - reads 262159 bytes
    li a7, 63           # syscall read (63)
    ecall
    ret 

set_canvas_size:
    mv a0, s2
    mv a1, s1
    li a7, 2201
    ecall
    ret

    
iterate_heading:
    # iterar colunas, linhas e alfa do arquivo salvo em s0
    # devolve numero de colunas e linhas em a1 e ponteiro para inicio da matriz em s0
    li t1, 32
    
    beq a2, t1, if # se o valor de colunas só possui um digito
    bne a2, t1, else # se o valor de colunas possui pelo menos dois digitos

    if:
        # é preciso somar 2 em s0
        addi s0,s0, 2
        # numero de linhas ou colunas salvos em a1
        addi a1, a1, -48
        j cont

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

            # é preciso somar 3 em s0
            addi s0, s0, 3
            j cont
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

            # é preciso somar 4 em s0
            addi s0, s0, 4            
    cont:
        ret

read_alfa:
    # ponteiro para o alfa em s0
    # valor de alfa em a0
    li t1, 10
    
    lbu t2, 0(s0)
    lbu t3, 1(s0)
    lbu t4, 2(s0)

    beq t3, t1, alfaumdigito
    bne t3, t1, elsealfa
    

    alfaumdigito:
        # é preciso somar 2 em s0
        addi s0,s0, 2
        # alfa em a0
        mv a0, t2
        addi a0, a0, -48
        j contalfa
    
    elsealfa:
        beq t4, t1, alfadoisdigitos # o valor so possui dois digitos
        bne t4, t1, alfatresdigitos # o valor possui tres digitos
        alfadoisdigitos:
            # converter numero de string para int
            addi t2, t2, -48
            addi t3, t3, -48
            li t1, 10 
            mul t2, t2, t1
            li t1, 1
            mul t3, t3, t1  
            add a0, t2, t3

            # é preciso somar 3 em s0
            addi s0, s0, 3
            j contalfa

        alfatresdigitos:
            # converter numero de string para int
            addi t2, t2, -48
            addi t3, t3, -48
            addi t4, t4, -48
            
            li t1, 100 
            mul t2, t2, t1
            li t1, 10
            mul t3, t3, t1  
            li t1, 1
            mul t4, t4, t1
            
            add a0, t2, t3
            add a0, a0, t4

            # é preciso somar 4 em s0
            addi s0, s0, 4            

    contalfa:
        ret


iterate_matrix:
    # iterar matriz a partir do ponteiro salvo em s0, numero de linhas e colunas salvo em a1
    # 

    li t1, 0 # i
    li t0, 0 # j
    li t2, 0 # x
    li t3, 0 # y


    loop_matrix:
        beq t1, s2, endloop
        li t0, 0
        loop_colums:
            beq t0, s1, endloopcolums 
            li a2, 0x00000000
            lbu t4, 0(s0) # salvei o valor rgb da matriz

            slli t5, t4, 8 
            slli t6, t4, 16
            slli t4, t4, 24 
            
            add a2, a2, t4
            add a2, a2, t5
            add a2, a2, t6
            addi a2, a2, 255 # alfa
            # set pixel 
                # x e y
            mv a0, t0 
            mv a1, t1
                # salvar RGB e ALFA     
            li a7, 2200
            ecall
            # atualizar iteradores
            addi t0, t0, 1
            addi s0, s0, 1
            j loop_colums
        
        endloopcolums:
        addi t1, t1, 1
        j loop_matrix
    endloop:
    ret

.bss

input_address: .skip 0x4000F# buffer


.data 
input_file: .asciz "image.pgm"
