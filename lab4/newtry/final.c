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
    long long aux=numero, qtd=0;
    char digito[40];

    while (aux > 0) {
        aux /= 10;
        qtd++;
    }
    
    aux = numero;
    for (int i=qtd-1; i>=0; i--) {
        digito[i] = aux%10 + '0';
        aux /= 10;
    }
    write(STDOUT_FD, digito, qtd);
    write(STDOUT_FD, "\n", 1);
}


char check_sign(char *number)
{
    char sign;
    if (number[0] == '-')
    {
        sign = 'n';
        return sign;
    }
    sign = 'p';
    return sign;
}

char check_base(char *number)
{
    char base;
    if (number[1] == 'x')
    {
        base = 'h';
        return base;
    }
    base = 'd';
    return base;
}


int convert_value(char letter)
{
    char hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    long i = 0;
    for (i = 0; i < 16; i++)
    {
        if (letter == hex[i])
        {
            break;
        }
    }
    return i;
}

unsigned int to_decimal(char *number, char base, int n)
{
    /*
    converter uma string para um numero decimal em complemento de 2
    */

    int digit; 
    unsigned int potencia = 1;
    char auxvalue[2];
    unsigned int result = 0; 
    int j=0;
    char auxstring[50];

    if (base == 'd')
    {
        if (number[0] == '-') {
            j = 1;
        }
        for (int i=n-2; i>=j; i--) {
            digit = number[i] - '0';
            result += digit*potencia;
            potencia *= 10; 
        }
    }
    else {
        for (int i = n-2; i >= 2; i--) {
            digit = convert_value(number[i]);
            result += (digit)*potencia;
            potencia *= 16;
        }
    }
    return result;
}

int to_c2(unsigned int number)
{
    /*
    converte um número decimal para complemento de 2
    */


    int diff=0; 
    int result;
    if (number > 2147483647)
    {
        diff = number - 2147483648;
        result = -2147483648 + diff;
        return result;
    }
    else if (number < -2147483648)
    {
        diff = number + 2147483648;
        result = 2147483648 + diff;
        return result;
    }
    else result = number;
    return result;
}

void printn() {
    write(STDOUT_FD,"\n",1);
}


char * to_binary (char *numero, char base) {
    
} 

int main() {
    char entrada[40], base, sign;
    int resposta2;
    unsigned int decimal;
    int n = read(STDIN_FD, entrada, 40);
    char resposta2c[40];
    
    base = check_base(entrada);

    decimal = to_decimal(entrada, base, n);
    resposta2 = to_c2(decimal);
    
    //resposta1
    //resposta2
    if (base =='d' & check_sign(entrada)=='n') {
        write(STDOUT_FD,"-", 1);
        print(resposta2);
    }
    else {
        print(resposta2);
    }
    //resposta3
    //resposta4
    //resposta5
    
    
}


void _start()
{
  int ret_code = main();
  exit(ret_code);
}