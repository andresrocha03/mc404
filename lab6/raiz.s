.globl _start

_start:
    jal main
    li a0, 0
    li a7, 93 # exit
    ecall

.data:
    input_address: .skip 0x20  # buffer
    answer: .skip 0x4

.text:

main:
    #salvei o input em a1
    jal read

    #salvar input em local seguro
    mv s0, a1
    
    #obter os digitos da string salva em a1
    jal get_digit

    #converter os 4 caracteres em 4 inteiros 
    jal string_to_int

    #get number from 4 int
    jal to_decimal 
   

    #converter int para string



    result: .skip 0x20    

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
    #input string em s0
    #output digitos da string em a0,a1,a2,a3
    lbu a0, 0(s0)
    lbu a1, 1(s0)
    lbu a2, 2(s0)
    lbu a3, 3(s0)
    ret

str_to_int:
    #converter string para int
    #input: receber string de 4 digitos salvos em a0, a1, a2, a3
    #output: devolver inteiros em a4,a5,a6,a7
    addi a4, a0, -48
    addi a5, a1, -48
    addi a6, a2, -48
    addi a7, a3, -48
    ret

to_decimal:
    #multiplicar pelas potencias de 10
    #input: 4 inteiros salvos em a4,a5,a6,a7
    #output: numero inteiro em a0
    muli t1, t1, 1000
    muli t2, t2, 100
    muli t3, t3, 10
    muli t4, t4, 1
    ret


sqr_root:
     #calcular raiz
    li a6, 0 #i do for
    li a7, 10 #limite do for
    li t1 #k
    li t2, 0

    div t1, a5, 2 #k = y/2

    for:
        bge a6, a7, cont    # Sai do laço se i >= 10
        div t2, a5, t1      # y/k
        add t2, t1, t2      # k + y/k
        div t2, t2, 2       # (k + y/k)/2
        addi a6, a6, 1 # i <= i+1
        j for
    ret

to_string:
    