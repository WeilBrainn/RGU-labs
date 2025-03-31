#include "encoder.h"

int main() {
    unsigned char key[] = { 0x1A, 0x2B, 0x3C, 0x4D, 0x5E };
    int key_length = sizeof(key) / sizeof(key[0]);

    Encoder enc(key, key_length);
    enc.encode("input_file.txt", "encrypted.bin");
    enc.encode("encrypted.bin", "decrypted.txt");

    std::cout << "Files encrypted and decrypted!" << std::endl;

    return 0;
}
