//----------PP6 Day 3 Menu----------
//----------==============----------

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

//----------Main Code----------
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
    std::cout << "Enter the operation you with to perform:" << std::endl;
    std::cout << "1 - Create a FourVector and calculate its interval" << std::endl;
    std::cout << "2 - Create and Boost a FourVector" << std::endl;
    std::cout << "3 - Add two FourVectors" << std::endl;
    std::cout << "4 - Analyse input files for muon pairs (Day 3 version)"
              << std::endl;
    std::cout << "5 - Determine if a given FourVector is space/timelike" << std::endl;
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
      std::cout << "[RESULT]: interval = " << iV->interval() << std::endl;
      destroyFourVector(iV);
    }
    else if(menu3 == '2'){
      iV = userCreateFourVector();
      std::cout << "Enter the boost speed along z: ";
      ivelocity = getNumber();
      res = iV->boost_z(ivelocity);
      if(!res){
        std::cout << "[RESULT] v = " << iV->asString() << std::endl;
        destroyFourVector(iV);
      }
    }
    else if(menu3 == '3'){
      std::cout << "Details for 1st FourVector:" << std::endl;
      iV = userCreateFourVector();
      std::cout << "Details for 2nd FourVector:" << std::endl;
      iU = userCreateFourVector();
      FourVector sum = (*iV) + (*iU);
      std::cout << "[RESULT] v = " << sum << std::endl;
      destroyFourVector(iV);
      destroyFourVector(iU);
    }
    else if(menu3 == '4'){
      res = pp6day3_muonanalysis();
    }
    else if(menu3 == '5'){
      iV = userCreateFourVector();
      FourVector::CausalType oT = iV->getCausalType();
      std::cout << "[RESULT]: v " << iV->asString() << " is " << asString(oT) << std::endl;
      destroyFourVector(iV);
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
