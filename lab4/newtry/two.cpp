#include <iostream>
using namespace std;


void twocomplement(int decimal) {
    int numero = 0;
    int res = 0;

    if (decimal < 0) numero = -decimal - 1;
    else numero = decimal;
    
    for (int i=0; i<32; i++) {
        if (!(numero & 1<<i)) {
            cout << (1<<i);
            res |= (1<<i);
        } 
    }
    cout << '\n';
    cout << res;
}

int main()
{    
    int n;
    n += 2147483648;
    cout << n;

    twocomplement(n);
    
}