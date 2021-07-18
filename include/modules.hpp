//
// Created by niickson on 7/18/21.
//

#ifndef PARSER_MODULES_HPP
#define PARSER_MODULES_HPP

#include "usual_observer.hpp"
#include "target_observer.hpp"

class abstract_module {
public:
    virtual abstract_observer* create_observer(const pid_t& pid_) const = 0;
};

class usual_module: public abstract_module {
public:
    abstract_observer* create_observer(const pid_t& pid_) const override{
        return new usual_observer(pid_);
    }
};

class target_module: public abstract_module {
public:
    abstract_observer* create_observer(const pid_t& pid_) const override{
        return new target_observer(pid_);
    }
};



#endif //PARSER_MODULES_HPP
