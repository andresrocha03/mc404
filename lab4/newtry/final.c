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

void printn() {
    write(STDOUT_FD,"\n",1);
}




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

void printui(unsigned int numero) {
    unsigned int aux1=0, aux2=0, qtd=0;
    char digitos[40];

    
    if (numero ==0) {
        write(STDOUT_FD, "0\n", 12);
    }
    else {
        aux1 = numero;

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
    char hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
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

char reconvert_value(int number)
{
    char letter;
    char hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    letter = hex[number];
    return letter;
}

int to_decimal(char *number, char base, int n)
{
    /*
    converter uma string para um numero decimal em complemento de 2
    */

    int digit, potencia = 1, result = 0, j=0, sign = 1;

    if (base == 'd') { //se a base for decimal 
        if (number[0] == '-') { //se o numero for negativo ignoro o sinal de -
            j = 1;
            sign = -1;
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
    
    return result*sign;
}

int to_c2(int decimal) {
    int numero = 0;
    int res = 0;

    if (decimal < 0) numero = (-decimal) - 1;
    else numero = decimal;

    for (int i=0; i<32; i++) {
        if (!(numero & (1<<i))) {
            res = res | (1<<i);
        } 
    }
    
    return numero;
}



void print_binary (int numero) {
    write(STDOUT_FD, "0b", 2);
    int i = 31;
    char binary[40];

    //encontrar o primeiro 1 nos 32 bits
    for (; i>=0; i--) {  //percorrer os bits
        if ((numero & (1<<i))) { 
            break; //break ao encontrar o 1; o indice i guarda a posicao do primeiro 1
        } 
    }
    for (int j=i; j>=0; j--) { //iterar a partir do primeiro i
        if (!(numero & (1<<j))) {
            write(STDOUT_FD,"0",1);
        } 
        if ((numero & (1<<j))) {
            write(STDOUT_FD,"1",1);
        } 
    }
    write(STDOUT_FD,"\n",1);
} 


unsigned int change_endiannes(int numero) {
    unsigned int lmostbyte=0, lmiddlebyte=0, rmiddlebyte=0, rmostbyte=0;
    unsigned int res;
    
    // if (numero >= 0) uinumero = numero;
    // else if (numero < 0) {
    //     uinumero = numero + 2147483648 + 2147483648;  
    // }

    
    lmostbyte = (numero & 0x000000FF) >> 00;
    lmiddlebyte = (numero & 0x0000FF00) >> 8;
    rmiddlebyte = (numero & 0x00FF0000) >> 16;
    rmostbyte = (numero & 0xFF000000) >> 24;

    lmostbyte <<= 24;
    lmiddlebyte <<= 16;
    rmiddlebyte <<= 8;
    rmostbyte <<= 0;
 
 
    res = (lmostbyte | lmiddlebyte
            | rmiddlebyte | rmostbyte);
 
    return res;

}

void print_hex (int numero) {
    /*
    receber um numero decimal em complemento de 2
    printar seu valor em hexadecimal
    */
    int potencia=1,dresult=0;
    char hresult; 
    int nibble, j = 9,bit;
    char hex[40], resposta[40];

    hex[0] = '0';
    hex[1] = 'x';


    for (int k=0; k<8; k++) { // iterar de nibble em nibble
        dresult = 0;
        potencia = 1;
        nibble = (numero>>4*k) & 15; 
        hresult = reconvert_value(nibble); //passar valor decimal para hex
        hex[j] = hresult;
        j--;
    }
    hex[10] = '\n';
    hex[11] = '\0';

    resposta[0] = '0';
    resposta[1] = 'x';

    int i,r=2;
    for (i=2; hex[i] != '\0'; i++) { //tirar zeros à esquerda
        if (hex[i] != '0') break;
    }

    for (int k=i; hex[k] != '\0'; k++) {//tirar zeros à esquerda
        resposta[r] = hex[k];
        r++;
    }
    resposta[r] = '\0';

    write(STDOUT_FD,resposta, 1+r);
}

void print_octal (int numero) {
    /*
    receber um numero decimal em complemento de 2
    printar seu valor em hexadecimal
    */
    int potencia=1;
    char oresult; 
    int bits, j = 12,bit;
    char oct[40], resposta[40];

    oct[0] = '0';
    oct[1] = 'o';

    for (int k=0; k<11; k++) { // iterar de bits em bits
        if (k != 10) {
            potencia = 1;
            bits = (numero>>3*k) & 7; 
            oct[j] = bits + '0';
            j--;
        }
        else {
            if (numero & (1<<31)) { // se o ultimo bit for 1
                if (!(numero & (1<<30))) { //se o penultimo bit for 0
                    oct[j] = '2';
                }
                else {          
                oct[j] = '3';
                }
            }
            if (!(numero & (1<<31))) { // se o ultimo bit for 0
                if (!(numero & (1<<30))) { //se o penultimo bit for 0
                    oct[j] = '0';
                }
                else { //penultimo bit é 1
                    oct[j] = '1';
                }

            } 
        }
        
    }
    oct[13] = '\n';
    oct[14] = '\0';
    
    resposta[0] = '0';
    resposta[1] = 'o';

    int i,r=2;
    for (i=2; oct[i] != '\0'; i++) { //tirar zeros à esquerda
        if (oct[i] != '0') break;
    }

    for (int k=i; oct[k] != '\0'; k++) {//tirar zeros à esquerda
        resposta[r] = oct[k];
        r++;
    }
    resposta[r] = '\0';

    write(STDOUT_FD, resposta, 20);
    
}




int main() {
    char entrada[40], base, sign;
    int  twocomp, decimal, n, x=100;
    unsigned int resposta3=0;
    n = read(STDIN_FD, entrada, 40);
    
    base = check_base(entrada);

    decimal = to_decimal(entrada, base, n);
    
    //if (decimal == -2147483648)  ; 
    //twocomp = to_c2(decimal);
    
    ////resposta1
        print_binary(decimal);
    ////resposta2
        print(decimal);
    //resposta3
        resposta3 = change_endiannes(decimal);
        printui(resposta3);
    //resposta4
        print_hex(decimal);
    //resposta5
        print_octal(decimal);
    
    
}

void _start()
{
  int ret_code = main();
  exit(ret_code);
}