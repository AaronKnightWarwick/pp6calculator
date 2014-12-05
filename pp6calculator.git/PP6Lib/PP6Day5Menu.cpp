//----------Day 5 Menu----------
//----------==========----------

#include "PP6Day5Menu.hpp"

//----------Standard Library----------
//----------================----------

#include <iostream>

//----------This Project----------
//----------============----------

#include "PP6Math.hpp"

//----------Main Code----------
//----------=========----------

void pp6day5_menu()
{

  double res;
  char menu5;
  
  while(true){

    std::cout << "                          " << std::endl;
    std::cout << "PP6Calculator - Day 5 Menu" << std::endl;
    std::cout << "==========================" << std::endl;
    std::cout << "Enter the operation you wish to perform:" << std::endl;
    std::cout << "UNDER CONSTRUCTION" << std::endl;
    std::cout << "Enter q to quit to the main menu" << std::endl;
    std::cout << "                                " << std::endl;
    std::cout << "Enter your choice here: " << std::endl;
      
    std::cin >> menu5;
    
    if(!std::cin){
      std::cerr << "[ERROR] User input error" << std::endl;
      std::cin.clear();
      std::cin.ignore();
      continue;
    }
      
    if(menu5 == 'q'){
      break;
    }
    
    else{
      std::cerr << "[ERROR] The operation '" << menu5 << "' is invalid"
		<< std::endl;
      continue;
    }
    
    if(res){
      std::cerr << "[ERROR] Operation '" << menu5
		<< "' returned a non-zero code '" << res
		<< "'. Please check parameters."
		<< std::endl;
      res = 0;
      continue;
    }
  }
}
