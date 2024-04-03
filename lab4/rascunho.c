#include <stdio.h>

long long poww(long long base, long long exp) {
    long long result=1;
    for (int i=0;i<exp;i++) {
        result *= base; 
    }
    return result;
}



int strleng(char* string) {
    int i = 0;
    while (*string++) {
        i++;
    }
    return i;

}

void strcopy(char *string1, char *string2) {
    for (int i=0; i<strleng(string2); i++) {
        string1[i] = string2[i];
    }
}


int chartoint(char string) {
    int result;
    result = string - '0';
    return result;
}

char  check_sign(char * number) {
    char sign;
    if (number[0] == '-') {
        sign = 'n';
        return sign;
    }
    char aux[20]; 
    sign = 'p';
    return sign;
}


char  check_base(char * number) {
    char base;
    if (number[1] == 'x') {
        base = 'h';
        return base;
    }
    char aux[20]; 
    base = 'd';
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

int convert_valueint(char letter) {
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
    long long result=0, number[50];
    int i=0;
    char base, sign;
    
    base = check_base(string); 
    sign = check_sign(string);
    //hex number
    if (base == 'h') {
        printf("number: %s", string);
        for (i=2; i<strleng(string); i++) {
            number[i] = convert_valuell(string[i]);
            //printf("number vector: %lli\n",number[i]);
        }
        int len = i;
        int exp = len-1;
        for (i=0; i<len; i++) {
            result += (number[i])*poww(16,exp); 
        }    
        return result;
    }

    //decimal number
    int k;
    if (sign == 'p') k = 0;
    else k = 1;
    for (i=k; i<strleng(string); i++) {
        number[i] = string[i] - '0';
    }
    int len = i;
    int exp = len-1;
    for (i=0; i<len; i++) {
       //printf("number vector: %lli\n",number[i]);
       result += (number[i])*poww(10,exp); 
       exp--;
    }
    if (k==1) result *= -1; 
    return result;
}

char * lltoa (long long number, char *string){
    int i=0;
    char stringaux[50];
    //printf("number: %d\n",number);
    while (number>0) {
        stringaux[i] = number%10  + '0';
        //printf("number10: %lli\n",number%10);
        number = number/10;
        i++;
    }
    //stringaux[i] = '\0';
    //printf("STRINGaux: %s\n",stringaux);
    //inverter resposta
    int k=0;
    for (int j=i-1; j>=0; j--) {
        //printf("STRINGauxchar: %c\n",stringaux[j]);
        string[k] = stringaux[j]; 
        k++;
    }
    //printf("STRING: %s",string);
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
    if (strleng(number) > 10) {
        return 1;
    } 
    if (strleng(number) == 10) {
        for (int i=0; i<strleng(number); i++) {
            if (number[i] > limit[i]) {
                return 1;           
            }
            else if (number[i] < limit[i]) {
                return 0;
            }
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


void to_binary(long long number, char* answer) {
    /* 
    converts a decimal number to its binary representation
    */
    char aux[100];
    int q,r=0,i=0;

    while (number > 0) {
        aux[i] = number%2 + '0';
        //printf("aux[i]: %c\n", aux[i]);
        number /= 2;
        i++;
    }
    aux[i] = '\0';
    //inverter resposta
    for (int j=strleng(aux)-1; j>=0; j--) {
        answer[r] = aux[j]; 
        r++;
    }
    answer[r] = '\0';
}

char* ato_decimal(char *number, char base, char* sresult) {
    /* 
    converte um numero hexadecimal para decimal
    se for um numero decimal, retorna o próprio numero.
    */
    int nvalue, exp = strleng(number)-3; //subtrai 2 devido ao "0x", depois subtrai mais um para acessar corretamente os indices
    char auxvalue[2];
    long long  nresult=0; 
    char auxstring[50];

    if (base == 'd') {
        strcopy(sresult,number);
    }
    else {
        for (int i=2; i<strleng(number); i++) {
            nvalue = convert_valuell(number[i]);
            //printf("dec: %d|",nvalue);
            //printf("exp: %d|",exp);
            //printf("poww: %lli|",poww(16,exp));
            //printf("conta: %lli\n",nvalue*poww(16,exp));
            nresult += (nvalue)*poww(16,exp);
            exp--;
        }
        lltoa(nresult,auxstring);
        strcopy(sresult,auxstring);
    }
    
}


long long ato_c2decimal(char *number) {
    /* 
    converte um número decimal em complemento de 2 para decimal
    */
    //printf("NUMBER: %s\n", number);
    char sign = check_sign;

    long long diff, aux, result;
    if (char_is_bigger(number) && sign =='p') {
        //printf("ISBIGGER\n");
        aux = atoll(number);
        diff = aux - 2147483648;
        //printf("DIFF: %lli", diff);
        result = -2147483648 + diff;
        return result;

    }    
    else if (sign=='n') {
        
    }

    long long answer = atoll(number);
    return answer;
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

int * to_octal(char *string,char base, int *vresult) {
    if (base== 'd') {

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
    ato_decimal(string,base,decvalue);
    c2value = ato_c2decimal(decvalue);
    unsigned int aux;
    int vaux[50],i=0;
    
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
    scanf("%s", number);

    char base, dresult[40], bresult[100]; 
    int *hexresult, *oresult;

    long long c2result;
    
    unsigned int invdresult;
    
    
    base = check_base(number);

    printf("%c\n", base);
    ato_decimal(number, base, dresult);
    printf("dresult: %s\n", dresult);

    c2result = ato_c2decimal(dresult);
    printf("%lli\n", c2result);

    to_binary(c2result,bresult);
    printf("%s\n", bresult);
    
    //c2result    = ato_c2decimal(auxc2);
    //printf("%lli\n", c2result);
    //invdresult  = change_endianness(number);
    //invdresult  = uito_decimal(invdresult); 
    //printf("%d\n", invdresult);
    if (base == 'h') {
        //write number
    //    printf("%s\n", number);        
    }
    else { 
        //hexresult = to_c2hex(number,hexresult);
        //printf("%d\n", hexresult);
    }
    

    //oresult = to_octal(number,base,oersult);

    return 0;
}

