//
// Created by niickson on 7/19/21.
//

#ifndef FUZZER_USUAL_INPUT_GENERATOR_HPP
#define FUZZER_USUAL_INPUT_GENERATOR_HPP

#include "abstract/input_generator.hpp"
#include <fstream>
#include "nlohmann/json.hpp"

class usual_input_generator: public input_generator {
public:
    void generate(std::list<std::string>& inputs) override;

private:
    void generate_modified_json(std::list<std::string>& inputs);
};

void usual_input_generator::generate(std::list<std::string>& inputs) {
    generate_dummy_file(inputs);
    generate_dummy(inputs);
    generate_random_json(inputs);
    generate_modified_json(inputs);
}

void usual_input_generator::generate_modified_json(std::list<std::string> &inputs) {
    const static std::string input_str = "modifiedjson";
    std::ofstream out;
    for (auto i = 0; i < 5; ++i){
        std::string filename = input_str + std::to_string(i);
        nlohmann::json json;
        out.open(filename);
        for(auto j = 0; j < RANDOM(6); ++j){
            json[random_string(RANDOM(6))] = random_string(RANDOM(6));
        }
        std::string json_str = json.dump();
        json_str.insert(RANDOM(6), "; }");
        out << json_str << std::endl;
        inputs.push_back(filename);
        out.close();
    }
}


#endif //FUZZER_USUAL_INPUT_GENERATOR_HPP
