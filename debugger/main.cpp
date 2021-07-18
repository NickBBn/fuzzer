#include <iostream>
#include "sys/ptrace.h"
#include <sys/wait.h>
#include <unistd.h>
#include "modules.hpp"

int main() {
    auto* module = new usual_module();
    //auto* module = new target_module();
    pid_t pid = fork();
    abstract_observer* observer = module->create_observer(pid);
    observer->observe();
}
