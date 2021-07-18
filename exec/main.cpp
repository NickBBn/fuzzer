#include <iostream>
#include "nlohmann/json.hpp"
#include <vector>
#include "sys/types.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    //return EXIT_SUCCESS;
    //abort();
    std::vector<size_t> a;
    for (size_t i = 0; i < 10; ++i){
        a[i] = i; // imitate sigsegv;
    }
}
