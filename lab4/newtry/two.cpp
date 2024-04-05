#include <iostream>
using namespace std;


void twocomplement(int decimal) {
    int numero = 0;
    int res = 0;

    if (decimal == -2147483648) {
        //cout << "entrei\n";
        numero = - (decimal + 1); 
        cout << numero << "\n";
    }
    else {
        if (decimal < 0) numero = (-decimal) - 1;
        else numero = decimal;
    }
    
    for (int i=0; i<32; i++) {
        if (!(numero & (1<<i))) {
            res = res | (1<<i);
        } 
    }

    int k = 31;
    for (; k>=0; k--) {  //percorrer os bits
        if ((numero & (1<<k))) { 
            break; //break ao encontrar o 1; o indice i guarda a posicao do primeiro 1
        } 
    }
    
    for (int i=k; i>=0; i--) {
        if (!(decimal & (1<<i))) {
            cout << 0 ;
        } 
        if ((decimal & (1<<i))) {
            cout << 1 ;
        } 
    }

    
    
    cout << "\n" << res;
}

int main()
{    

    int n;
    cin >> n;
    twocomplement(n);
    
}