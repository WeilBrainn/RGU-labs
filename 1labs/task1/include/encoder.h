#ifndef ENCODER_H
#define ENCODER_H

class Encoder {
protected:
    unsigned char* key;
    int length_key;
    unsigned char s_key[256];

public:
    // Конструктор
    Encoder(unsigned char const* input_key, int key_length);

    // Деструктор
    virtual ~Encoder();

    // Конструктор копирования
    Encoder(const Encoder& other);

    // Оператор присваивания
    Encoder& operator=(const Encoder& other);

    // Конструктор перемещения
    Encoder(Encoder&& other) noexcept;

    // Оператор присваивания перемещения
    Encoder& operator=(Encoder&& other) noexcept;

    void set_key(unsigned char const* new_key, int new_length);
    void encode(const char* input_file_path, const char* output_file_path);

protected:
    void KSA();
    void mutate_state();

private:
    void copy_from(const Encoder& other);
    void move_from(Encoder&& other) noexcept;
};

#endif