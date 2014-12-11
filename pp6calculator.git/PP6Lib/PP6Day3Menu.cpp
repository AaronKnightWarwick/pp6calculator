//----------PP6Day3Menu.cpp----------
//----------===============----------

#include "PP6Day3Menu.hpp"

//----------Standard Library----------
//----------================----------

#include <iostream>
#include <limits>

//----------This Project----------
//----------============----------

#include "PP6FourVector.hpp"
#include "PP6Math.hpp"
#include "PP6Day3MuonAnalysis.hpp"

FourVector* userCreateFourVector(){
  double it, ix, iy, iz;

  std::cout << "Enter the t-component: ";
  it = getNumber();
  std::cout << "Enter the x-component: ";
  ix = getNumber();
  std::cout << "Enter the y-component: ";
  iy = getNumber();
  std::cout << "Enter the z-component: ";
  iz = getNumber();
 
  return createFourVector(it, ix, iy, iz);
}

//----------Menu Code----------
//----------=========----------

void pp6day3_menu(){
  FourVector *iV, *iU;
  double ivelocity;
  
  double res; 
  char menu3;

  while(true){
    std::cout << "                          " << std::endl;
    std::cout << "PP6Calculator - Day 3 Menu" << std::endl;
    std::cout << "==========================" << std::endl;
    std::cout << "                          " << std::endl;
    std::cout << "Please enter the operation you wish to perform:" << std::endl;
    std::cout << "Enter '1' to create a four vector and calculate its interval" << std::endl;
    std::cout << "Enter '2' to create and boost a four vector" << std::endl;
    std::cout << "Enter '3' to add two four vectors" << std::endl;
    std::cout << "Enter '4' to analyse input files for muon pairs (Day 3 version)" 
              << std::endl;
    std::cout << "Enter 'q' to quit" << std::endl;
    std::cout << "                 " << std::endl;
    
    std::cin >> menu3;
      
    if(!std::cin){
      std::cerr << "[ERROR] User input error" << std::endl;
      std::cin.clear();
      std::cin.ignore();
      continue;
    }

    if(menu3 == 'q'){
      break;
    }

    else if(menu3 == '1'){
      iV = userCreateFourVector();
      std::cout << "Interval = " << iV->interval() << std::endl;
      destroyFourVector(iV);    
    }
   
    else if(menu3 == '2'){
      iV = userCreateFourVector();

      std::cout << "Enter the boost speed along z: ";
      ivelocity = getNumber();

      res = iV->boost_z(ivelocity);
      if(!res){
        std::cout << "v = " << iV->asString() << std::endl;
        destroyFourVector(iV);
      }
    }
    
    else if(menu3 == '3'){
      std::cout << "Details for 1st FourVector:" << std::endl;
      iV = userCreateFourVector();
      std::cout << "Details for 2nd FourVector:" << std::endl;
      iU = userCreateFourVector();
      FourVector sum = (*iV) + (*iU);
      std::cout << "v = " << sum << std::endl;
      destroyFourVector(iV);
      destroyFourVector(iU);
    }
 
    else if(menu3 == '4'){
      res = pp6day3_muonanalysis();
    }
    
    else{
      std::cerr << "[ERROR] Operation '" << menu3 << "' not recognised."
                << std::endl;
      continue;
    }

    if(res){
      std::cerr << "[ERROR] Operation '" << menu3 << "' returned a non-zero code '" 
		<< res << "'. Please check parameters." << std::endl;
      res = 0;
      destroyFourVector(iV);
      destroyFourVector(iU);
      continue;
    }
  }
}
