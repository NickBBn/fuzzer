//
// Created by niickson on 7/19/21.
//

#ifndef FUZZER_USUAL_INPUT_GENERATOR_HPP
#define FUZZER_USUAL_INPUT_GENERATOR_HPP

#include "abstract_input_generator.hpp"
#include <fstream>
#include "nlohmann/json.hpp"

class usual_input_generator: public abstract_input_generator {
public:
    void generate(std::list<std::string>& inputs) override;

private:
    void generate_dummy(std::list<std::string>& inputs);
    void generate_dummy_file(std::list<std::string>& inputs);
    void generate_random_json(std::list<std::string>& inputs);
    void generate_modified_json(std::list<std::string>& inputs);
};

void usual_input_generator::generate(std::list<std::string>& inputs) {
    generate_dummy_file(inputs);
    generate_dummy(inputs);
    generate_random_json(inputs);
    generate_modified_json(inputs);
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
        out << random_string(rand() % 6 + 1)<< std::endl;
        inputs.push_back(filename);
        out.close();
    }
}

void usual_input_generator::generate_random_json(std::list<std::string> &inputs) {
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

void usual_input_generator::generate_modified_json(std::list<std::string> &inputs) {
    const static std::string input_str = "modifiedjson";
    std::ofstream out;
    for (auto i = 0; i < 5; ++i){
        std::string filename = input_str + std::to_string(i);
        nlohmann::json json;
        out.open(filename);
        for(auto j = 0; j < rand() % 6 + 1; ++j){
            json[random_string(rand() % 6 + 1)] = random_string(rand() % 6 + 1);
        }
        std::string json_str = json.dump();
        json_str.insert(rand() % 6 + 1, "; }");
        out << json_str << std::endl;
        inputs.push_back(filename);
        out.close();
    }
}


#endif //FUZZER_USUAL_INPUT_GENERATOR_HPP
