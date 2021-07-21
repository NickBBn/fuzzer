//
// Created by niickson on 7/19/21.
//

#ifndef FUZZER_INPUT_GENERATOR_HPP
#define FUZZER_INPUT_GENERATOR_HPP

#define RANDOM(number) rand() % number + 1

#include <list>
#include <algorithm>
#include "nlohmann/json.hpp"

class input_generator {
public:
    virtual void generate(std::list<std::string>& inputs) = 0;
    virtual void generate_dummy(std::list<std::string>& inputs);
    virtual void generate_dummy_file(std::list<std::string>& inputs);
    virtual void generate_random_json(std::list<std::string>& inputs);
    virtual ~input_generator() = default;
    std::string random_string(const size_t& length);
};

std::string input_generator::random_string(const size_t &length) {
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

void input_generator::generate_dummy(std::list<std::string> &inputs) {
    inputs.emplace_back("nofile1");
    inputs.emplace_back("nofile2");
}

void input_generator::generate_dummy_file(std::list<std::string> &inputs) {
    const static std::string input_str = "input";
    std::ofstream out;
    for (auto i = 0; i < 5; ++i){
        std::string filename = input_str + std::to_string(i);
        out.open(filename);
        out << random_string(rand() % 6 + 1)<< std::endl;
        inputs.push_back(filename);
        out.close();
    }
}

void input_generator::generate_random_json(std::list<std::string> &inputs) {
    const static std::string input_str = "json";
    std::ofstream out;
    for (auto i = 0; i < 5; ++i){
        std::string filename = input_str + std::to_string(i);
        nlohmann::json json;
        out.open(filename);
        for(auto j = 0; j < rand() % 6 + 1; ++j){
            json[random_string(rand() % 6 + 1)] = random_string(rand() % 6 + 1);
        }
        out << json.dump() << std::endl;
        inputs.push_back(filename);
        out.close();
    }
}


#endif //FUZZER_INPUT_GENERATOR_HPP
