//
// Created by niickson on 7/19/21.
//

#ifndef FUZZER_ABSTRACT_LAUNCHER_HPP
#define FUZZER_ABSTRACT_LAUNCHER_HPP


class abstract_launcher {
public:
    virtual pid_t launch(const std::string& filename) = 0;
    virtual ~abstract_launcher() = default;
protected:
    explicit abstract_launcher(const std::string& exe):executable(exe){}
    std::string executable{};
};


#endif //FUZZER_ABSTRACT_LAUNCHER_HPP
