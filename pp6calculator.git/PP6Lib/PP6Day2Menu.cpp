//----------Day 2 Menu----------
//----------==========----------

#include "PP6Day2Menu.hpp"

//----------Standard Library----------
//----------================----------

#include <iostream>
#include <cmath>

//----------This Project----------
//----------============----------
#include "PP6Math.hpp"
#include "PP6Day2VectorAnalysis.hpp"
#include "PP6Day2MuonAnalysis.hpp"

//----------Main Code----------
//----------=========----------

void pp6day2_menu() {
  
  double res; 
  char menu2;

  while(true){
    
    std::cout << "                          " << std::endl;
    std::cout << "PP6Calculator - Day 2 Menu" << std::endl;
    std::cout << "==========================" << std::endl;
    std::cout << "Enter the operation you wish to perform:" << std::endl;
    std::cout << "Enter 1 to swap two numbers" << std::endl;
    std::cout << "Enter 2 to bubble sort an array of numbers" << std::endl;
    std::cout << "Enter 3 to generate and analyse N random 4-Vectors" 
	      << std::endl;
    std::cout << "Enter 4 to analyse input files for muon pairs" << std::endl;
    std::cout << "Enter q to quit to the main menu" << std::endl;
    std::cout << "                                " << std::endl;
    std::cout << "Enter you choice: " << std::endl;
    
    std::cin >> menu2;
      
    if(!std::cin){
      std::cerr << "[ERROR] User input error" << std::endl;
      std::cin.clear();
      std::cin.ignore();
      continue;
    }

    if(menu2 == 'q'){
      break;
    }
    
    else if(menu2 == '1'){
      
      double a, b;
      std::cout << "Enter the first number you wish to be swapped: ";
      a = input();
      std::cout << "Enter the second number you wish to be swapped: ";
      b = input();
 
      std::cout << "Before the swap a = " << a << " and b = " << b << std::endl;
      
      swap(a, b);
      
      std::cout << "A swap is being performed" << std::endl;

      std::cout << "After the swap a = " << a << " and b = " << b << std::endl; 
    }
    
    else if(menu2 == '2'){
      
      int arraysize;
      std::cout << "Enter the size of the array: ";
      arraysize = input();
      if(arraysize > 0){
        double *currentarray = new double[arraysize];
        for(int i = 0; i < arraysize; ++i){
	  std::cout << "Enter the value of element " << i << ": ";
          currentarray[i] = input();
        }

	std::cout << "Array before sorting:" << std::endl;
        printArray(currentarray, arraysize);
        
        bubblesort(currentarray, arraysize);
        
	std::cout << "Array after sorting:" << std::endl;
        printArray(currentarray, arraysize);
        
        delete [] currentarray;
      }
      
      else{
	std::cerr << "[ERROR]: Array size must be greater than 0" << std::endl;
      }
    }
    
    else if(menu2 == '3'){

      res = pp6day2_vectoranalysis();
    }
    
    else if(menu2 == '4'){

      res = pp6day2_muonanalysis();
    }
    
    else{
      std::cerr << "[ERROR] Operation '" << menu2 << "' is not valid"
                << std::endl;
      continue;
    }

    if(res){
      std::cerr << "[ERROR] The operation '" << menu2 
                << "' gave an error" << res << "' Check parameters."
                << std::endl;
      res = 0;
      continue;
    }
  }
}
