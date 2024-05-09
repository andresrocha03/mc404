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

    # ler coordenadas 
    li a2, 12           # size - reads 12 bytes
    jal read
    mv s0, a1           # coord
    # obter numeros inteiros a partir da entrada
        # Xc
    jal get_coord 
    mv s2, a0
        # Yb
    addi s0, s0, 5 # atualizar ponteiros
    jal get_coord 
    mv s3, a0
    
    # ler tempos
    debug:
    li a2, 20          # size - reads 20 bytes
    jal read
    mv s0, a1           # TR, TA, TA, TB, TC   
        # Tr
    addi s0, s0,-1
    jal get_time
    mv s4, a0
        # Ta
    addi s0, s0, 5
    jal get_time
    mv s5, a0
        # Tb
    addi s0, s0, 5
    jal get_time
    mv s6, a0
        # Tc
    addi s0, s0, 5
    jal get_time
    mv s7, a0

    debug5:
    li t1, 3
    li t2, 10
    # calcular Da : (tr - ta) * 3/ 10
    sub s8, s4, s5
    mul s8, s8, t1
    div s8, s8, t2

    # calcular Db
    sub s9, s4, s6
    mul s9, s9, t1
    div s9, s9, t2

    # calcular Dc
    sub s9, s4, s7
    mul s9, s9, t1
    div s9, s9, t2

    # calcular y
    mul t1, s8, s8 # da²
    mul t2, s3, s3 # yb²
    mul t3, s9, s9 # db²
    li t5, 2
    mul t4, t5, s3
    add s10, t1, t2
    sub s10, s10, t3
    div s10, s10, t4

    # calcular x = (da²+xc²-dc²)/(2xc)
    mul t5, s2, s2 # Xc²
    mul t6, s9, s9 # dc²
    li t3, 2
    mul t2, t3, s2 # 2xc
    add s11, t1, t5
    sub s11, s11, t6
    div s11, s11, t2

    # salvar resposta em result (s1)
    la s1, result
    mv a0, s11
    jal save

    addi s1, s1, 5
    mv a0, s10
    jal save
     
    jal write
    li t4, 10
    sb t4, 5(s1)    # escrever digito em result 

    lw ra,0(sp)
    addi sp, sp, 4
    ret

read:

    li a0, 0            # file descriptor = 0 (stdin)
    la a1, input_address
    li a7, 63           # syscall read (63)
    ecall
   
    ret 

write:
    li a0, 1                # file descriptor = 1 (stdout)
    la a1, result           # buffer
    li a2, 20               # size - Writes 20 bytes.
    li a7, 64               # syscall write (64)
    ecall
    ret

get_digit:
    # input string em s0
    # output digitos da string em a0(sinal),a1,a2,a3,a4
    lbu a1, 1(s0)
    lbu a2, 2(s0)
    lbu a3, 3(s0)
    lbu a4, 4(s0)
    ret

to_decimal:
    # converter uma string para um numero decimal
    # input: 4 caracteres em a0, a1, a2, a3
    # output: numero inteiro em a0
    
    # converter string para int
    addi a1, a1, -48
    addi a2, a2, -48
    addi a3, a3, -48
    addi a4, a4, -48
    
    
    # multiplicar pelas potencias de 10
    li t5, 1000
    mul a1, a1, t5
    li t5, 100
    mul a2, a2, t5
    li t5, 10
    mul a3, a3, t5
    li t5, 1
    mul a4, a4, t5
    

    li a5, 0
    add a5, a5, a1
    add a5, a5, a2
    add a5, a5, a3
    add a5, a5, a4
    
    li t1, 45
    bne a0, t1, endif
        li t1, -1
        mul a5, a5, t1
    endif:
        li a0, 0
        mv a0, a5
    ret

get_coord:
    # ler uma string de 4 digitos com sinal, salva em s0
    # retorna numero inteiro em a0
    addi sp,sp,-4
    sw ra, 0(sp)

    # obter os digitos da string salva em s0, salvos em a0 (sinal), a1, a2, a3, a4
    lbu a0, 0(s0) # get sign
    jal get_digit

    # get int number from 4 str and save it in a0
    jal to_decimal 

    lw ra,0(sp)
    addi sp, sp, 4
    ret

get_time:
    # ler uma string de 4 digitos sem sinal, salva em s1
    # retorna numero inteiro em a0
    addi sp,sp,-4
    sw ra, 0(sp)
    debug1:
    # obter os digitos da string salva em s0, salva-los em a0 (sinal), a1, a2, a3, a4
    li a0, 43
    jal get_digit
    debug2:
    # get int number from 4 str and save it in a0
    jal to_decimal 
    debug3:
    lw ra,0(sp)
    addi sp, sp, 4
    ret

# sqrt:
    # calcular raiz
    # input: numero decimal salvo em a0
    # output: raiz quadrada aproximada em a0
#     li t1, 0    # i do for
#     li t2, 21   # limite do for
#    li t3, 0    # y/k
#    li t4, 0    # k 
#    li t5, 2    
    
#    div t4, a0, t5 # k = y/2
#    loop_sqrt:
#        bge t1, t2, lab_sqrt    # Sai do laço se i >= 21
#        div t3, a0, t4          # y/k
#        add t4, t4, t3          # k + y/k
#        div t4, t4, t5          # (k + y/k)/2
#        addi t1, t1, 1          # i <= i+1
#        j loop_sqrt

#    lab_sqrt:
#        mv a0, t4
#        ret


save:
    # salva um inteiro em result, como uma string no formato SDDDD
    # input: numero inteiro armazenado em a0, ponteiro para result armazenado em s1
    # output: resultado salvo em result

    li t1, 0
    li t4, 43
    bge t1, t4, menor # verificar se é maior ou igual que 0
        li t4, 45
    menor:
    sb t4, 0(s1)

    li t3, 1000     # divisor
    divu t4, a0, t3  # retirar um digito do numero e guardar o quociente
    rem a0, a0, t3  # guardar resto da divisao 
    addi t4, t4, 48 # converter para string
    sb t4, 1(s1)    # escrever digito em result   

    li t3, 100   
    divu t4, a0, t3  # retirar um digito do numero e guardar o quociente
    rem a0, a0, t3  # guardar resto da divisao 
    addi t4, t4, 48 # converter para string
    sb t4, 2(s1)    # escrever digito em result    
    
    li t3, 10
    divu t4, a0, t3  # retirar um digito do numero e guardar o quociente
    rem a0, a0, t3  # guardar resto da divisao 
    addi t4, t4, 48 # converter para string
    sb t4, 3(s1)    # escrever digito em result    
    
    li t3, 1
    divu t4, a0, t3  # retirar um digito do numero e guardar o quociente
    rem a0, a0, t3  # guardar resto da divisao 
    addi t4, t4, 48 # converter para string
    sb t4, 4(s1)    # escrever digito em result 
    
    
    ret

.bss
input_address: .skip 0x20  # buffer
result: .skip 0x20

