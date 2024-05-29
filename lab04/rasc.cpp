
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
    int potencia=1,dresult=0,hresult; 
    int ini = 28, fim = 31, j = 9,bit;
    char hex[40];

    cout << "0x";

    for (int k=0; k<8; k++) { // iterar de nibble em nibble
        dresult = 0;
        potencia = 1;
        cout << "k: " << k << "\n";  
        for (int i=fim; i>=ini; i--) { 
            cout << "i: " << i << "\n";
            bit = (numero & (1<<i)); //pegar cada bit do nibble
            cout << bit << "\n";
           
            dresult += bit*potencia; //calcular o valor do nibble em decimal

            potencia *= 2;          //atualizar potencia
        }
        cout << "\n" << dresult << "\n";
        hresult = reconvert_value(dresult); //passar valor decimal para hex
        hex[j] = hresult + '0';
        j--;
        ini -= 4;
        fim -= 4;
        cout << "j: " << j << "\n";;

    }
    hex[10] = '\n';
    cout << hex;
}

int main()
{    

    int n;
    cin >> n;
    print_hex(n);
    
}