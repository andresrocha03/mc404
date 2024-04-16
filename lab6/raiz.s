.globl _start

_start:
    jal main
    
    li a0, 0
    li a7, 93 # exit
    ecall

.data:
    input_address: .skip 0x20  # buffer
    result: .skip 0x20

.text:

main:
    # ponteiro para a resposta 
    la s1, result

    # parametros do for
    li s2, 0    # i = 0 
    li s3, 4    # limite do for
    li s4, 5   # 5 bytes

    # salvei o input em s0
    addi sp,sp,-4
    sw ra, 0(sp)
    jal read
    jal loop_main
    jal write # write result

loop_main:
    bge s2, s3, lab_main # if i <= 4

    # atualizar ponteiro do input
    li t1, 1
    mul t1, s2, s4  # t1 = i*5 bytes
    add s0, s0, t1  # s1 <= &input_addres[s0] + 5*i 

    # atualizar ponteiro do result
    li t1, 1
    mul t1, s2, s4  # t1 = i*5 bytes
    add s1, s1, t1  # s1 <= &input_addres[s0] + 5*i 

    # obter os digitos da string salva em s0
    addi sp,sp,-4
    sw ra, 0(sp)
    jal get_digit

    # get int number from 4 str
    addi sp,sp,-4
    sw ra, 0(sp)
    jal to_decimal 

    # calcular raiz quadrada
    addi sp,sp,-4
    sw ra, 0(sp)
    jal sqrt 

    # salvar resposta em result
    addi sp,sp,-4
    sw ra, 0(sp)
    jal save

    addi s2, s2, 1

    j loop_main

lab_main: 
    ret

read:

    li a0, 0            # file descriptor = 0 (stdin)
    la s0, input_address# buffer
    li a2, 20           # size - Reads 20 bytes.
    li a7, 63           # syscall read (63)
    ecall
    lw ra,0(sp)
    addi sp, sp, 4
    ret 

write:
    li a0, 1            # file descriptor = 1 (stdout)
    la a1, t1           # buffer
    li a2, result       # size - Writes 20 bytes.
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
    lw ra,0(sp)
    addi sp, sp, 4
    ret

to_decimal:
    # converter uma string para um numero decimal
    # input: 4 inteiros salvos em t1,t2,t3,t4
    # output: numero inteiro em a0
    
    # converter string para int
    addi t1, a0, -48
    addi t2, a1, -48
    addi t3, a2, -48
    addi t4, a3, -48
    
    # multiplicar pelas potencias de 10
    muli t1, t1, 1000
    muli t2, t2, 100
    muli t3, t3, 10
    muli t4, t4, 1
    
    li a0, 0

    add a0, t1
    add a0, t2
    add a0, t3
    add a0, t4

    lw ra,0(sp)
    addi sp, sp, 4
    ret


sqrt:
    # calcular raiz
    # input: numero decimal salvo em a0
    # output: raiz quadrada aproximada em a0
    li t1, 0    # i do for
    li t2, 10   # limite do for
    li t3, 0       # auxiliar
    li t4, 0    # k 

    div t4, a0, 2 #k = y/2

loop_sqrt:
    bge t1, t2, lab_sqrt    # Sai do laço se i >= 10
    div t3, a0, t4      # y/k
    add t4, t4, t3      # k + y/k
    div t4, t4, 2       # (k + y/k)/2
    addi t1, t1, 1      # i <= i+1
    j loop_sqrt


lab_sqrt:
    mv a0, t4
    lw ra,0(sp)
    addi sp, sp, 4
    ret

save:
    # salva um inteiro em result, como uma string no formato DDDD
    # input: numero inteiro armazenado em a0, ponteiro para result armazenado em s1
    # output: resultado salvo em result

    li t1, 0 # i = 0
    li t2, 4 # limite do for
    li t3, 10
    li t4, 48
    addi s1, s1, 3 # somar 3 bytes, ou seja, 3 digitos para deslocar até o fim do número
    la t5, s1

initialize_zeros:
    sb t4, 0(t5)         # Inicializa com '0'
    addi t5, t5, -1      # Decrementa o endereço de t5
    addi t2, t2, -1      # Decrementa o contador
    bnez t2, initialize_zeros # Continua inicialização se t2 != 0

loop_save:
    blt t1, t2, lab_save
    rem t4, a0, t3  # guardar resto da divisao por 10
    div a0, a0, t3  # retirar um digito do numero e guardar o quociente
    addi t4, t4, 48 # converter para string
    sb t4, 0(s1)    # escrever digito em result na ordem inversa   
    addi s1, s1, -1

lab_save: ret