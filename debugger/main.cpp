#include <iostream>
#include "sys/ptrace.h"
#include <sys/wait.h>
#include <unistd.h>
#include "modules.hpp"

/*
void print_regs(const pid_t& pid, std::ostream& out){
    struct user_regs_struct regs{};
    ptrace(PTRACE_GETREGS, pid, NULL, &regs);
    out << "REGS: " << std::endl << std::hex << std::uppercase
        << "ORIG_RAX " << regs.orig_rax << std::endl
        << "RAX " << regs.rax << std::endl
        << "RBX " << regs.rbx << std::endl
        << "RCX " << regs.rcx << std::endl
        << "RDX " << regs.rdx << std::endl
        << "RDI " << regs.rdi << std::endl
        << "RSI " << regs.rsi << std::endl
        << "CS " << regs.cs << std::endl
        << "DS " << regs.ds << std::endl
        << "ES " << regs.es << std::endl
        << "SS " << regs.ss << std::endl
        << "FS " << regs.fs << std::endl
        << "FS_BASE " << regs.fs_base << std::endl
        << "GS " << regs.gs << std::endl
        << "GS_BASE " << regs.gs_base << std::endl
        << "RIP " << regs.rip << std::endl
        << "RBP " << regs.rbp << std::endl
        << "RSP " << regs.rsp << std::endl
        << "EFLAGS " << regs.eflags << std::endl
        << "R8 " << regs.r8 << std::endl
        << "R9 " << regs.r9 << std::endl
        << "R10 " << regs.r10 << std::endl
        << "R11 " << regs.r11 << std::endl
        << "R12 " << regs.r12 << std::endl
        << "R12 " << regs.r13 << std::endl
        << "R14 " << regs.r14 << std::endl
        << "R15 " << regs.r15 << std::endl;

}
*/
int main() {
    auto* module = new usual_module();
    const abstract_observer* observer = module->create_observer();
    int status = 0;
    pid_t pid = fork();
    if (pid == -1){
        std::cout << "Unable to create child process";
        return EXIT_FAILURE;
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
                    observer->print_regs(pid, std::cout);
                    observer->iamchild();
                    ptrace(PTRACE_CONT, pid, NULL, NULL);
                    break;
                }
            }
            ptrace(PTRACE_CONT, pid, NULL, NULL);
        }
    }
    return EXIT_SUCCESS;
}
