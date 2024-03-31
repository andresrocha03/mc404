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

void strcpy(char *string1, char *string2) {
    for (int i=0; i<strlen(string1); i++) {
        string1[i] = string2[i];
    }
}

int * chartoint(char string) {
    int result;
    result = string - '0';
    return result;
}



int atoint(char *string) {
    int result, number[50];
    int i=0;
    for (i=0; i<strlen(string); i++) {
        number[i] = string[i] - '0';
    }
    int len = sizeof(number)/sizeof(int);
    int exp = len-1;
    for (i=0; i<len; i++) {
       result += (number[i])*pow(10,exp); 
    }
    return result;
}

long long atoll(char *string) {
    long long result, number[50];
    int i=0;
    for (i=0; i<strlen(string); i++) {
        number[i] = string[i] - '0';
    }
    int len = sizeof(number)/sizeof(int);
    int exp = len-1;
    for (i=0; i<len; i++) {
       result += (number[i])*pow(10,exp); 
    }
    return result;
}

char * intoa (int number){
    char string[50];
    int i=0;
    while (number>0) {
        string[i] = number%10;
        number = number/10;
    }
    return string;
}

char * lltoa (long long number){
    char string[50];
    int i=0;
    while (number>0) {
        string[i] = number%10;
        number = number/10;
    }
    return string;
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


int char_is_bigger(char *number) {
    /*
    check if an number is bigger than 2147483647
    */

    char limit[] = {'2','1','4','7','4','8','3','6','4','7'};
    
    for (int i=0; i<strlen(number); i++) {
        if (number[i] > limit[i]) {
            return 1;           
        }
        else if (number[i] < limit[i]) {
            return 0;
        }
    }  
    return 0;
}

int is_bigger(long long number) {
    /*
    check if an number is bigger than 2147483647
    */
    if (number > 2147483647) {
        return 1;
    }
    return 0;
}


char* to_binary(char* snumber) {
    /* 
    converts a decimal number to its binary representation
    */
    char aux[50],answer[50];
    int nnumber,q,r,i=0;
    nnumber = atoint(snumber);    
    while (nnumber > 0) {
        aux[i] = nnumber%2 + '0';
        nnumber /= 2;
        i++;
    }
    //inverter resposta
    
    for (int j=strlen(aux)-1; j>=0; j--) {
        answer[i] = aux[j]; 
    }
    return answer;
}

char *to_decimal(char *number, char base[20]) {
    /* 
    converte um numero hexadecimal para decimal
    se for um numero decimal, retorna o próprio numero.
    */
    char sresult[50];
    int nvalue, expoent = strlen(number)-3; //subtrai 2 devido ao "0x", depois subtrai mais um para acessar corretamente os indices
    char auxvalue[2];
    long long  nresult; 

    if (base == 'd') {
        return number;
    }

    for (int i=2; i<strlen(*number); i++) {
        if (number[i] > 'A' && number[i] < 'Z') {
            strcpy(auxvalue,*convert_value(number[i]));
        }
        else { 
            strcpy(auxvalue,number[i]);
        }
        nvalue = chartoint(auxvalue);
        nresult += (nvalue)*pow(16,expoent);
        expoent--;
    }
    strcpy(sresult,intoa(nresult));
    return &sresult;
}


long long to_c2decimal(char *number) {
    /* 
    converte um número em complemento de 2 para decimal
    */
    
     
    long long diff, aux, result;
    if (char_is_bigger(number)) {
        aux = atoll(number);
        diff = aux - 2147483648;
        result = -2147483648 + diff;
        return result;

    }    

    return atoll;
}

char *change_endianness(char *number) {
    /* 
    converte um numero hexadecimal para decimal
    se for um numero decimal, retorna o próprio numero.
    */
    char sresult[50];
    int nvalue, expoent = strlen(number)-3; //subtrai 2 devido ao "0x", depois subtrai mais um para acessar corretamente os indices
    char auxvalue[2];
    long long  nresult; 

    for (int i=2; i<strlen(*number); i++) {
        if (number[i] > 'A' && number[i] < 'Z') {
            strcpy(auxvalue,*convert_value(number[i]));
        }
        else { 
            strcpy(auxvalue,number[i]);
        }
        nvalue = chartoint(auxvalue);
        nresult += (nvalue)*pow(16,expoent);
        expoent--;
    }
    strcpy(sresult,intoa(nresult));
    return &sresult;
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
    long long c2result;
    long long invdresult;
    
    dresult     = to_decimal(&number, base);
    bresult     = to_binary(&number);
    c2result    = to_c2decimal(&number);
    invdresult = change_endianness(&number);
    to_hexa(&number);
    to_octal(&number);

    /* Write n bytes from the str buffer to the standard output */
    write(STDOUT_FD, number, n);
    return 0;
}





/*
char *to_decimal(char *number, char base[20]) {
    char sresult[50];
    int nvalue, nresult, expoent = strlen(number)-3; //subtrai 2 devido ao "0x", depois subtrai mais um para acessar corretamente os indices
    char auxvalue[2];
    if (base == 'd') {
        return number;
    }
    for (int i=2; i<strlen(*number); i++) {
        if (number[i] > 'A' && number[i] < 'Z') {
            strcpy(auxvalue,*convert_value(number[i]));
        }
        else { 
            strcpy(auxvalue,number[i]);
        }
        nvalue = chartoint(auxvalue);
        nresult += (nvalue)*pow(16,expoent);
        expoent--;
    }
    strcpy(sresult,intoa(nresult));
    return &sresult;
}
*/
