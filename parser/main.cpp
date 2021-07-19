#include <iostream>
#include "nlohmann/json.hpp"
#include <fstream>

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
    std::cout << "Hello, World!" << std::endl;
    nlohmann::json input;
    input_file >> input;
    for (const auto& element : input.items()){
        std::cout << element.key() << ": " << element.value() << std::endl;
    }
    input_file.close();
    //return EXIT_SUCCESS;
    //abort();
    /*
    std::vector<size_t> a;
    for (size_t i = 0; i < 10; ++i){
        a[i] = i; // imitate sigsegv;
    }
     */
}
