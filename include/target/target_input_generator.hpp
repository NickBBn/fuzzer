#ifndef FUZZER_TARGET_INPUT_GENERATOR_HPP
#define FUZZER_TARGET_INPUT_GENERATOR_HPP

#include "abstract/input_generator.hpp"

class target_input_generator: public input_generator {
public:
    void generate(std::list<std::string>& inputs) override;

private:
    void generate_modified_json(std::list<std::string>& inputs);
};

void target_input_generator::generate(std::list<std::string> &inputs) {
    generate_dummy_file(inputs);
    generate_dummy(inputs);
    generate_random_json(inputs);
    generate_modified_json(inputs);
}

void target_input_generator::generate_modified_json(std::list<std::string> &inputs) {
    const static std::string input_str = "modifiedjson";
    std::ofstream out;
    static const nlohmann::json json_orig = {
            {"key1",        "static string"},
            {"key2",        "input"},
            {"array",       {"abracatabra", "blablabla", "yahooooooo!"}},
            {"search_type", "QUEUE"}
    };
    for (auto i = 0; i < 10; ++i) {
        std::string filename = input_str + std::to_string(i);
        nlohmann::json json = json_orig;
        if (RANDOM(10) > 7) json["key1"] = random_string(RANDOM(6));
        if (RANDOM(10) > 9) json.erase("key1");
        if (RANDOM(10) > 9) json["key1"] = random_string(RANDOM(6));
        if (RANDOM(2)) json["search_type"] = "STACK";
        if (RANDOM(10) > 9) json["search_type"] = random_string(RANDOM(6));
        if (RANDOM(10) > 8) json.erase("search_type");
        out.open(filename);
        out << json.dump() << std::endl;
        inputs.push_back(filename);
        out.close();
    }
}

#endif //FUZZER_TARGET_INPUT_GENERATOR_HPP
