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

    # ler colunas e linhas 
    jal read
    mv s0, a1 # salvar conteudo do arquivo em s0
   
    jal to_decimal

    lw ra,0(sp)
    addi sp, sp, 4
    ret

read:
    la a1, input_address
    li a2, 4     # size - reads 4 bytes
    li a7, 63           # syscall read (63)
    ecall
    ret 

write:
    li a0, 1            # file descriptor = 1 (stdout)
    la a1, result       # buffer
    li a2, 20           # size - Writes 20 bytes.
    li a7, 64           # syscall write (64)
    ecall
    ret

to_decimal:
    # converter uma string para um numero decimal
    # input: endereco da string em a0
    # output: numero inteiro em a0
    
    # converter string para int
    li t1, 10 // \n
    li t4, 1 //multiplicador
    mv s0, 0
    loop_decimal: 
        lbu t2, 0(s0)
        addi s0, s0, 1
        beq t2, t1, end_loop_decimal

        li t3, 95 // -
        beq t2, t3, negativo
        bne t2, t3, positivo

        negativo:
            li t4, -1
            lbu t2, 0(s0)
            addi s0, s0, 1

        positivo:
            addi t2, t2, -48
            mul t2, t2, t1
            mul s0, s0, t1
            add s0, t2
        j loop_decimal
    
    end_loop_decimal:
        ret


save:
    # salva um inteiro em result, como uma string no formato DDDD
    # input: numero inteiro armazenado em a0, ponteiro para result armazenado em s1
    # output: resultado salvo em result
    //li a0, 0
    li t5, 32
    
    li t3, 1000 # divisor
    div t4, a0, t3  # retirar um digito do numero e guardar o quociente
    rem a0, a0, t3  # guardar resto da divisao 
    addi t4, t4, 48 # converter para string
    sb t4, 0(s1)    # escrever digito em result na ordem inversa   

    li t3, 100   
    div t4, a0, t3  # retirar um digito do numero e guardar o quociente
    rem a0, a0, t3  # guardar resto da divisao 
    addi t4, t4, 48 # converter para string
    sb t4, 1(s1)    # escrever digito em result na ordem inversa   
    
    li t3, 10
    div t4, a0, t3  # retirar um digito do numero e guardar o quociente
    rem a0, a0, t3  # guardar resto da divisao 
    addi t4, t4, 48 # converter para string
    sb t4, 2(s1)    # escrever digito em result na ordem inversa   
    
    li t3, 1
    div t4, a0, t3  # retirar um digito do numero e guardar o quociente
    rem a0, a0, t3  # guardar resto da divisao 
    addi t4, t4, 48 # converter para string
    sb t4, 3(s1)    # escrever digito em result na ordem inversa   
    
    sb t5, 4(s1)
    ret



.bss

input_address: .skip 0x10 # buffer
result: .skip 0x10

