#ifndef CAT_HPP
#define CAT_HPP

#include "Animal.hpp"

class Cat : public Animal {
public:
    Cat(const std::string &n) : Animal(n) { }
private:
    std::string name_impl() const override;
};

#endif