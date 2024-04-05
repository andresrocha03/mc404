#include <iostream>
using namespace std;

void print_octal (int numero) {
    /*
    receber um numero decimal em complemento de 2
    printar seu valor em hexadecimal
    */
    int potencia=1;
    char oresult; 
    int bits, j = 12,bit;
    char oct[40], resposta[40];

    oct[0] = '0';
    oct[1] = 'o';

    for (int k=0; k<11; k++) { // iterar de bits em bits
        if (k != 10) {
            potencia = 1;
            bits = (numero>>3*k) & 7; 
            oct[j] = bits + '0';
            j--;
        }
        else {
            if (numero & (1<<31)) { // se o ultimo bit for 1
                if (!(numero & (1<<30))) { //se o penultimo bit for 0
                    //cout << "ENTREI AQUI\n";
                    oct[j] = '2';
                }
                else {          
                oct[j] = '3';
                }
            }
            if (!(numero & (1<<31))) { // se o ultimo bit for 0
                if (!(numero & (1<<30))) { //se o penultimo bit for 0
                    oct[j] = '0';
                }
                else { //penultimo bit é 1
                    //cout << "ENTREI AQUI\n";
                    oct[j] = '1';
                }

            } 
        }
        
    }
    oct[13] = '\n';
    oct[14] = '\0';

    resposta[0] = '0';
    resposta[1] = 'o';

    int i,r=2;
    for (i=2; oct[i] != '\0'; i++) { //tirar zeros à esquerda
        if (oct[i] != '0') break;
    }

    for (int k=i; oct[k] != '\0'; k++) {//tirar zeros à esquerda
        resposta[r] = oct[k];
        r++;
    }
    resposta[r] = '\0';

    cout << resposta << "\n";
}


int main()
{    

    int n;
    cin >> n;
    //cout << (1<<1);
    print_octal(n);
    
}