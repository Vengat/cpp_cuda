#ifndef Account_hpp
#define Account_hpp

#include <iostream>


class Account {
private:
    int m_AccNo;
    std::string m_Name;
    static int s_ANGenerator;
protected:
    float m_Balance;
    
public:
    Account(const std::string &name, float balance);
    virtual ~Account();
    
    
    const std::string GetName() const;
    float GetBalance() const;
    const int GetAccountNumber() const;
    
    virtual void WithDraw(float amount);
    virtual void AccumulateInterest();
    void Deposit(float amount);
    virtual float GetInterestRate() const;
    
};
#endif

