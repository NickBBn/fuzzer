//
// Created by niickson on 7/18/21.
//

#ifndef PARSER_USUAL_OBSERVER_HPP
#define PARSER_USUAL_OBSERVER_HPP

#include "abstract_observer.hpp"

class usual_observer: public abstract_observer{
public:
    explicit usual_observer(const pid_t& pid_): abstract_observer(pid_){}
    void observe() override{
        int status = 0;
        if (pid == -1){
            std::cout << "Unable to create child process";
            throw;
        } else if (pid == 0){ //child process
            ptrace(PTRACE_TRACEME, 0, NULL, NULL);
            execl("parser", (const char*)nullptr, (char*)nullptr);
        } else { //parent process
            while(true){
                wait(&status);
                if (WIFEXITED(status)) {
                    std::cout << "Child ended successfully" << std::endl;
                    break;
                }
                if (WIFSTOPPED(status)){
                    int signal = WSTOPSIG(status);
                    if (signal != SIGTRAP){
                        std::cout << "Child interrupted witn signal " << signal << std::endl;
                        print_regs(std::cout);
                        ptrace(PTRACE_CONT, pid, NULL, NULL);
                        break;
                    }
                }
                ptrace(PTRACE_CONT, pid, NULL, NULL);
            }
        }
    }
};


#endif //PARSER_USUAL_OBSERVER_HPP
