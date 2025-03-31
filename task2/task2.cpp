#include "LOGICAL_VALUES_ARRAY.h"

// Constructor
logical_values_array::logical_values_array(unsigned int value) : _value(value) {}

// Getters
unsigned int logical_values_array::get_value() const {
    return _value;
}

int logical_values_array::get_bit(size_t position) const {
    if (position >= sizeof(unsigned int) * 8) {
        throw std::out_of_range("bit position is out of range");
    }
    return (_value >> position) & 1;
}

int logical_values_array::operator[](size_t position) const {
    return get_bit(position);
}

// Mutator
void logical_values_array::set_value(unsigned int new_value) {
    _value = new_value;
}

// Logic operation
logical_values_array logical_values_array::invert() const {
    return logical_values_array(~_value);
}

logical_values_array logical_values_array::conjunction(const logical_values_array& other) const {
    return logical_values_array(this->_value & other._value);
}

logical_values_array logical_values_array::disjunction(const logical_values_array& other) const {
    return logical_values_array(this->_value | other._value);
}

logical_values_array logical_values_array::xor_func(const logical_values_array& other) const {
    return logical_values_array(this->_value ^ other._value);
}

logical_values_array logical_values_array::implication(const logical_values_array& other) const {
    return logical_values_array(~this->_value | other._value);
}

logical_values_array logical_values_array::coimplication(const logical_values_array& other) const {
    return logical_values_array(~(~this->_value | other._value));
}

logical_values_array logical_values_array::pierce_arrow(const logical_values_array& other) const {
    return logical_values_array(~(this->_value | other._value));
}

logical_values_array logical_values_array::sheffer_stroke(const logical_values_array& other) const {
    return logical_values_array(~(this->_value & other._value));
}

// Static comparison
bool logical_values_array::equals(const logical_values_array& first, const logical_values_array& second) {
    return first._value == second._value;
}

// Convert to string
void logical_values_array::to_binary_string(char* buffer, size_t buffer_size) const {
    if (buffer_size < sizeof(unsigned int) * 8 + 1) {
        throw std::invalid_argument("buffer_size is out of range");
    }

    size_t num_bits = sizeof(unsigned int) * 8;
    for (size_t i = 0; i < num_bits; i++) {
        buffer[i] = ((_value >> (num_bits - 1 - i)) & 1) ? '1' : '0';
    }
    buffer[num_bits] = '\0';
}
