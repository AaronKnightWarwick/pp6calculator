//----------PP6Day2Menu.cpp----------
//----------===============----------

#include "PP6Day2Menu.hpp"

//----------Standard Library----------
//----------================----------

#include <iostream>
#include <cmath>
#include <limits>

//----------This Project----------
//----------============----------

#include "PP6Math.hpp"
#include "PP6Day2VectorAnalysis.hpp"
#include "PP6Day2MuonAnalysis.hpp"

//----------Main Code----------
//----------=========----------

void pp6day2_menu(){

  double res; 
  char menu2;

  while(true){
    std::cout << "                          " << std::endl;
    std::cout << "PP6Calculator - Day 2 Menu" << std::endl;
    std::cout << "==========================" << std::endl;
    std::cout << "                          " << std::endl;
    std::cout << "Please enter the operation you wish to perform:" << std::endl;
    std::cout << "Enter '1' to swap two numbers" << std::endl;
    std::cout << "Enter '2' to sort an array of numbers" << std::endl;
    std::cout << "Enter '3' to generate and analyse N random 4-Vectors" << std::endl;
    std::cout << "Enter '4' to analyse input files for muon pairs" << std::endl;
    std::cout << "Enter 'q' to quit" << std::endl;
    std::cout << "                 " << std::endl;
    
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
      std::cout << "Enter the first number: ";
      a = getNumber();
      std::cout << "Enter the second number: ";
      b = getNumber();
 
      std::cout << "Before swap (a,b) = (" << a << ", " << b << ")" 
                << std::endl;
      swap(a, b);
      std::cout << "After swap (a,b) = (" << a << ", " << b << ")"
                << std::endl; 
    }
    else if(menu2 == '2'){
      int arraySize;
      std::cout << "Enter the size of the array: ";
      arraySize = getNumber();
      if(arraySize > 0){
        double *currentArray = new double[arraySize];
        for(int i = 0; i < arraySize; ++i){
          std::cout << "Enter the value of element " << i << ": ";
          currentArray[i] = getNumber();
        }

        std::cout << "Array before sorting:" << std::endl;
        printArray(currentArray, arraySize);
        
        basic_sort(currentArray, arraySize);
        
        std::cout << "Array after sorting:" << std::endl;
        printArray(currentArray, arraySize);
        
        delete [] currentArray;
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
      std::cerr << "[ERROR] Operation '" << menu2 << "' not recognised." << std::endl;
      continue;
    }

    if(res){
      std::cerr << "[ERROR] Operation '" << menu2 << "' returned a non-zero code '" 
		<< res << "'. Please check parameters." << std::endl;
      res = 0;
      continue;
    }
  }
}
