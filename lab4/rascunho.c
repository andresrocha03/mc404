#include <stdio.h>

int poww(int base, int exp) {
    int result=1;
    for (int i=0;i<exp;i++) {
        result *= 16; 
    }
    return result;
}



int strleng(char *string) {
    char aux;
    int i = 0;
    while (aux != '\0') {
        aux = string[i];
        i++;
    }
    return i;

}

void strcopy(char *string1, char *string2) {
    for (int i=0; i<strleng(string1); i++) {
        string1[i] = string2[i];
    }
}

int chartoint(char string) {
    int result;
    result = string - '0';
    return result;
}

char * check_base(char * number, char *base) {
    if (number[0] == '0' && number[1] == 'x') {
        strcopy(base,"hexadecimal");
        return base;
    }
    strcopy(base,"decimal");
    return base;

}

long long convert_valuell(char letter) {
    char hex[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    long long i=0;
    for (i=0;i<16;i++) {
        if (letter == hex[i]) {
            break;
        }
    }
    return i;
}

long long convert_valueint(char letter) {
    char hex[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    int i=0;
    for (i=0;i<16;i++) {
        if (letter == hex[i]) {
            break;
        }
    }
    return i;
}

int atoint(char *string) {
    int result, number[50];
    int i=0;
    
    for (i=0; i<strleng(string); i++) {
        number[i] = string[i] - '0';
    }
    int len = sizeof(number)/sizeof(int);
    int exp = len-1;
    for (i=0; i<len; i++) {
       result += (number[i])*poww(10,exp); 
    }
    return result;
}

long long atoll(char *string) {
    long long result, number[50];
    int i=0;
    //hex number
    char base[50];
    check_base(string,base); 
    if (base[0] == 'h') {
        for (i=2; i<strleng(string); i++) {
            number[i] = convert_valuell(string[i]);
        }
        int len = sizeof(number)/sizeof(long long);
        int exp = len-1;
        for (i=0; i<len; i++) {
            result += (number[i])*poww(16,exp); 
        }    
        return result;
    }
    //decimal number
    for (i=0; i<strleng(string); i++) {
        number[i] = string[i] - '0';
    }
    int len = sizeof(number)/sizeof(int);
    int exp = len-1;
    for (i=0; i<len; i++) {
       result += (number[i])*poww(10,exp); 
    }
    return result;
}

char * intoa (int number, char *string){
    int i=0;
    while (number>0) {
        string[i] = number%10;
        number = number/10;
    }
    return string;
}

char reconvert_value(int number) {
    char letter = ' ';
    if (number == 10) {
        letter = 'A';
    }
    else if (number == 11) {
        letter = 'B';
    }
    else if (number == 12) {
        letter = 'C';
        
    }
    else if (number == 13) {
        letter = 'D';
        
    }
    else if (number == 14) {
        letter = 'E';
        
    }
    else if (number == 15) {
        letter = 'F';
    }
    else {
        letter = number + '0';
    }
    return letter;
}

int char_is_bigger(char *number) {
    /*
    check if an number is bigger than 2147483647
    */

    char limit[] = {'2','1','4','7','4','8','3','6','4','7'};
    for (int i=0; i<strleng(number); i++) {
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
    
    for (int j=strleng(aux)-1; j>=0; j--) {
        answer[i] = aux[j]; 
    }
    return answer;
}

char* ato_decimal(char *number, char base[20]) {
    /* 
    converte um numero hexadecimal para decimal
    se for um numero decimal, retorna o próprio numero.
    */
    char sresult[50];
    int nvalue, expoent = strleng(number)-3; //subtrai 2 devido ao "0x", depois subtrai mais um para acessar corretamente os indices
    char auxvalue[2];
    long long  nresult; 

    if (base == 'd') {
        return number;
    }

    for (int i=2; i<strleng(*number); i++) {
        if (number[i] > 'A' && number[i] < 'Z') {
            nvalue = convert_valueint(number[i]);
            nresult += (nvalue)*poww(16,expoent);
            expoent--;
    }
    char auxstring[50];
    strcopy(sresult,intoa(nresult,auxstring));
    return sresult;
}


long long ato_c2decimal(char *number) {
    /* 
    converte um número decimal em complemento de 2 para decimal
    */
    
    long long diff, aux, result;
    if (char_is_bigger(number)) {
        aux = atoll(number);
        diff = aux - 2147483648;
        result = -2147483648 + diff;
        return result;

    }    

    return atoll(number);
}

unsigned int uito_decimal(unsigned int number) {
    unsigned int result;
    int aux[50], i=0;
    while (number>0) {
        aux[i] = number%10;
        number = number/10;
        i++;
    }
    int exp = i-1;
    for (int j=0; j<i; j++) {
        result = aux[i]*poww(16,exp);
        exp--;
    }
    return result;
}

unsigned int change_endianness(char *number) {
    /* 
    inverter bytes do numero recebido, devolver numero com endianess trocado
    */
    long long llnumber;
    long long leftmost_byte, leftmiddle_byte, rightmiddle_byte, rightmost_byte;
    
    llnumber = atoll(number);

    leftmost_byte    = (llnumber & 0x000000FF) >> 00;
    leftmiddle_byte  = (llnumber & 0x0000FF00) >> 8;
    rightmiddle_byte = (llnumber & 0x00FF0000) >> 16;
    rightmost_byte   = (llnumber & 0xFF000000) >> 24; 
    
    leftmost_byte <<= 24;
    leftmiddle_byte <<= 16;
    rightmiddle_byte <<= 8;
    rightmost_byte <<= 0;

    long long result = (leftmost_byte | leftmiddle_byte | 
                        rightmiddle_byte | rightmost_byte);
    return result;
}  


int * to_c2hex(char* string,int *vresult) {
    int diff, vaux[50], i=0;
    unsigned int aux=0; 
    long long nnumber;
    //fazer diff = number - 2147483647
    //fazer aux = diff + 2147483647
    //converter aux para hex

    nnumber = atoll(string);
    diff = nnumber - 2147483647;
    aux = diff + 2147483647;
    
    while (aux > 0) {
        vaux[i] = aux%16;
        aux /= 16;
        i++;
    }

    //inverter resposta
    int k = 0;
    for (int j=i-1; j>=0; j--) {
        vresult[k] = reconvert_value(vaux[i]);
        k++;
    }
    return vresult;    
}

int * to_octal(char *string,char *base, int *vresult) {
    if (base[0]== 'd') {

        unsigned int aux, diff;
        int vaux[50],i=0;
        long long nnumber;
    

        nnumber = atoll(string);
        diff = nnumber - 2147483647;
        aux = diff + 2147483647;

        aux = atoll(string);
        while (aux > 0) {
            vaux[i] = aux%8;
            aux /= 8;
            i++;
        }

        //inverter resposta
        int k = 0;
        for (int j=i-1; j>=0; j--) {
            vresult[k] = vaux[i];
            k++;
        }
        return vresult;
    }
    
    char * decvalue;
    long long c2value, nnumber; 
    decvalue = ato_decimal(string,base);
    c2value = ato_c2decimal(decvalue);
    unsigned int aux;
    int vaux[50],i=0, vresult[50];
    
    nnumber = atoll(string);
    int diff = nnumber - 2147483647;
    aux = diff + 2147483647;

    while (aux > 0) {
        vaux[i] = aux%8;
        aux /= 8;
        i++;
    }

    //inverter resposta
    int k = 0;
    for (int j=i-1; j>=0; j--) {
        vresult[k] = vaux[i];
        k++;
    }
    return vresult;


    
}


int main()
{
    char number[50];

    /* Read up to 20 bytes from the standard input into the str buffer */
    int n = scanf("%s", number);

    char base[20];; 
    char * dresult, *bresult, *auxc2;
    int *hexresult, *oresult;

    long long c2result;
    
    unsigned int invdresult;
    
    check_base(number,base);

    dresult     =  ato_decimal(number, base);
    printf("%s\n", dresult);
    bresult     = to_binary(number);
    printf("%s\n", bresult);
    auxc2       = ato_decimal(number, base);
    c2result    = ato_c2decimal(auxc2);
    printf("%lli\n", c2result);
    invdresult  = change_endianness(number);
    invdresult  = uito_decimal(invdresult); 
    printf("%d\n", invdresult);
    if (base[0] == 'h') {
        //write number
        printf("%s\n", number);        
    }
    else { 
        //hexresult = to_c2hex(number,hexresult);
        //printf("%d\n", hexresult);
    }
    

    //oresult = to_octal(number,base,oersult);

    return 0;
}

