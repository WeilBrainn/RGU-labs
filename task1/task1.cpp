#include "encoder.h"

Encoder::Encoder(unsigned char const* input_key, int key_length) {
    length_key = key_length;
    key = new unsigned char[length_key];
    for (int i = 0; i < length_key; i++) {
        key[i] = input_key[i];
    }
    KSA();
}

Encoder::~Encoder() {
    delete[] key;
}

void Encoder::set_key(unsigned char const* new_key, int new_length) {
    if (key != nullptr) {
        delete[] key;
    }
    length_key = new_length;
    key = new unsigned char[length_key];
    for (int i = 0; i < length_key; i++) {
        key[i] = new_key[i];
    }
    KSA();
}

void Encoder::encode(const char* input_file_path, const char* output_file_path) {
    if (input_file_path == nullptr || output_file_path == nullptr) {
        return;
    }
    KSA();

    std::ifstream inFile(input_file_path, std::ios::binary);
    std::ofstream outFile(output_file_path, std::ios::binary);
    if (!inFile.is_open() || !outFile.is_open()) {
        return;
    }

    char byte;
    unsigned char i = 0, j = 0;
    while (inFile.get(byte)) {
        i = (i + 1) % 256;
        j = (j + s_key[i]) % 256;

        unsigned char temp = s_key[i];
        s_key[i] = s_key[j];
        s_key[j] = temp;

        unsigned char keystream = s_key[(s_key[i] + s_key[j]) % 256];
        char encrypted_byte = byte ^ keystream;

        outFile.put(static_cast<char>(encrypted_byte));
    }

    inFile.close();
    outFile.close();
}

void Encoder::KSA() {
    for (int i = 0; i < 256; i++) {
        s_key[i] = i;
    }

    unsigned char j = 0;
    for (int i = 0; i < 256; i++) {
        j = (j + s_key[i] + key[i % length_key]) % 256;

        unsigned char temp = s_key[i];
        s_key[i] = s_key[j];
        s_key[j] = temp;
    }
}

void Encoder::mutate_state() {
    for (int i = 0; i < 256; i++) {
        s_key[i] ^= 0x5A;
    }
}
