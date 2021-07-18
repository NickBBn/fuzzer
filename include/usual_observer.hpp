//
// Created by niickson on 7/18/21.
//

#ifndef PARSER_USUAL_OBSERVER_HPP
#define PARSER_USUAL_OBSERVER_HPP

#include "abstract_observer.hpp"

class usual_observer: public abstract_observer{
public:
    void iamchild() const override{
        std::cout << "Usual observer" << std::endl;
    }
};


#endif //PARSER_USUAL_OBSERVER_HPP
