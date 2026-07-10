#include "Checking.hpp"
#include <iostream>

Checking::Checking(const std::string &name, float balance) : Account(name, balance) {}

Checking::~Checking() {}

void Checking::WithDraw(float amount) {
    if (m_Balance - amount > 50) {
        //m_Balance -= amount; another ways is
        Account::WithDraw(amount);
    } else {
        std::cout << "Insufficient funds " << std::endl;
    }
}
