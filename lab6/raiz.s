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
    # ponteiro para a resposta 
    la s1, result

    # parametros do for
    li s2, 0    # i = 0 
    li s3, 4    # limite do for
  
    # salvei o input em s0
    jal read

    loop_main:
        bge s2, s3, lab_main # if i < 4
        # obter os digitos da string salva em s0
        jal get_digit

        # get int number from 4 str
        jal to_decimal 

        # calcular raiz quadrada
        //jal sqrt 

        # salvar resposta em result
        jal save

        # atualizar ponteiro do input
        addi s0, s0, 5  # s1 <= &input_addres[s0] + 5 

        # atualizar ponteiro do result
        addi s1, s1, 5  # s1 <= &result[s1] + 5 

        addi s2, s2, 1

        j loop_main

    lab_main: 
        jal write
        lw ra,0(sp)
        addi sp, sp, 4
        ret

read:

    li a0, 0            # file descriptor = 0 (stdin)
    la s0, input_address# buffer
    li a2, 20           # size - Reads 20 bytes.
    li a7, 63           # syscall read (63)
    ecall
   
    ret 

write:
    li a0, 1            # file descriptor = 1 (stdout)
    la a1, result           # buffer
    li a2, 20       # size - Writes 20 bytes.
    li a7, 64           # syscall write (64)
    ecall
    ret

get_digit:
    # input string em s0
    # output digitos da string em a0,a1,a2,a3
    lbu a0, 0(s0)
    lbu a1, 1(s0)
    lbu a2, 2(s0)
    lbu a3, 3(s0)
    ret

to_decimal:
    # converter uma string para um numero decimal
    # input: 4 caracteres em a0, a1, a2, a3
    # output: numero inteiro em a0
    
    # converter string para int
    addi a0, a0, -48
    addi a1, a1, -48
    addi a2, a2, -48
    addi a3, a3, -48
    
    # multiplicar pelas potencias de 10
    li t5, 1000
    mul a0, a0, t5
    li t5, 100
    mul a1, a1, t5
    li t5, 10
    mul a2, a2, t5
    li t5, 1
    mul a3, a3, t5
    
    add a0, a0, a1
    add a0, a0, a2
    add a0, a0, a3
    ret

sqrt:
    # calcular raiz
    # input: numero decimal salvo em a0
    # output: raiz quadrada aproximada em a0
    li t1, 0    # i do for
    li t2, 10   # limite do for
    li t3, 0    # y/k
    li t4, 0    # k 
    li t5, 2    
    
    div t4, a0, t5 # k = y/2
    loop_sqrt:
        bge t1, t2, lab_sqrt    # Sai do laço se i >= 10
        div t3, a0, t4      # y/k
        add t4, t4, t3      # k + y/k
        div t4, t4, t5       # (k + y/k)/2
        addi t1, t1, 1      # i <= i+1
        j loop_sqrt

    lab_sqrt:
        mv a0, t4
        ret

save:
    # salva um inteiro em result, como uma string no formato DDDD
    # input: numero inteiro armazenado em a0, ponteiro para result armazenado em s1
    # output: resultado salvo em result

    li t5, 10 
    
    li t3, 1000 # divisor
    div t4, a0, t3  # retirar um digito do numero e guardar o quociente
    rem a0, a0, t3  # guardar resto da divisao por 1000
    addi t4, t4, 48 # converter para string
    sb t4, 0(s1)    # escrever digito em result na ordem inversa   

    li t3, 100   
    div t4, a0, t3  # retirar um digito do numero e guardar o quociente
    rem a0, a0, t3  # guardar resto da divisao por 1000
    addi t4, t4, 48 # converter para string
    sb t4, 1(s1)    # escrever digito em result na ordem inversa   
    
    li t3, 10
    div t4, a0, t3  # retirar um digito do numero e guardar o quociente
    rem a0, a0, t3  # guardar resto da divisao por 1000
    addi t4, t4, 48 # converter para string
    sb t4, 2(s1)    # escrever digito em result na ordem inversa   
    
    li t3, 1
    div t4, a0, t3  # retirar um digito do numero e guardar o quociente
    rem a0, a0, t3  # guardar resto da divisao por 1000
    addi t4, t4, 48 # converter para string
    sb t4, 3(s1)    # escrever digito em result na ordem inversa   
    
    sb t5, 4(s1)
    ret

.bss
input_address: .skip 0x20  # buffer
result: .skip 0x20

# 0400 5337 2240 9166