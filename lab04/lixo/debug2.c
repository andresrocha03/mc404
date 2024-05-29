int read(int __fd, const void *__buf, int __n)
{
    int ret_val;
    __asm__ __volatile__(
        "mv a0, %1           # file descriptor\n"
        "mv a1, %2           # buffer \n"
        "mv a2, %3           # size \n"
        "li a7, 63           # syscall write code (63) \n"
        "ecall               # invoke syscall \n"
        "mv %0, a0           # move return value to ret_val\n"
        : "=r"(ret_val)                   // Output list
        : "r"(__fd), "r"(__buf), "r"(__n) // Input list
        : "a0", "a1", "a2", "a7");
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
        :                                 // Output list
        : "r"(__fd), "r"(__buf), "r"(__n) // Input list
        : "a0", "a1", "a2", "a7");
}

void exit(int code)
{
    __asm__ __volatile__(
        "mv a0, %0           # return code\n"
        "li a7, 93           # syscall exit (64) \n"
        "ecall"
        :           // Output list
        : "r"(code) // Input list
        : "a0", "a7");
}

#define STDIN_FD 0
#define STDOUT_FD 1

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
            // printf("number vector: %lli\n", number[i]);
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
    int k, j = 0;
    if (sign == 'p')
        k = 0;
    else
        k = 1;
    for (i = k; i < strleng(string); i++)
    {
        number[j] = string[i] - '0';
        j++;
    }
    int len = j;
    int exp = len - 1;
    for (i = 0; i < len; i++)
    {
        result += (number[i]) * poww(10, exp);
        exp--;
    }
    if (k == 1)
        result *= -1;
    return result;
}

char *lltoa(unsigned int number, char *string)
{
    int i = 0;
    char stringaux[50];
    while (number > 0)
    {
        stringaux[i] = number % 10 + '0';
        number = number / 10;
        i++;
    }

    // inverter resposta
    int k = 0;
    for (int j = i - 1; j >= 0; j--)
    {
        string[k] = stringaux[j];
        k++;
    }
    string[k] = '\n';
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
    char aux[100], debug[2];
    int q, r = 0, i = 0;

    while (number > 0)
    {
        aux[i] = number % 2 + '0';
        number /= 2;
        i++;
    }
    // write(STDOUT_FD, aux, strleng(aux));
    // inverter resposta
    for (int j = i - 1; j >= 0; j--)
    {
        answer[r] = aux[j];
        r++;
    }

    answer[r] = '\n';
}

char *ato_decimal(char *number, char base, char *sresult)
{
    /*
    converte um numero hexadecimal para decimal
    se for um numero decimal, retorna o próprio numero.
    */
    int nvalue, exp = strleng(number) - 3; // subtrai 2 devido ao "0x", depois subtrai mais um para acessar corretamente os indices
    char auxvalue[2];
    unsigned int nresult = 0;
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
    char sign = check_sign(number);

    long long diff, aux, result;
    if (char_is_bigger(number) && sign == 'p')
    {
        aux = atoll(number);
        diff = aux - 2147483648;
        result = -2147483648 + diff;
        return result;
    }
    else if (char_is_lower(number) && sign == 'n')
    {
        aux = atoll(number);
        diff = aux + 2147483648;
        result = 2147483648 + diff;
        return result;
    }

    result = atoll(number);
    return result;
}

unsigned int c2to_decimal(char *number, int n)
{
    /*
    converte um número c2 para decimal
    */
    char sign = check_sign(number);

    // long long diff = 0, aux = 0;
    unsigned int result = 0;
    // char debug[40];
    int i = 0;
    if (sign == 'n')
    {
        i = 1;
        // aux = atoll(number);
        // diff = aux + 2147483648;
        // result = 2147483648 + diff;
        // lltoa(result, debug);
        // return result;
    }

    for (; i < n - 1; i++)
    {
        result = result * 10;
        result += number[i] - '0';
    }

    if (sign == 'n')
    {
        return -result;
    }
    // write(STDOUT_FD, &result, 20);
    //  result = (unsigned int)atoll(number);
    //  result = 545648;
    return result;
}

long long change_endianness(long long number)
{
    //
    // receber um long long  e mudar seu endianness
    //
    char binary[33];

    // printf("im in\n");

    to_binary(number, binary);
    // printf("number: %lli\n", number);
    // printf("binary: %s\n", binary);

    // completar 32 bits
    char aux[33];
    int j;
    if (strleng(binary) < 32)
    {
        int limit = 32 - strleng(binary);
        for (int i = 0; i < limit; i++)
        {
            aux[i] = '0';
        }
        j = limit;
        for (int i = 0; i < strleng(binary); i++)
        {
            aux[j] = binary[i];
            j++;
        }
    }
    else
    {
        strcopy(aux, binary);
    }
    aux[32] = '\0';
    // printf("bits completos: %s\n", aux);

    // inverter bytes
    int ini = 24, fim = 31;
    j = 0;
    char byte[9];
    int b = 0;
    for (int k = 0; k < 4; k++)
    {
        for (int i = ini; i <= fim; i++)
        {
            binary[j] = aux[i];
            // byte[b]   = aux[i];
            j++;
            // b++;
            // printf("i: %d ", i);
        }
        // byte[8] = '\0';
        // printf("     byte: %s\n", byte);
        // b = 0;
        ini -= 8;
        fim -= 8;
    }
    binary[32] = '\0';
    // printf("bits invertidos: %s\n", binary);

    // converter para decimal
    long long exp = 31;
    long long result = 0;
    long long bit;
    for (int i = 0; i < strleng(binary); i++)
    {
        bit = binary[i] - '0';
        // printf("-------------------------\n");
        // printf(" bit: %lli |", bit);
        // printf(" exp: %lli", exp);
        // printf(" poww: %lli", poww(2,exp));
        result += bit * poww(2, exp);
        // printf("result: %lli\n", result);
        // printf("-------------------------\n");
        exp--;
    }
    // printf("result: %lli\n", result);
    return result;
}

void to_hex(long long number, char *vresult)
{
    int vaux[50];
    int i = 0;
    // printf("ENTREI\n");
    // printf("number: %lli\n", number);
    vresult[0] = '0';
    vresult[1] = 'x';
    while (number > 0)
    {
        // printf("--------------------------------------\n");
        // printf("numberper16: %lli\n", number%16);
        vaux[i] = number % 16;
        // printf("vaux[i] = %d " , vaux[i]);
        number /= 16;
        i++;
        // printf("number: %lli\n", number);
        // printf("--------------------------------------\n");
    }
    // printf("\n");
    //  inverter resposta
    int k = 2;
    for (int j = i - 1; j >= 0; j--)
    {
        // printf("reconvert value: %c\n", reconvert_value(vaux[i]));
        vresult[k] = reconvert_value(vaux[j]);
        k++;
    }
    vresult[k] = '\n';
}

void to_octal(long long number, char *vresult)
{
    int i = 0;
    char vaux[50];
    vresult[0] = '0';
    vresult[1] = 'o';

    while (number > 0)
    {
        vaux[i] = number % 8 + '0';
        number /= 8;
        i++;
    }
    vaux[i] = '\0';
    int k = 2;
    for (int j = i - 1; j >= 0; j--)
    {
        vresult[k] = vaux[j];
        k++;
    }
    vresult[k] = '\n';
}

void to_2complement(unsigned int number, char *vresult)
{
    int i = 0;
    char vaux[50];
    char sign = 'p';
    int two_complement;
    if (number > 2147483647)
    {
        two_complement = 2147483647;
    }
    else
    {
        two_complement = (int)number;
    }
    if (two_complement < 0)
    {
        sign = 'n';
        two_complement = -two_complement;
    }
    while (two_complement != 0)
    {
        vaux[i] = (two_complement % 10) + '0';
        two_complement /= 10;
        write(STDOUT_FD, &(vaux[i]), 1);
        write(STDOUT_FD, "\n", 1);

        i++;
    }
    int k = 0;
    if (sign == 'n')
    {
        vresult[0] = '-';
        k = 1;
    }
    for (int j = i - 1; j >= 0; j--)
    {
        vresult[k] = vaux[j];
        k++;
    }
    vresult[k] = '\n';
}

int main()
{
    // scanf("%s", number);

    char number[40];
    char base = 'a';
    char dresult[40], bresult[40], hexresult[40], oresult[40], resposta1[40], resposta2[40], resposta3[40], aux[40];
    char init[4], c2char[40];
    unsigned int c2dresult;
    long c2result;
    long long invdresult = 0;
    int j = 2;

    // ler entrada
    int n = read(STDIN_FD, number, 40);
    // atoll(number);

    // inicializar
    for (int i = 0; i < 3; i++)
    {
        init[i] = 'a';
    }

    strcopy(dresult, init);
    strcopy(bresult, init);
    strcopy(hexresult, init);
    strcopy(oresult, init);
    strcopy(resposta1, init);
    strcopy(resposta2, init);
    strcopy(resposta3, init);
    strcopy(aux, init);
    // strcopy(c2char, init);

    base = check_base(number);

    // converter hexadecimal para um numero decimal nao assinado
    ato_decimal(number, base, dresult);
    // write(STDOUT_FD, dresult, strleng(dresult));

    // converter o numero decimal para a representacao em unsigned
    c2dresult = c2to_decimal(dresult, n);

    // write(STDOUT_FD, c2dresult, 20);

    // converter o numero decimal para o numero binario

    lltoa(c2dresult, c2char);

    write(STDOUT_FD, c2char, strleng(c2char));

    to_binary(c2dresult, bresult);
    resposta1[0] = '0';
    resposta1[1] = 'b';
    int i = 1;
    for (; i < strleng(bresult); i++)
    {
        resposta1[i + 1] = bresult[i];
    }
    resposta1[i + 1] = '\n';

    write(STDOUT_FD, resposta1, strleng(resposta1));

    // converter para complemento de 2
    // c2result = ato_c2decimal(dresult);

    // //change endianness
    // //printf("c2drseult: %lli\n", c2dresult);
    // invdresult = change_endianness(c2dresult);
    // lltoa(invdresult, resposta3);

    // //valor em hexadecimal
    to_hex(c2dresult, hexresult);
    write(STDOUT_FD, hexresult, strleng(hexresult));

    // //valor em octal
    to_octal(c2dresult, oresult);
    write(STDOUT_FD, oresult, strleng(oresult));

    to_2complement(c2result, resposta3);
    write(STDOUT_FD, resposta3, strleng(resposta3));

    // if (c2result < 0) {
    //      lltoa(-c2result,aux);
    //      resposta2[0] = '-';
    //      j=1;
    //     //  printf("aux: %s\n",aux);
    //      for (int i=0; i<strleng(aux); i++) {
    //         resposta2[j] = aux[i];
    //         j++;
    //         // printf("aux: %s\n",aux);
    //     }
    // //     resposta2[j] = '\0';
    // }
    // else if (c2result >= 0) {
    //     lltoa(c2result, resposta2);
    // }

    // write(STDOUT_FD, resposta1, strleng(resposta1)+2);
    //  write(STDOUT_FD, resposta2, strleng(resposta2)+1);
    //  write(STDOUT_FD, resposta3, strleng(resposta3)+1);
    //  write(STDOUT_FD, hexresult, strleng(hexresult)+1);
    //  write(STDOUT_FD, oresult, strleng(oresult)+1);

    // printf("%c\n", base);
    // printf("dresult: %s\n", dresult);
    // printf("%s", resposta1);
    // printf("%s", resposta2);
    // printf("%s", resposta3);
    // printf("%s", hexresult);
    // printf("%s", oresult);
    return 0;
}

void _start()
{
    int ret_code = main();
    exit(ret_code);
}