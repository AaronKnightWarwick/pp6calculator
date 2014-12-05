//----------Day 3 Menu----------
//----------==========----------

#include "PP6Day3Menu.hpp"

//----------Standard Library----------
//----------================----------

#include <iostream>

//----------This Project----------
//----------============----------

#include "PP6FourVector.hpp"
#include "PP6Math.hpp"

//-----------------------------------

FourVector* userCreateFourVector(){

  double it, ix, iy, iz;
  
  std::cout << "Enter the t-component: ";
  it = input();
  std::cout << "Enter the x-component: ";
  ix = input();
  std::cout << "Enter the y-component: ";
  iy = input();
  std::cout << "Enter the z-component: ";
  iz = input();

  return createFourVector(it, ix, iy, iz);
}

//----------Main Code----------
//----------=========----------

void pp6day3_menu()
{

  FourVector *iV, *iU;
  double ivelocity;
  double res;
  char menu3;
  
  while(true){

    std::cout << "                          " << std::endl;
    std::cout << "PP6Calculator - Day 3 Menu" << std::endl;
    std::cout << "==========================" << std::endl;
    std::cout << "Enter the operation you wish to perform:" << std::endl;
    std::cout << "Enter 1 to creat a 4-vector and to calculate its interval" 
	      << std::endl;
    std::cout << "Enter 2 to create a 4-vector and to boost it to a new frame of referecnce" << std::endl;
    std::cout << "Enter 3 to add two 4-vector together" << std::endl;
    std::cout << "Enter 4 to analyse muon pairs" << std::endl;
    std::cout << "Enter q to quit to the main menu" << std::endl;
    std::cout << "                                " << std::endl;
    std::cout << "Enter your choice here: " << std::endl;
      
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
      std::cout << "[result]: interval = " << iV->interval() << std::endl;
      destroyFourVector(iV);
    }
    else if(menu3 == '2'){
	iV = userCreateFourVector();
	std::cout << "Enter the boost speed along z: ";
	ivelocity = input();
	res = iV->boost_z(ivelocity);
	if(!res){
	    std::cout << "[result] v = " << iV->asString() << std::endl;
	    destroyFourVector(iV);
	  }
      }
    else if(menu3 == '3'){
	std::cout << "Details for 1st FourVector:" << std::endl;
	iV = userCreateFourVector();
	std::cout << "Details for 2nd FourVector:" << std::endl;
	iU = userCreateFourVector();
	FourVector sum = (*iV) + (*iU);
	std::cout << "[result] v = " << sum << std::endl;
	destroyFourVector(iV);
	destroyFourVector(iU);
      }
    else if(menu3 == '4'){
      std::cout << "UNDER CONSTRUCTION" << std::endl;
      }
    else
      {
	std::cerr << "[error] Operation '" << menu3 << "' not recognised."
		  << std::endl;
	continue;
      }
    
    if(res){
	std::cerr << "[ERROR] Operation '" << menu3
		  << "' returned a non-zero code '" << res
		  << "'. Please check parameters."
		  << std::endl;
	res = 0;
	destroyFourVector(iV);
	destroyFourVector(iU);
	continue;
      }
  }
}
