//----------Day 3 Menu----------
//----------==========----------

#include "PP6Day4Menu.hpp"

//----------Standard Library----------
//----------================----------

#include <iostream>

//----------This Project----------
//----------============----------

#include "PP6Math.hpp"

//----------Main Code----------
//----------=========----------

void pp6day4_menu()
{

  double res;
  char menu4;
  
  while(true){

    std::cout << "                          " << std::endl;
    std::cout << "PP6Calculator - Day 4 Menu" << std::endl;
    std::cout << "==========================" << std::endl;
    std::cout << "Enter the operation you wish to perform:" << std::endl;
    std::cout << "UNDER CONSTRUCTION" << std::endl;
    std::cout << "Enter q to quit to the main menu" << std::endl;
    std::cout << "                                " << std::endl;
    std::cout << "Enter your choice here: " << std::endl;
      
    std::cin >> menu4;
    
    if(!std::cin){
      std::cerr << "[ERROR] User input error" << std::endl;
      std::cin.clear();
      std::cin.ignore();
      continue;
    }
      
    if(menu4 == 'q'){
      break;
    }
    
    else{
      std::cerr << "[ERROR] The operation '" << menu4 << "' is invalid"
		<< std::endl;
      continue;
    }
    
    if(res){
      std::cerr << "[ERROR] Operation '" << menu4
		<< "' returned a non-zero code '" << res
		<< "'. Please check parameters."
		<< std::endl;
      res = 0;
      continue;
    }
  }
}
