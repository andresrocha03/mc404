.globl _start


.text


_start:
    jal main
    li a0, 0
    li a7, 93 # exit
    ecall


main:
    addi sp,sp,-4
    sw ra, 0(sp)

    # ler colunas e linhas 
    jal read
    mv s0, a1 # salvar conteudo do arquivo em s0
   
    jal to_decimal

    la t4, head_node
    li t1, 10001
    li a1, -1
    jal find_node

    la s1, result
    jal save

    jal write
    
    lw ra,0(sp)
    addi sp, sp, 4
    ret

read:
    la a1, input_address
    li a2, 10               # size - reads 10 bytes
    li a7, 63               # syscall read (63)
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
    # input: endereco da string em s0
    # output: numero inteiro em a0
    
    # converter string para int
    li t1, 10 # \n
    li t4, 1 # multiplicador
    li a0, 0
    
    lbu t2, 0(s0)
    addi s0, s0, 1
    li t3, 45 #  -
   
    bne t2, t3, loop_decimal
    li t4, -1
    lbu t2, 0(s0)
    addi s0, s0, 1

    loop_decimal: 
        beq t2, t1, end_loop_decimal
      
        addi t2, t2, -48
        mul a0, a0, t1
        add a0, t2, a0

        lbu t2, 0(s0)
        addi s0, s0, 1

    
        j loop_decimal
    
    end_loop_decimal:
        mul a0, a0, t4
        ret

find_node:
    # recebe endereco em t4 e um inteiro em a0
    # devolve o numero do nó em a1

    // t4 é no atual
    // t1 é a soma atual 
    // a0 é o inteiro que estamos procurando
    // a2 é o 0, pra ver se chegamos no ultimo no
    beq t1, a0, found
   
    li a2, 0 
    beq t4, a2, no_result_found
    
    lw t1, 0(t4)
    lw t2, 4(t4)
    lw t3, 8(t4)

    add t1, t2, t1
    add t1, t3, t1

    lw t4, 12(t4)
    addi a1, a1, 1
    j find_node
    
    found:
        ret
    
    no_result_found:
        li a1, -1
        ret

save:
    # salva um inteiro em result, como uma string
    # input: numero inteiro armazenado em a1, ponteiro para result armazenado em s1
    # output: resultado salvo em result
   
    // t5 é o \n
    // t6 é o 
    // t3 é -1, caso em que nenhum no foi encontrado
    li t5, 1
    li t6, 0
    li t3, -1
    
    bne a1, t3, yes_result
    no_result:
        li t4, 45
        sb t4, 0(s1)
        li t4, 49
        sb t4, 1(s1)
        sb t5, 2(s1)
        ret
   
    yes_result:
    mv t4, a1 // armazenar em t4 temporariamente para contar o numero de digitos

    li t2, 0
    loop_digit:    
        div t4, t4, t5  # retirar um digito do numero e guardar o quociente
        addi t2, t2,  1
        beq t4, t6, potencia
        j loop_digit
    
    li t1, 1
    li t6, 10
    potencia:
        beq t1, t2, end_potencia
        mul t5, t5, t6
        addi t1, t1, 1
        j potencia

    end_potencia:
    li t1, 0
    loop_save:
        beq t1, t2, end_all
        
        div t4, a1, t5  # retirar um digito do numero e guardar o quociente
        rem a1, a1, t5  # guardar resto da divisao 
        div t5, t5, t6

        addi t4, t4, 48 # converter para string
        sb t4, 0(s1)    # escrever digito em result na ordem inversa   

        addi s1, s1, 1
        addi t1, t1, 1
        j loop_save
    
    end_all:
        sb t5, 0(s1)
        ret

.bss
input_address: .skip 0x10 # buffer
result: .skip 0x10
