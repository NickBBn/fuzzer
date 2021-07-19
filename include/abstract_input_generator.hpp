//
// Created by niickson on 7/19/21.
//

#ifndef FUZZER_ABSTRACT_INPUT_GENERATOR_HPP
#define FUZZER_ABSTRACT_INPUT_GENERATOR_HPP

#include <list>

class abstract_input_generator {
public:
    virtual void generate(std::list<std::string>& inputs) = 0;
    virtual ~abstract_input_generator() = default;
};


#endif //FUZZER_ABSTRACT_INPUT_GENERATOR_HPP
