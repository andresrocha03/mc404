#include <iostream>
#include <bitset>

// Function to calculate the two's complement representation
std::string twosComplement(int num, int bits) {
    // Convert the decimal number to binary
    std::bitset<32> binary(num);

    // Invert all the bits
    for (int i = 0; i < bits; ++i) {
        binary[i] = !binary[i];
    }

    // Add 1 to the binary representation
    int carry = 1;
    for (int i = 0; i < bits; ++i) {
        if (binary[i] == 0 && carry == 1) {
            binary[i] = 1;
            carry = 0;
        } else if (binary[i] == 1 && carry == 1) {
            binary[i] = 0;
        }
    }

    // Return the binary representation as a string
    return binary.to_string().substr(32 - bits);
}

int main() {
    int num;
    int bits;

    // Input the decimal number and number of bits
    std::cout << "Enter a decimal number: ";
    std::cin >> num;
    std::cout << "Enter the number of bits: ";
    std::cin >> bits;

    // Check for valid input bits
    if (bits < 2 || bits > 32) {
        std::cout << "Invalid number of bits. Please enter a number between 2 and 32." << std::endl;
        return 1;
    }

    // Calculate and output the two's complement representation
    std::string twosComp = twosComplement(num, bits);
    std::cout << "Two's complement representation: " << twosComp << std::endl;

    return 0;
}
