#include <stdio.h>

int main() {
    int input;
    
    scanf("%d",&input);
    if (input > 2147483647) {
        printf("OIOIOIOIO");
    }
    
    return 0;
}