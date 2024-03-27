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

void _start()
{
  int ret_code = main();
  exit(ret_code);
}

#define STDIN_FD  0
#define STDOUT_FD 1


int strlen(char *string) {
    char aux;
    int i = 0;
    while (aux != '\0') {
        aux = string[i];
        i++;
    }
    return i;

}

void strcpy() {

}

void atoi() {

}

void itoa (){

}



char * check_base(char * number) {
    char base[20];
    if (number[0] == '0' && number[1] == 'x') {
        strcpy(base,"hexadecimal");
        return &base;
    }
    else {
        strcpy(base,"decimal");
        return &base;
    }

}

char * convert_value(char letter) {
    char number[2] = ' ';
    if (letter == 'A') {
        number[0] = '1';
        number[1] = '0';
    }
    if (letter == 'B') {
        number[0] = '1';
        number[1] = '1';
    }
    if (letter == 'C') {
        number[0] = '1';
        number[1] = '2';
    }
    if (letter == 'D') {
        number[0] = '1';
        number[1] = '3';
    }

    if (letter == 'E') {
        number[0] = '1';
        number[1] = '4';
    }
    if (letter == 'F') {
        number[0] = '1';
        number[1] = '5';
    }

    return number;
}


char* to_decimal(char *number, char base[20]) {
    char sresult[50];
    int nvalue, nresult, expoent = strlen(number)-3; //subtrai 2 devido ao "0x", depois subtrai mais um para acessar corretamente os indices
    char auxvalue[2];
    if (strcmp(base,"decimal")) { //checar como funciona
        return number;
    }
    for (int i=2; i<strlen(*number); i++) {
        if (number[i] > 'A' && number[i] < 'Z') {
            strcpy(auxvalue,*convert_value(number[i]));
        }
        else { 
            strcpy(auxvalue,number[i]);
        }
        atoi(auxvalue,nvalue,10);
        nresult += (nvalue)*pow(16,expoent);
        expoent--;
    }
    itoa(nresult,sresult,10);
    return &sresult;
}


char* to_binary(char* snumber) {
    /* 
    converts a decimal number to its binary representation
    */
    char ianswer[20],answer[20];
    int nnumber,q,r,i=0;
    atoi(snumber, nnumber, 10);    
    while (nnumber >= 2) {
        answer[i] = nnumber%2 + '0';
        nnumber /= 2;
        i++; 
    }
    answer[i+1] = nnumber + '0';
    //inverter resposta
    for (int j=strlen(ianswer)-1; j>=0; j--) {


    }
}

char* to_hexadecimal() {

}

char* to_octal() {

}


int main()
{
    char number[32];

    /* Read up to 20 bytes from the standard input into the str buffer */
    int n = read(STDIN_FD, number, 32);

    char base[20] = check_base(&number); 
    char * dresult, *bresult;

    dresult = to_decimal(&number, base);
    bresult = to_binary(&number);
    to_decimal(&number);
    change_endianness(&number);
    to_hexa(&number);
    to_octal(&number);



    /* Write n bytes from the str buffer to the standard output */
    write(STDOUT_FD, number, n);
    return 0;
}