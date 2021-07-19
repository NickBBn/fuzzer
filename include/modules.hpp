//
// Created by niickson on 7/18/21.
//

#ifndef PARSER_MODULES_HPP
#define PARSER_MODULES_HPP

#include "usual_observer.hpp"
#include "target_observer.hpp"
#include "usual_launcher.hpp"
#include "usual_input_generator.hpp"

class abstract_module {
protected:
    abstract_module(){
        srand(time(NULL));
    }
public:
    virtual abstract_observer* create_observer(const pid_t& pid_) const = 0;
    virtual abstract_launcher* create_launcher(const std::string& exe) const = 0;
    virtual abstract_input_generator* create_input_generator() const = 0;
};

class usual_module: public abstract_module {
public:
    abstract_observer* create_observer(const pid_t& pid_) const override{
        return new usual_observer(pid_);
    }
    abstract_launcher* create_launcher(const std::string& exe) const override{
        return new usual_launcher(exe);
    }
    abstract_input_generator* create_input_generator() const override{
        return new usual_input_generator;
    }
};

class target_module: public abstract_module {
public:
    abstract_observer* create_observer(const pid_t& pid_) const override{
        return new target_observer(pid_);
    }
};



#endif //PARSER_MODULES_HPP
