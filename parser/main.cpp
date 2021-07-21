#include <iostream>
#include "nlohmann/json.hpp"
#include <fstream>

bool target_function(const nlohmann::json& json, std::ostream& out){
    if (json["key1"] != "static string"){
        return false;
    }
    if (json["search_type"] == "STACK"){
        out << "STACK " << json["key2"] << std::endl;
    } else if (json["search_type"] == "QUEUE"){
        out << "QUEUE " << json["key2"] << std::endl;
    } else return false;
    return true;
}

int main(int argc, char* argv[]) {
    if (argc != 2 ){
        std::cout << "Program requires argument" << std::endl;
        return EXIT_FAILURE;
    }
    std::string filename = argv[1];
    std::ifstream input_file;
    input_file.open(filename);
    if (!input_file.is_open()){
        std::cout << "could not open file" << std::endl;
        return EXIT_FAILURE;
    }

    nlohmann::json input;
    input_file >> input;
    bool res;
    if (input.contains("key1")){
        res = target_function(input, std::cout);
        if (!res) return EXIT_FAILURE;
    }
    for (const auto& element : input.items()){
        std::cout << element.key() << ": " << element.value() << std::endl;
    }
    input_file.close();
    return EXIT_SUCCESS;
}
