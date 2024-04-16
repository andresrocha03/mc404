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
    la a6, result

    # parametros do for
    li t6, 0
    li t7, 4
    li t5, 40 # 5 bytes

for:
    bge t6, t7, cont
    
    # atualizar ponteiro 
    muli t5, t6, 8  # t5 <= t6*8
    add a6, a6, t5  # a6 <= &result[0] + i*8 

    # salvei o input em a1
    jal read

    # salvar input em local seguro
    mv s0, a1
    
    # obter os digitos da string salva em s0
    jal get_digit

    # converter os 4 caracteres em 4 inteiros 
    jal string_to_int

    # get number from 4 int
    jal to_decimal 

    
    # converter int para string
    jal to_string    
    
    addi t6, t6, 1
    j for

cont: # o que colocal aqui ???????????

read:
    li a0, 0            # file descriptor = 0 (stdin)
    la a1, input_address # buffer
    li a2, 20           # size - Reads 20 bytes.
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

get_digit:
    # input string em s0
    # output digitos da string em a0,a1,a2,a3
    lbu a0, 0(s0)
    lbu a1, 1(s0)
    lbu a2, 2(s0)
    lbu a3, 3(s0)
    ret

str_to_int:
    # converter string para int
    # input: receber string de 4 digitos salvos em a0, a1, a2, a3
    # output: devolver inteiros em t1,t2,t3,t4
    addi t1, a0, -48
    addi t2, a1, -48
    addi t3, a2, -48
    addi t4, a3, -48
    ret

to_decimal:
    # multiplicar pelas potencias de 10
    # input: 4 inteiros salvos em t1,t2,t3,t4
    # output: numero inteiro em a0
    
    muli t1, t1, 1000
    muli t2, t2, 100
    muli t3, t3, 10
    muli t4, t4, 1
    
    li a0, 0

    add a0, t1
    add a0, t2
    add a0, t3
    add a0, t4
    ret


sqr_root:
    # calcular raiz
    # input: numero decimal salvo em a0
    # output: raiz quadrada aproximada em a0
    li t1, 0    # i do for
    li t2, 10   # limite do for
    li t3       # auxiliar
    li t4, 0    # k 

    div t4, a0, 2 #k = y/2

    for:
        bge t1, t2, cont    # Sai do laço se i >= 10
        div t3, a0, t4      # y/k
        add t4, t4, t3      # k + y/k
        div t4, t4, 2       # (k + y/k)/2
        addi t1, t1, 1      # i <= i+1
        j for
    mv a0, t4
    ret

to_string:
    # convert an int number into string
    # input: numero inteiro armazenado em a0, ponteiro para result armazenado em t1
    # output: numero em formato de string salvo em result
    
    