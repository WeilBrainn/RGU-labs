#pragma once
#ifndef logical_values_array_H
#define LOGICAL_VALUES_ARRAY_H

#include <iostream>
#include <stdexcept>

class logical_values_array {
private:
    unsigned int _value;

public:
    // Constructor
    logical_values_array(unsigned int value = 0);

    // Getters
    unsigned int get_value() const;
    int get_bit(size_t position) const;
    int operator[](size_t position) const;

    // Mutator
    void set_value(unsigned int new_value);

    // Logic operation
    logical_values_array invert() const;
    logical_values_array conjunction(const logical_values_array& other) const;
    logical_values_array disjunction(const logical_values_array& other) const;
    logical_values_array xor_func(const logical_values_array& other) const;
    logical_values_array implication(const logical_values_array& other) const;
    logical_values_array coimplication(const logical_values_array& other) const;
    logical_values_array pierce_arrow(const logical_values_array& other) const;
    logical_values_array sheffer_stroke(const logical_values_array& other) const;

    // comparison
    static bool equals(const logical_values_array& first, const logical_values_array& second);

    // convert to string
    void to_binary_string(char* buffer, size_t buffer_size) const;
};

#endif
