int read(int __fd, const void *__buf, int __n){
    int ret_val;
  __asm__ __volatile__(
    "mv a0, %1           # file descriptor\n"
    "mv a1, %2           # buffer \n"
    "mv a2, %3           # size \n"
    "li a7, 63           # syscall write code (63) \n"
    "ecall               # invoke syscall \n"
    "mv %0, a0           # move return value to ret_val\n"
    : "=r"(ret_val)  // Output list
    : "r"(__fd), "r"(__buf), "r"(__n)    // Input list
    : "a0", "a1", "a2", "a7"
  );
  return ret_val;
}

void write(int __fd, const void *__buf, int __n)
{
  __asm__ __volatile__(
    "mv a0, %0           # file descriptor\n"
    "mv a1, %1           # buffer \n"
    "mv a2, %2           # size \n"
    "li a7, 64           # syscall write (64) \n"
    "ecall"
    :   // Output list
    :"r"(__fd), "r"(__buf), "r"(__n)    // Input list
    : "a0", "a1", "a2", "a7"
  );
}

void exit(int code)
{
  __asm__ __volatile__(
    "mv a0, %0           # return code\n"
    "li a7, 93           # syscall exit (64) \n"
    "ecall"
    :   // Output list
    :"r"(code)    // Input list
    : "a0", "a7"
  );
}

#define STDIN_FD  0
#define STDOUT_FD 1


void print(int numero) {
    int aux1=0, aux2=0, qtd=0;
    char digitos[40];


    if (numero == -2147483648) { 
        write(STDOUT_FD, "-2147483648\n", 12);
        //aqui é preciso setar manualmente pois nao é possivel fazer
        //aux1 = -numero nesse caso;
    }
    else if (numero ==0) {
        write(STDOUT_FD, "0\n", 12);
    }
    else {
        if (numero < 0) {
            write(STDOUT_FD,"-",1);
            aux1 = -numero; 
        }
        else aux1 = numero;

        aux2=aux1;
        while (aux2 > 0) { //contar qtd de digitos
            aux2 /= 10;
            qtd++;
        }
        
        aux2 = aux1;
        for (int i=qtd-1; i>=0; i--) { 
            digitos[i] = aux2%10 + '0'; //converter digitos de int para char
            // write(STDOUT_FD, &digitos[i], 20);
            // write(STDOUT_FD, "\n", 1);
            aux2 /= 10;
        }

        digitos[qtd] = '\n';
        digitos[qtd+1] = '\0';

        write(STDOUT_FD, digitos, qtd+2);
    }
}

void extract_numbers(char *numbers, int * values, int n)
{
    /*
    converter uma string numeros decimais
    */

    int digit, potencia = 1, result = 0, v=0, sign = 1;

    for (int i=0; i<= 24; i+=6) {
        if (numbers[i] == '-') { //se o numero for negativo salvo o sinal em sign
            sign = -1;
        }
        for (int j=i+4; j>i; j--) {
            digit = numbers[j] - '0';
            result += digit*potencia;
            potencia *= 10; 
        }
        values[v] = result*sign;
        v++;
        potencia = 1;
        result = 0;
        sign = 1;
    }   
}

int operate(int * values) {
    int first=0, second=0, third=0, fourth=0, fifth=0;
    int result = 0;
    
    result   |= (values[0]    &         0b11111) << 0;
    result   |= (values[1]    &         0b1111111) << 5;
    result   |= (values[2]    &         0b111111111) << 12;
    result   |= (values[3]    &         0b1111) << 21;
    result   |= (values[4]    &         0b1111111) << 25;
    
    return result;
}

void hex_code(int value){ 
        char hex[11];
        unsigned int uval = (unsigned int) value, aux;

        hex[0] = '0';
        hex[1] = 'x';
        hex[10] = '\n';

        for (int i = 9; i > 1; i--){
            aux = uval % 16;
            if (aux >= 10)
                hex[i] = aux - 10 + 'A';
            else
                hex[i] = aux + '0';
            uval = uval / 16;
        }
        write(1, hex, 11);
    }



int main()  {
    
    //agrupar bits para cada valor no vetor 
    //printar resultado oem hexadecimal

    int n, values[5];
    char input[35];

    n = read(STDIN_FD, input, 35);

    extract_numbers(input, values, n);

    int result = operate(values);

    hex_code(result);
    


    return 0;
}






void _start()
{
  int ret_code = main();
  exit(ret_code);
}

