//
// Created by niickson on 7/18/21.
//

#ifndef PARSER_MODULES_HPP
#define PARSER_MODULES_HPP

#include "usual/usual_observer.hpp"
#include "target/target_input_generator.hpp"
#include "usual/usual_launcher.hpp"
#include "usual/usual_input_generator.hpp"
#include "memory"

class abstract_module {
protected:
    abstract_module(){
        srand(time(NULL));
    }
public:
    virtual std::unique_ptr<observer> create_observer(const pid_t& pid_) const = 0;
    virtual std::unique_ptr<launcher> create_launcher(const std::string& exe) const = 0;
    virtual std::unique_ptr<input_generator> create_input_generator() const = 0;
};

class usual_module: public abstract_module {
public:
    std::unique_ptr<observer> create_observer(const pid_t& pid_) const override{
        return std::make_unique<usual_observer>(usual_observer(pid_));
    }
    std::unique_ptr<launcher> create_launcher(const std::string& exe) const override{
        return std::make_unique<usual_launcher>(usual_launcher(exe));
    }
    std::unique_ptr<input_generator> create_input_generator() const override{
        return std::make_unique<usual_input_generator>(usual_input_generator());
    }
};

class target_module: public abstract_module {
public:
    std::unique_ptr<observer> create_observer(const pid_t& pid_) const override{
        return std::make_unique<usual_observer>(usual_observer(pid_));
    }
    std::unique_ptr<launcher> create_launcher(const std::string& exe) const override{
        return std::make_unique<usual_launcher>(usual_launcher(exe));
    }
    std::unique_ptr<input_generator>create_input_generator() const override{
        return std::make_unique<target_input_generator>(target_input_generator());
    }
};



#endif //PARSER_MODULES_HPP
