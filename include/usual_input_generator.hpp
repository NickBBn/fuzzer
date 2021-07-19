//
// Created by niickson on 7/19/21.
//

#ifndef FUZZER_USUAL_INPUT_GENERATOR_HPP
#define FUZZER_USUAL_INPUT_GENERATOR_HPP

#include "abstract_input_generator.hpp"
#include <fstream>

class usual_input_generator: public abstract_input_generator {
public:
    void generate(std::list<std::string>& inputs) override;

private:
    void generate_dummy(std::list<std::string>& inputs);
    void generate_dummy_file(std::list<std::string>& inputs);
};

void usual_input_generator::generate(std::list<std::string>& inputs) {
    generate_dummy_file(inputs);
    generate_dummy(inputs);
}

void usual_input_generator::generate_dummy(std::list<std::string> &inputs) {
    inputs.push_back("nofile1");
    inputs.push_back("nofile2");
}

void usual_input_generator::generate_dummy_file(std::list<std::string>& inputs) {
    const static std::string input_str = "input";
    std::ofstream out;
    for (auto i = 0; i < 5; ++i){
        std::string filename = input_str + std::to_string(i);
        out.open(filename);
        out << i << " dsaf " << std::endl;
        inputs.push_back(filename);
        out.close();
    }
}


#endif //FUZZER_USUAL_INPUT_GENERATOR_HPP
