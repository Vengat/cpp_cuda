#ifndef Checking_hpp
#define Checking_hpp

#include "Account.hpp"

class Checking : public Account {
public:
    // Alternate way of inheriting the base class constructor since Checking class just has the same constructor as the Account and its present only to invoke the Base constructor
    // Now the below command will inherit all the constructors from the base class
    using Account::Account;
//    Checking(const std::string &name, float balance);
    ~Checking();
    void WithDraw(float amount) override;
};
#endif
