//
// Created by niickson on 7/18/21.
//

#ifndef PARSER_USUAL_OBSERVER_HPP
#define PARSER_USUAL_OBSERVER_HPP

#include "abstract/observer.hpp"
#include <sstream>
#include <fstream>

class usual_observer: public observer{
public:
    explicit usual_observer(const pid_t& pid_): observer(pid_){}
    void observe(const std::string& filename) override;
};

void usual_observer::observe(const std::string& filename) {
    int status = 0;
    std::stringstream info;
    while(true){
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            status = WEXITSTATUS(status);
            info << "Child ended successfully with exit code "
                      << status << std::endl;
            std::cout << "Child ended successfully with exit code "
                 << status << std::endl;
            break;
        }
        if (WIFSTOPPED(status)){
            int signal = WSTOPSIG(status);
            if (signal != SIGTRAP){
                std::string signal_str = std::to_string(signal);
                if (signal == SIGABRT) signal_str += " SIGABRT";
                if (signal == SIGSEGV) signal_str += " SIGSEGV";
                info << "Child interrupted with signal " << signal_str << std::endl;
                std::cout << "Child interrupted with signal " << signal_str << std::endl;
                print_regs(info);
                ptrace(PTRACE_CONT, pid, NULL, NULL);
                break;
            }
        }
        ptrace(PTRACE_CONT, pid, NULL, NULL);
    }
    std::ofstream report(filename, std::ios::app);
    report << info.str() << std::endl;
    report.close();
}


#endif //PARSER_USUAL_OBSERVER_HPP
