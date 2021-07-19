#include <iostream>
#include <list>
#include "modules.hpp"

int main() {
    auto* module = new usual_module();
    std::list<std::string> inputs;
    //auto* module = new target_module();
    abstract_input_generator* input_generator = module->create_input_generator();
    input_generator->generate(inputs);
    for (const auto& input_filename : inputs){
        std::cout << "------------------------------" << std::endl
                  << "current input: " << input_filename << std::endl;
        abstract_launcher* launcher = module->create_launcher("parser");
        pid_t pid = launcher->launch(input_filename);
        abstract_observer* observer = module->create_observer(pid);
        observer->observe(input_filename);
        delete launcher;
        delete observer;
    }
    delete input_generator;
    delete module;
    return EXIT_SUCCESS;
}
