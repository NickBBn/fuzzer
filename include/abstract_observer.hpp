
#ifndef PARSER_ABSTRACT_OBSERVER_HPP
#define PARSER_ABSTRACT_OBSERVER_HPP

#include <iostream>
#include "sys/ptrace.h"
#include <sys/wait.h>
#include <unistd.h>
#include "sys/user.h"

class abstract_observer {
public:
    void print_regs(std::ostream& out) const;
    virtual void observe(const std::string& filename) = 0;
    virtual ~abstract_observer() = default;
protected:
    explicit abstract_observer(const pid_t& pid_): pid(pid_){};
    pid_t pid;
};

void abstract_observer::print_regs(std::ostream &out) const {
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


#endif //PARSER_ABSTRACT_OBSERVER_HPP
