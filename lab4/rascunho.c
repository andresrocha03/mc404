#include <stdio.h>

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

char * intoa (int number){
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


char *to_decimal(char *number, char base[20]) {
    /* 
    converte um numero hexadecimal para decimal
    se for um numero decimal, retorna o próprio numero.
    */
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


char* to_hexadecimal() {

}

char* to_octal() {

}


int main()
{
    char number[32];

    /* Read up to 20 bytes from the standard input into the str buffer */
    
    scanf("%d", &number);


    char base[20] = check_base(&number); 
    char * dresult, *bresult, *c2result;

    dresult     = to_decimal(&number, base);
    bresult     = to_binary(&number);
    //c2result    = to_c2decimal(&number);
    //change_endianness(&number);
    //to_hexa(&number);
    //to_octal(&number);

    printf("%s\n", bresult);
   

    /* Write n bytes from the str buffer to the standard output */
    return 0;
}