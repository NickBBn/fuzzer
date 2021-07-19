//
// Created by niickson on 7/19/21.
//

#ifndef FUZZER_ABSTRACT_INPUT_GENERATOR_HPP
#define FUZZER_ABSTRACT_INPUT_GENERATOR_HPP

#include <list>
#include <algorithm>

class abstract_input_generator {
public:
    virtual void generate(std::list<std::string>& inputs) = 0;
    virtual ~abstract_input_generator() = default;
    std::string random_string(const size_t& length);
};

std::string abstract_input_generator::random_string(const size_t &length) {
    auto randchar = []() -> char
    {
        static const char charset[] =
                "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}


#endif //FUZZER_ABSTRACT_INPUT_GENERATOR_HPP
