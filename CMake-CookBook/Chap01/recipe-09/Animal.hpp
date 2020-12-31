#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <string>

class Animal {
public:
    Animal() = delete;
    explicit Animal(const std::string &n);
    std::string name() const;
    virtual ~Animal() {};
protected:
    std::string name_;
private:
    virtual std::string name_impl() const = 0;
};

#endif