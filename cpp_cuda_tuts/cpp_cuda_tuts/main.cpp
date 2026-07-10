//
//  main.cpp
//  cpp_cuda_tuts
//
//  Created by Vengat Ramanan on 08/04/26.
//

#include "Account.hpp"
#include <iostream>

int main(int argc, const char * argv[]) {
    // insert code here...
    
    //std::cout << "Hello, World!\n";
    
    Account acc {"Vengat", 1000};
    std::cout << "Initial balance " << acc.GetBalance() << std::endl;
    
    acc.Deposit(1000);
    std::cout << "Get account balance " << acc.GetBalance() << std::endl;
    
    return EXIT_SUCCESS;
}

