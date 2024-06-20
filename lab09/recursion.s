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

    jal find_node

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
    # input: endereco da string loop_digiem s0
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
    # recebe inteiro em a0
    # devolve o numero do nó em a0

    la a1, head_node // endereco do primeiro no
    li t4, 0 //contador de nos
    li t1, 10001 //valor soma total
    
    search_loop:
        lw t1, 0(a1)
        lw t2, 4(a1)
        lw t3, 8(a1)

        add t1, t2, t1
        add t1, t3, t1
        beq t1, a0, found
        
        lw a1, 12(a1)
        beq a1, zero, no_result_found
        
        addi t4, t4, 1
        j search_loop
    
    found:
        mv a0, t4  
        ret
    
    no_result_found:
        li a0, -1
        ret

save:
    # salva um inteiro em result, como uma string
    # input: numero inteiro armazenado em a0
    # output: resultado salvo em result
   
    // se a0 for -1, nao foi encontrado nenhum no
    li t1, -1
    la s1, result
    bne a0, t1, yes_result
        li t1, 45
        sb t1, 0(s1) // colocar o -
        li t1, 49
        sb t1, 1(s1) // colocar o 1
        li t1, 10
        sb t1, 2(s1) // colocar o \n
        ret
   
    yes_result: 
    mv t1, a0 // armazenar em t1 temporariamente para contar o numero de digitos
    li t2, 0
    li t3, 10
    conta_digito:    
        div t1, t1, t3  # retirar um digito do numero e guardar o quociente
        addi t2, t2,  1 // contabilizar o digito
        beq t1, zero, end_contagem
        j conta_digito

    // numero de digitos esta salvo em t2
    end_contagem:
    
    li t1, 1
    li t3, 1
    li t4, 10
    potencia:
        beq t1, t2, end_potencia
        mul t3, t3, t4
        addi t1, t1, 1
        j potencia

    //o valor do meu divisor esta guardado em t3
    end_potencia:
    
    li t1, 0
    li t5, 10
    loop_save:
        beq t1, t2, end_all

        div t4, a0, t3  # retirar um digito do numero e guardar o quociente
        rem a0, a0, t3  # guardar resto da divisao 
        div t3, t3, t5  # dividir divisor por 10

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
