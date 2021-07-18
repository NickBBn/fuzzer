//
// Created by niickson on 7/18/21.
//

#ifndef FUZZER_TARGET_OBSERVER_HPP
#define FUZZER_TARGET_OBSERVER_HPP

#include "abstract_observer.hpp"

class target_observer: public abstract_observer{
public:
    void iamchild() const override{
        std::cout << "Target observer" << std::endl;
    }
};


#endif //FUZZER_TARGET_OBSERVER_HPP
