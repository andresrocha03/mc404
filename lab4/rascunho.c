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
    // printf("number: %d\n",number);
    while (number > 0)
    {
        stringaux[i] = number % 10 + '0';
        // printf("number10: %lli\n",number%10);
        number = number / 10;
        i++;
    }
    // stringaux[i] = '\0';
    // printf("STRINGaux: %s\n",stringaux);
    // inverter resposta
    int k = 0;
    for (int j = i - 1; j >= 0; j--)
    {
        // printf("STRINGauxchar: %c\n",stringaux[j]);
        string[k] = stringaux[j];
        k++;
    }
    // printf("STRING: %s",string);
    return string;
}

char reconvert_value(int number)
{
    char letter = ' ';
    if (number == 10)
    {
        letter = 'A';
    }
    else if (number == 11)
    {
        letter = 'B';
    }
    else if (number == 12)
    {
        letter = 'C';
    }
    else if (number == 13)
    {
        letter = 'D';
    }
    else if (number == 14)
    {
        letter = 'E';
    }
    else if (number == 15)
    {
        letter = 'F';
    }
    else
    {
        letter = number + '0';
    }
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
    else 
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

unsigned int uito_decimal(unsigned int number)
{
    unsigned int result;
    int aux[50], i = 0;
    while (number > 0)
    {
        aux[i] = number % 10;
        number = number / 10;
        i++;
    }
    int exp = i - 1;
    for (int j = 0; j < i; j++)
    {
        result = aux[i] * poww(16, exp);
        exp--;
    }
    return result;
}

void to_c2hex(long long number, char *vresult)
{
    int vaux[50], i = 0;

    while (number > 0)
    {
        vaux[i] = number % 16;
        number /= 16;
        i++;
    }

    // inverter resposta
    int k = 0;
    for (int j = i - 1; j >= 0; j--)
    {
        vresult[k] = reconvert_value(vaux[i]);
        k++;
    }
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

/*
int *to_octal(char *string, char base, int *vresult)
{
    if (base == 'd')
    {

        unsigned int aux, diff;
        int vaux[50], i = 0;
        long long nnumber;

        nnumber = atoll(string);
        diff = nnumber - 2147483647;
        aux = diff + 2147483647;

        aux = atoll(string);
        while (aux > 0)
        {
            vaux[i] = aux % 8;
            aux /= 8;
            i++;
        }

        // inverter resposta
        int k = 0;
        for (int j = i - 1; j >= 0; j--)
        {
            vresult[k] = vaux[i];
            k++;
        }
        return vresult;
    }

    char *decvalue;
    long long c2value, nnumber;
    ato_decimal(string, base, decvalue);
    c2value = ato_c2decimal(decvalue);
    unsigned int aux;
    int vaux[50], i = 0;

    nnumber = atoll(string);
    int diff = nnumber - 2147483647;
    aux = diff + 2147483647;

    while (aux > 0)
    {
        vaux[i] = aux % 8;
        aux /= 8;
        i++;
    }

    // inverter resposta
    int k = 0;
    for (int j = i - 1; j >= 0; j--)
    {
        vresult[k] = vaux[i];
        k++;
    }
    return vresult;
}
*/

int main()
{
    char number[50];

    /* Read up to 20 bytes from the standard input into the str buffer */
    scanf("%s", number);

    char base, dresult[100], bresult[100], hexresult[100];
    int *oresult;

    long long c2dresult, c2result;

    long long invdresult=0;

    base = check_base(number);

    // converter hexadecimal para um numero decimal nao assinado
    ato_decimal(number, base, dresult);

    // converter o numero decimal para a representacao em unsigned
    c2dresult = c2to_decimal(dresult);

    // converter o numero decimal para o numero binario
    to_binary(c2dresult, bresult);

    // converter para complemento de 2
    c2result = ato_c2decimal(dresult);

    //change endianness
    printf("c2drseult: %lli\n", c2dresult);
    invdresult = change_endianness(c2dresult);
    
    
    // printf("%c\n", base);
    //printf("dresult: %s\n", dresult);
    printf("0b%s\n", bresult);
    printf("c2_result: %lli\n", c2result);
    printf("change endianness: %lli\n", invdresult);

    return 0;
}


//if (base == 'h')
    //{
        // write number
        //    printf("%s\n", number);
  //  }
    //else
    //{
        // hexresult = to_c2hex(number,hexresult);
        // printf("%d\n", hexresult);
    //}

    // oresult = to_octal(number,base,oersult);


    //invdresult  = uito_decimal(invdresult);
    //to_c2hex(c2result, hexresult);
    //uiresult = decimal_to_unsigned(dresult);
    
/*
unsigned int change_endianness(long long llnumber)
{
    // inverter bytes do numero recebido, devolver numero com endianess trocado
    // long long llnumber;
    long long leftmost_byte, leftmiddle_byte, rightmiddle_byte, rightmost_byte;

    printf("entrei\n");
    printf("number: %lli\n", llnumber);

    printf("number: %lli\n", llnumber);
    // llnumber = atoll(number);
    printf("llnumber: %lli\n", llnumber);

    leftmost_byte = (llnumber & 0x000000FF) >> 00;
    // printf("left most: %lli\n", leftmost_byte);
    leftmiddle_byte = (llnumber & 0x0000FF00) >> 8;
    rightmiddle_byte = (llnumber & 0x00FF0000) >> 16;
    rightmost_byte = (llnumber & 0xFF000000) >> 24;

    leftmost_byte <<= 24;
    leftmiddle_byte <<= 16;
    rightmiddle_byte <<= 8;
    rightmost_byte <<= 0;

    long long result = (leftmost_byte | leftmiddle_byte |
                        rightmiddle_byte | rightmost_byte);
    return result;
}
*/

// 1110000010100110000100000000000
// 1110000010100110000000000000000
