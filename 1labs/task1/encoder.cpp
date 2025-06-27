#include "./include/encoder.h"
#include <fstream>

// Конструктор
Encoder::Encoder(unsigned char const* input_key, int key_length)
        : key(nullptr), length_key(key_length) {
    if (input_key != nullptr && key_length > 0) {
        key = new unsigned char[length_key];
        for (int i = 0; i < length_key; i++) {
            key[i] = input_key[i];
        }
        KSA();
    }
}

// Деструктор
Encoder::~Encoder() {
    delete[] key;
}

// Конструктор копирования
Encoder::Encoder(const Encoder& other)
        : key(nullptr), length_key(0) {
    copy_from(other);
}

// Оператор присваивания
Encoder& Encoder::operator=(const Encoder& other) {
    if (this != &other) {
        delete[] key;
        copy_from(other);
    }
    return *this;
}

// Конструктор перемещения
Encoder::Encoder(Encoder&& other) noexcept
        : key(nullptr), length_key(0) {
    move_from(static_cast<Encoder&&>(other));
}

// Оператор присваивания перемещения
Encoder& Encoder::operator=(Encoder&& other) noexcept {
    if (this != &other) {
        delete[] key;
        move_from(static_cast<Encoder&&>(other));
    }
    return *this;
}

void Encoder::set_key(unsigned char const* new_key, int new_length) {
    if (new_key == nullptr || new_length <= 0) {
        return;
    }

    delete[] key;
    length_key = new_length;
    key = new unsigned char[length_key];
    for (int i = 0; i < length_key; i++) {
        key[i] = new_key[i];
    }
    KSA();
}

void Encoder::encode(const char* input_file_path, const char* output_file_path) {
    if (input_file_path == nullptr || output_file_path == nullptr || key == nullptr) {
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

        outFile.put(encrypted_byte);
    }

    inFile.close();
    outFile.close();
}

void Encoder::KSA() {
    if (key == nullptr) {
        return;
    }

    for (int i = 0; i < 256; i++) {
        s_key[i] = static_cast<unsigned char>(i);
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

// Приватные вспомогательные методы
void Encoder::copy_from(const Encoder& other) {
    length_key = other.length_key;
    if (other.key != nullptr && length_key > 0) {
        key = new unsigned char[length_key];
        for (int i = 0; i < length_key; i++) {
            key[i] = other.key[i];
        }
    } else {
        key = nullptr;
    }

    // Копируем s_key
    for (int i = 0; i < 256; i++) {
        s_key[i] = other.s_key[i];
    }
}

void Encoder::move_from(Encoder&& other) noexcept {
    key = other.key;
    length_key = other.length_key;

    // Перемещаем s_key
    for (int i = 0; i < 256; i++) {
        s_key[i] = other.s_key[i];
    }

    // Очищаем other
    other.key = nullptr;
    other.length_key = 0;
}