#ifndef encoder.h
#define encoder.h

#include <iostream>
#include <fstream>

class Encoder {
protected:
    unsigned char* key;
    int length_key;
    unsigned char s_key[256];

public:
    Encoder(unsigned char const* input_key, int key_length);
    virtual ~Encoder(); 

    void set_key(unsigned char const* new_key, int new_length);
    void encode(const char* input_file_path, const char* output_file_path);

protected:
    void KSA();
    void mutate_state();
};

#endif
