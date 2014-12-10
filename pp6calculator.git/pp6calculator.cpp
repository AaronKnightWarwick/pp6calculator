//----------Standard Library----------
//----------================----------

#include <iostream>
#include <limits>

//----------This Project----------
//----------============----------

#include "PP6Day1Menu.hpp"
#include "PP6Day2Menu.hpp"
#include "PP6Day3Menu.hpp"
#include "PP6Day4Menu.hpp"
#include "PP6Day5Menu.hpp"

//----------Main Code----------
//----------=========----------

int main() 
{
  char menu;

  while(true) {
    std::cout << "                              " << std::endl;
    std::cout << "Welcome to the PP6 Calculator!" << std::endl;
    std::cout << "                              " << std::endl;
    std::cout << "PP6Calculator - Main Menu" << std::endl;
    std::cout << "=========================" << std::endl;
    std::cout << "                         " << std::endl;
    std::cout << "Please enter which operation you wish to perform:" << std::endl;
    std::cout << "Enter '1' for day 1 basic mathematical operations" << std::endl;
    std::cout << "Enter '2' for day 2 array operations" << std::endl;
    std::cout << "Enter '3' for day 3 four vector operations" << std::endl;
    std::cout << "Enter '4' for day 4 standard library operations" << std::endl;
    std::cout << "Enter '5' for day 5" << std::endl;
    std::cout << "Enter 'q' to quit" << std::endl;
    std::cout << "                 " << std::endl;

    std::cin >> menu;

    if(!std::cin){
      std::cerr << "[ERROR] User input error" << std::endl;
      std::cin.clear();
      std::cin.ignore();
      continue;
    }

    if(menu == 'q'){
      break;
    }
    else if(menu == '1'){
      pp6day1_menu();
    }
    else if(menu == '2'){
      pp6day2_menu();
    }
    else if(menu == '3'){
      pp6day3_menu();
    }
    else if(menu == '4'){
      pp6day4_menu();
    }
    else if(menu == '5'){
      pp6day5_menu();
    }
    else{
      std::cerr << "[ERROR] Operation '" << menu << "' not recognised."
                << std::endl;
      continue;
    }
  }
 
  std::cout << "Thank you for using pp6calculator!" << std::endl;
  return 0;
}

