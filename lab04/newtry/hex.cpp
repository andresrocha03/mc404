
#include <iostream>
using namespace std;

char reconvert_value(int number)
{
    char letter;
    char hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    letter = hex[number];
    return letter;
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

    cout << "0x";

    for (int k=0; k<8; k++) { // iterar de nibble em nibble
        dresult = 0;
        potencia = 1;
        cout << "k: " << k << "\n"; 
        nibble = (numero>>4*k) & 15; 
        cout << "nibble: " << nibble << "\n"; 
        hresult = reconvert_value(nibble); //passar valor decimal para hex
        cout << "hex: " << hresult << "\n"; 
        hex[j] = hresult;
        j--;
        cout << "j: " << j << "\n";;

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

    cout << resposta << "\n";
}

int main()
{    

    int n;
    cin >> n;
    print_hex(n);
    
}