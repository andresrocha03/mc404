.globl recursive_tree_search
.globl puts
.globl gets
.globl atoi
.globl itoa
.globl exit

exit:
    mv a0, zero
    li a7, 93
    ecall

gets:
    addi sp, sp, -4
    sw ra, 0(sp)
    
    mv a1, a0
    jal read
    
    lw ra, 0(sp)
    addi sp, sp, 4
    ret

atoi:
    # converter uma string para um numero decimal
    # input: endereco da string a0
    # output: numero inteiro em a0
    
    # converter string para int
    li t1, 10 #
    li t4, 1 # multiplicador
    li t5, 0
    
    lbu t2, 0(a0)
    addi a0, a0, 1
    li t3, 45 #  -
   
    bne t2, t3, loop_decimal
    li t4, -1
    lbu t2, 0(a0)
    addi a0, a0, 1

    loop_decimal: 
        beq t2, zero, end_loop_decimal
        beq t2, t1, end_loop_decimal
      
        addi t2, t2, -48
        mul t5, t5, t1
        add t5, t2, t5
        lbu t2, 0(a0)

        addi a0, a0, 1

    
        j loop_decimal
    
    end_loop_decimal:
    mv a0, t5
    mul a0, a0, t4
    ret

recursive_tree_search:
    //root node em a0
    //val em a1

    search_value:
        addi sp, sp, -4
        sb ra, 0(sp)
        
        lw t1, 0(a0)
        beq t1, a1, found_result
        
        //go left
        addi sp, sp, -4
        sw a0, 0(sp)

        lw a0, 4(a0) //left
        beq a0, zero, direita
        
        jal search_value

    direita:
        lw t1, 0(sp)
        lw a0, 8(t1) //filho direito do pai
        beq
        jal search_value

    nulo:
        
    found_result:




itoa:
    //valor a ser convertido em a0
    //buffer a ser preenchido em a1
    //base 10 em a2 
   
    // se a0 for 0, nao foi encontrado nenhum no
    bne a0, zero, yes_result
        sb zero, 0(a1)
        ret
   
    yes_result: 
    mv t1, a0 // armazenar em t1 temporariamente para contar o numero de digitos
    li t2, 0
    li t3, 10
    conta_digito:    
        div t1, t1, t3  # retirar um digito do numero e guardar o quociente
        addi t2, t2,  1 // contabilizar o digito
        beq t1, zero, end_contagem
        beq t1, t3, end_contagem
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
        sb t4, 0(a1)    # escrever digito em result na ordem inversa   

        addi a1, a1, 1
        addi t1, t1, 1
        j loop_save
    
    end_all:
    sb zero, 0(a1)
    mv a0, a1
    ret


puts:
    //recebe string em a0

    addi sp, sp, -4
    sw ra, 0(sp)

    mv t1, a0
    li t3, 10
    li t2, 0

    conta_char:    
        lbu t4, 0(t1)
        addi t2, t2, 1 // contabilizar o digito
        addi t1, t1, 1
        beq t4, zero, end_contac
        beq t4, t3, end_contac 
        j conta_digito

    end_contac:
    
    mv a2, t2
    sb t3, 0(t1)
    jal write

    lw ra, 0(sp)
    addi sp, sp, 4
    ret




read:
    //la a1, input_address
    li a2, 20               # size - reads 10 bytes
    li a7, 63               # syscall read (63)
    ecall
    ret 


write:
    li a0, 1            # file descriptor = 1 (stdout)
    //la a1, result       # buffer
    //li a2, 20           # size - Writes 20 bytes.
    li a7, 64           # syscall write (64)
    ecall
    ret