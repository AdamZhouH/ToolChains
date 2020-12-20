#include <iostream>
#include "Message.hpp"
using namespace std;

int main(void) {
    Message say_hello("Hello, CMake World!");
    std::cout << say_hello << std::endl;
  
    Message say_goodbye("Goodbye, CMake World");
    std::cout << say_goodbye << std::endl;
    return 0;
}