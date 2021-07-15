#include <iostream>

#include "sys/ptrace.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "sys/user.h"
#include "sys/reg.h"
#include "sys/syscall.h"

int main() {
    long orig_rax;
    int status = 0;
    pid_t pid = fork();
    if (pid == 0){ //child process
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execl("parser", (const char*)nullptr, (char*)nullptr);
    } else { //parent process
        while(true){
            wait(&status);
            std::cout << status << std::endl;
            if (WIFSTOPPED(status)){
                int stop_status = WSTOPSIG(status);
                if (stop_status != SIGTRAP){
                    std::cout << "stop signal = " << stop_status << std::endl;
                    orig_rax = ptrace(PTRACE_PEEKUSER, // GETREGS
                                      pid, 8 * ORIG_RAX,
                                      NULL);
                    printf("The child made a "
                           "system call %ld\n", orig_rax);
                    int res = ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
                    break;
                }
            }
            if (WIFEXITED(status)) break;

            orig_rax = ptrace(PTRACE_PEEKUSER,
                              pid, 8 * ORIG_RAX,
                              NULL);
            printf("The child made a "
                   "system call %ld\n", orig_rax);
            ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
        }
    }
    std::cout << std::endl << status;
    return 0;
}
