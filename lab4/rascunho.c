#include <stdio.h>

long long poww(long long base, long long exp)
{
    long long result = 1;
    for (int i = 0; i < exp; i++)
    {
        result *= base;
    }
    return result;
}

int strleng(char *string)
{
    int i = 0;
    while (*string++)
    {
        i++;
    }
    return i;
}

void strcopy(char *string1, char *string2)
{
    for (int i = 0; i < strleng(string2); i++)
    {
        string1[i] = string2[i];
    }
}

int chartoint(char string)
{
    int result;
    result = string - '0';
    return result;
}

char check_sign(char *number)
{
    char sign;
    if (number[0] == '-')
    {
        sign = 'n';
        return sign;
    }
    char aux[20];
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
    char aux[20];
    base = 'd';
    return base;
}

long long convert_valuell(char letter)
{
    char hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    long long i = 0;
    for (i = 0; i < 16; i++)
    {
        if (letter == hex[i])
        {
            break;
        }
    }
    return i;
}

int convert_valueint(char letter)
{
    char hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    int i = 0;
    for (i = 0; i < 16; i++)
    {
        if (letter == hex[i])
        {
            break;
        }
    }
    return i;
}

int atoint(char *string)
{
    int result, number[50];
    int i = 0;

    for (i = 0; i < strleng(string); i++)
    {
        number[i] = string[i] - '0';
    }

    int len = sizeof(number) / sizeof(int);
    int exp = len - 1;
    for (i = 0; i < len; i++)
    {
        result += (number[i]) * poww(10, exp);
    }

    return result;
}

long long atoll(char *string)
{
    /*
    recebe um número no formato de string na base decimal ou hexadecimal
    devolve um numero long long decimal
    */

    long long result = 0, number[50];
    int i = 0;
    char base, sign;

    base = check_base(string);
    sign = check_sign(string);
    // hex number
    if (base == 'h')
    {
        // printf("number: %s", string);
        for (i = 2; i < strleng(string); i++)
        {
            number[i] = convert_valuell(string[i]);
            printf("number vector: %lli\n", number[i]);
        }
        int len = i;
        int exp = len - 1;
        for (i = 0; i < len; i++)
        {
            result += (number[i]) * poww(16, exp);
        }

        return result;
    }

    // decimal number
    // printf("decimal number\n");
    int k, j = 0;
    if (sign == 'p')
        k = 0;
    else
        k = 1;
    for (i = k; i < strleng(string); i++)
    {
        number[j] = string[i] - '0';
        // printf("number vector: %lli\n", number[j]);
        j++;
    }
    // printf("i: %d\n",i);
    int len = j;
    int exp = len - 1;
    for (i = 0; i < len; i++)
    {
        // printf("number vector: %lli\n", number[i]);
        result += (number[i]) * poww(10, exp);
        exp--;
    }
    if (k == 1)
        result *= -1;
    return result;
}

char *lltoa(long long number, char *string)
{
    int i = 0;
    char stringaux[50];
    //printf("number: %lli\n",number);
    while (number > 0) {
        stringaux[i] = number % 10 + '0';
        // printf("number10: %lli\n",number%10);
        number = number / 10;
        i++;
    }
    stringaux[i] = '\0';
    // printf("STRINGaux: %s\n",stringaux);
    // inverter resposta
    int k = 0;
    for (int j = i - 1; j >= 0; j--) {
        // printf("STRINGauxchar: %c\n",stringaux[j]);
        string[k] = stringaux[j];
        k++;
    }
    string[k] = '\0';
    // printf("STRING: %s\n",string);
    return string;
}

char reconvert_value(int number)
{
    char letter;
    char hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    letter = hex[number];
    return letter;
}

int char_is_bigger(char *number)
{
    /*
    check if an number is bigger than 2147483647
    */

    char limit[] = {'2', '1', '4', '7', '4', '8', '3', '6', '4', '7'};
    if (strleng(number) > 10)
    {
        return 1;
    }
    if (strleng(number) == 10)
    {
        for (int i = 0; i < strleng(number); i++)
        {
            if (number[i] > limit[i])
            {
                return 1;
            }
            else if (number[i] < limit[i])
            {
                return 0;
            }
        }
    }

    return 0;
}

int char_is_lower(char *number)
{
    /*
    check if an number is lower than -2147483648
    */

    char limit[] = {'2', '1', '4', '7', '4', '8', '3', '6', '4', '8'};
    if (strleng(number) > 10)
    {
        return 1;
    }
    if (strleng(number) == 10)
    {
        for (int i = 1; i < strleng(number); i++)
        {
            if (number[i] > limit[i])
            {
                return 1;
            }
            else if (number[i] < limit[i])
            {
                return 0;
            }
        }
    }

    return 0;
}



int is_bigger(long long number)
{
    /*
    check if an number is bigger than 2147483647
    */
    if (number > 2147483647)
    {
        return 1;
    }
    return 0;
}

void to_binary(long long number, char *answer)
{
    /*
    converts a decimal number to its binary representation
    */
    char aux[100];
    int q, r = 0, i = 0;
   
    while (number > 0)
    {
        aux[i] = number % 2 + '0';
        // printf("aux[i]: %c\n", aux[i]);
        number /= 2;
        i++;
    }
    aux[i] = '\0';
    // inverter resposta
    for (int j = strleng(aux) - 1; j >= 0; j--)
    {
        answer[r] = aux[j];
        r++;
    }
    answer[r] = '\0';

}

char *ato_decimal(char *number, char base, char *sresult)
{
    /*
    converte um numero hexadecimal para decimal
    se for um numero decimal, retorna o próprio numero.
    */
    int nvalue, exp = strleng(number) - 3; // subtrai 2 devido ao "0x", depois subtrai mais um para acessar corretamente os indices
    char auxvalue[2];
    long long nresult = 0;
    char auxstring[50];

    if (base == 'd')
    {
        strcopy(sresult, number);
    }
    else
    {
        for (int i = 2; i < strleng(number); i++)
        {
            nvalue = convert_valuell(number[i]);
            // printf("dec: %d|",nvalue);
            // printf("exp: %d|",exp);
            // printf("poww: %lli|",poww(16,exp));
            // printf("conta: %lli\n",nvalue*poww(16,exp));
            nresult += (nvalue)*poww(16, exp);
            exp--;
        }
        lltoa(nresult, auxstring);
        strcopy(sresult, auxstring);
    }
}

long long ato_c2decimal(char *number)
{
    /*
    converte um número decimal para complemento de 2
    */
    // printf("NUMBER: %s\n", number);
    // printf("ENTREI NO C2\n");
    char sign = check_sign(number);

    // printf("sign %c\n", sign);

    long long diff, aux, result;
    if (char_is_bigger(number) && sign == 'p')
    {
        // printf("ISBIGGER\n");
        aux = atoll(number);
        diff = aux - 2147483648;
        // printf("DIFF: %lli", diff);
        result = -2147483648 + diff;
        return result;
    }
    else if (char_is_lower(number) && sign == 'n')
    {
        aux = atoll(number);
        //printf("aux: %lli\n", aux);
        diff = aux + 2147483648;
        result = 2147483648 + diff;
        //printf("result: %lli\n", result);
        //printf("--------------------\n");
        return result;
    }

    result = atoll(number);
    return result;
}

long long c2to_decimal(char *number)
{
    /*
    converte um número c2 para decimal
    */
    
    //printf("------------------------------\n");
    //printf("ENTREI NO C2\n");
    
    //printf("NUMBER: %s\n", number);
    char sign = check_sign(number);

    //printf("sign %c\n", sign);

    long long diff, aux, result;
    // if (char_is_bigger(number) && sign == 'p') {
    //     //printf("ISBIGGER\n");
    //     aux = atoll(number);
    //     diff = aux - 2147483648;
    //     // printf("DIFF: %lli", diff);
    //     result = -2147483648 + diff;
    //     return result;
    // }
    //else 
    if (sign == 'n') {
        aux = atoll(number);
        //printf("aux: %lli\n", aux);
        diff = aux + 2147483648;
        result = 2147483648 + diff;
        //printf("result: %lli\n", result);
        //printf("--------------------\n");
        return result;
    }
    //printf("estou aqui\n");
    result = atoll(number);
    //printf("result\n");
    return result;
}

long long change_endianness(long long number) {
    //
    //receber um unsigned int e mudar seu endianness
    //
    char binary[33];

    //printf("im in\n");
    
    to_binary(number,binary);
    //printf("number: %lli\n", number);
    //printf("binary: %s\n", binary);

    //completar 32 bits
    char aux[33];
    int j;
    if (strleng(binary)<32) {
        int limit = 32-strleng(binary);
        for (int i=0; i<limit; i++) {
            aux[i] = '0';
        }
        j = limit;
        for (int i=0; i<strleng(binary); i++) {
            aux[j] = binary[i];
            j++;
        }
    }
    else {
        strcopy(aux,binary);
    }
    aux[32] = '\0';
    //printf("bits completos: %s\n", aux);
    
    //inverter bytes
    int ini = 24, fim = 31;
    j = 0; 
    char byte[9];
    int b=0;
    for (int k=0; k<4; k++) {
        for (int i=ini; i<=fim; i++) {
            binary[j] = aux[i];
            //byte[b]   = aux[i];
            j++;
            //b++;
            //printf("i: %d ", i);
        }   
        //byte[8] = '\0';
        //printf("     byte: %s\n", byte);
        //b = 0;
        ini -= 8;
        fim -= 8;
    }
    binary[32] = '\0';
    //printf("bits invertidos: %s\n", binary);

    //converter para decimal
    long long exp = 31;
    long long result=0;
    long long bit;
    for (int i=0; i<strleng(binary); i++) {
        bit = binary[i] - '0';
        //printf("-------------------------\n");
        //printf(" bit: %lli |", bit);
        //printf(" exp: %lli", exp);
        //printf(" poww: %lli", poww(2,exp));
        result += bit*poww(2,exp);
        //printf("result: %lli\n", result);
        //printf("-------------------------\n");
        exp--;
    }
    //printf("result: %lli\n", result);
    return result;
}


void to_hex(long long number, char *vresult)
{
    int vaux[50]; 
    int i = 0;
    //printf("ENTREI\n");
    //printf("number: %lli\n", number);
    vresult[0] = '0';
    vresult[1] = 'x';
    while (number > 0)
    {
        //printf("--------------------------------------\n");
        //printf("numberper16: %lli\n", number%16);
        vaux[i] = number%16;
        //printf("vaux[i] = %d " , vaux[i]);
        number /= 16;
        i++;
        //printf("number: %lli\n", number);
        //printf("--------------------------------------\n");
   }
    //printf("\n");
    // inverter resposta
    int k = 2;
    for (int j = i - 1; j >= 0; j--) {
        //printf("reconvert value: %c\n", reconvert_value(vaux[i]));
        vresult[k] = reconvert_value(vaux[j]);
        k++;
    }
    vresult[k] = '\0';
}


void to_octal(long long number, char *vresult)
{
    int i = 0;
    char vaux[50];
    vresult[0] = '0';
    vresult[1] = 'o';

    while (number > 0)
    {
        vaux[i] = number%8 +'0';
        number /= 8;
        i++;
    }
    vaux[i] = '\0';
    int k = 2;
    for (int j = i - 1; j >= 0; j--) {
        vresult[k] = vaux[j];
        k++;
    }
    vresult[k] = '\0';
}


int main()
{
    char number[40];

    /* Read up to 20 bytes from the standard input into the str buffer */
    scanf("%s", number);

    char base = 'a'; 
    char dresult[40], bresult[40], hexresult[40], oresult[40],resposta1[40], resposta2[40], resposta3[40], aux[40];
    char init[40] = {'a','a','a','a','\0'};
    long long c2dresult, c2result;

    long long invdresult=0;

    int j = 2;

    //inicializar
    strcopy(dresult, init);
    strcopy(bresult, init);
    strcopy(hexresult, init);
    strcopy(oresult, init);
    strcopy(resposta1, init);
    strcopy(resposta2, init);
    strcopy(resposta3, init);
    strcopy(aux, init);
    base = check_base(number);

    // converter hexadecimal para um numero decimal nao assinado
    ato_decimal(number, base, dresult);
    printf("%s\n", dresult);
    // converter o numero decimal para a representacao em unsigned
    c2dresult = c2to_decimal(dresult);
    
    // converter o numero decimal para o numero binario
    to_binary(c2dresult, bresult);
    resposta1[0] = '0';
    resposta1[1] = 'b';
   
    for (int i=0; i<strleng(bresult); i++) {
        resposta1[j] = bresult[i];
        j++;
    }
    // converter para complemento de 2
    c2result = ato_c2decimal(dresult);
    
    //change endianness
    //printf("c2drseult: %lli\n", c2dresult);
    invdresult = change_endianness(c2dresult);
    lltoa(invdresult, resposta3);

    //valor em hexadecimal
    to_hex(c2dresult, hexresult);

    //valor em octal
    to_octal(c2dresult, oresult);
   
    if (c2result < 0) {         
         lltoa(-c2result,aux);
         resposta2[0] = '-';
         j=1;
        //  printf("aux: %s\n",aux);
         for (int i=0; i<strleng(aux); i++) {
            resposta2[j] = aux[i];
            j++;
            // printf("aux: %s\n",aux);
        }
    //     resposta2[j] = '\0';
    }
    else if (c2result >= 0) {
        lltoa(c2result, resposta2);
    }
    
    //printf("BUG\n");
    // printf("%c\n", base);
    // printf("dresult: %s\n", dresult);
    printf("%s\n", resposta1);
    printf("%s\n", resposta2);
    printf("%s\n", resposta3);
    printf("%s\n", hexresult);
    printf("%s\n", oresult);
    return 0;
}
