#include <stdio.h>

int main() {
    int input;
    long long x = 10;

    x = x & 0x0000000F;
    x <<= 24;
    printf("%lli/\n",x);
    return 0;
}