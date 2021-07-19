//
// Created by niickson on 7/18/21.
//

#ifndef FUZZER_TARGET_OBSERVER_HPP
#define FUZZER_TARGET_OBSERVER_HPP

#include "abstract_observer.hpp"

class target_observer: public abstract_observer{
public:
    explicit target_observer(const pid_t& pid_): abstract_observer(pid_){}
    void observe(const std::string& filename) override {
        std::cout << "target observe" << std::endl;
    }
};


#endif //FUZZER_TARGET_OBSERVER_HPP
