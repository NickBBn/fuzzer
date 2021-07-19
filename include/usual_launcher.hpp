//
// Created by niickson on 7/19/21.
//

#ifndef FUZZER_USUAL_LAUNCHER_HPP
#define FUZZER_USUAL_LAUNCHER_HPP

#include "abstract_launcher.hpp"

class usual_launcher: public abstract_launcher {
public:
    explicit usual_launcher(const std::string& exe): abstract_launcher(exe){}
    pid_t launch(const std::string& filename) override;
};

pid_t usual_launcher::launch(const std::string& filename) {
    pid_t pid = fork();
    if (pid == -1){
        std::cout << "Unable to create child process";
        throw;
    } else if (pid == 0){ //child process
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execl(executable.c_str(), executable.c_str(), filename.c_str());
        exit(EXIT_SUCCESS);
    }
    return pid;
}


#endif //FUZZER_USUAL_LAUNCHER_HPP
