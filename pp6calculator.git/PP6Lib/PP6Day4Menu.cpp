//----------PP6Day4Menu.cpp----------
//----------===============----------

#include "PP6Day4Menu.hpp"

//----------Standard Library----------
//----------================----------

#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <vector>

//----------Third party----------
//----------===========----------

#include "FileReader.hpp"

//----------This Project----------
//----------============----------

#include "PP6Math.hpp"
#include "PP6ParticleInfo.hpp"
#include "PP6Day4MuonAnalysis.hpp"

//----------Main Code----------
//----------=========----------

int pp6day4_io_pdg() {
  std::string dbtFilename;
  std::cout << "Enter path to .dbt file to be read: ";
  dbtFilename = getString();

  FileReader dataBase(dbtFilename);

  if(!dataBase.isValid()){
    std::cerr << "[pp6day4_io_pdg:error] "
              << dbtFilename
              << " is not a valid file"
              << std::endl;
    return 1;
  } 

  else{
    std::vector<std::string> particleName;
    std::vector<int> particlePdgCode;
    std::vector<int> particleCharge;
    std::vector<double> particleMass;

    while(dataBase.nextLine()){
      particleName.push_back(dataBase.getField<std::string>(1));
      if(dataBase.inputFailed()){
        std::cout << "Could not get field 1 as std::string" << std::endl;
        continue;
      }

      particlePdgCode.push_back(dataBase.getField<int>(2));
      if(dataBase.inputFailed()){
        std::cout << "Could not get field 2 as int" << std::endl;
        continue;
      }
      particleCharge.push_back(dataBase.getField<int>(3));
      if(dataBase.inputFailed()){
        std::cout << "Could not get field 3 as int" << std::endl;
        continue;
      }

      particleMass.push_back(dataBase.getField<double>(4));
      if(dataBase.inputFailed()){
        std::cout << "Could not get field 4 as double" << std::endl;
        continue;
      }
    }

    std::vector<std::string>::iterator nameIter(particleName.begin());
    std::vector<std::string>::iterator stopCond(particleName.end());

    std::vector<int>::iterator pdgIter = particlePdgCode.begin();
    std::vector<int>::iterator chargeIter = particleCharge.begin();
    std::vector<double>::iterator massIter = particleMass.begin();
  
    for(; nameIter != stopCond; ++nameIter, ++pdgIter, ++chargeIter, ++massIter){
      std::cout << *nameIter << " " << *pdgIter << " " << *chargeIter << " "
                << *massIter << std::endl;
    }
  }

  return 0;
}

int pp6day4_check_particleinfo() {
  std::string dbtFilename;
  std::cout << "Enter path to .dbt file for initializing ParticleInfo: ";
  dbtFilename = getString();

  const ParticleInfo& dataBase = ParticleInfo::Instance(dbtFilename);

  std::cout << "Checking ParticleInfo contains entries... ";
  if(!dataBase.size()){
    std::cout << "fail" << std::endl;
    return 1;
  }

  else{
    std::cout << "ok" << std::endl;
  }

  std::cout << "Checking ParticleInfo returns correct mu- PDG code... ";
  if(dataBase.getPDGCode("mu-") != 13){
    std::cout << "fail" << std::endl;
    return 1;
  } 

  else{
    std::cout << "ok" << std::endl;
  }

  std::cout << "Checking ParticleInfo returns correct mu+ PDG code... ";
  if(dataBase.getPDGCode("mu+") != -13){
    std::cout << "fail" << std::endl;
    return 1;
  } 

  else{
    std::cout << "ok" << std::endl;
  }

  std::cout << "Checking ParticleInfo returns +ve mass for mu-... ";
  if(dataBase.getMassMeV(13) <= 0.0){
    std::cout << "fail" << std::endl;
    return 1;
  } 

  else{
    std::cout << "ok" << std::endl;
  }

  std::cout << "Checking ParticleInfo returns +ve mass for mu+... ";
  if(dataBase.getMassMeV(-13) <= 0.0){ 
    std::cout << "fail" << std::endl;
    return 1;
  }

  else{
    std::cout << "ok" << std::endl;
  }

  return 0;
}

int pp6day4_algorithm_demo() {
  size_t s;
  while((s < 10) || (s > 100)){
    std::cout << "Enter size of array to generate/sort [10 <= N <= 100]: ";
    s = getNumber();
  }

  std::vector<double> v(s,0);

  std::generate(v.begin(), v.end(), getRandom);

  std::cout << "Generated vector:" << std::endl;
  std::copy(v.begin(), v.end(), std::ostream_iterator<double>(std::cout, "\n"));
  
  std::vector<double>::iterator maxElem = std::max_element(v.begin(), v.end());
  std::vector<double>::iterator minElem = std::min_element(v.begin(), v.end());

  std::cout << "Max Element = " << *maxElem << std::endl;
  std::cout << "Min Element = " << *minElem << std::endl;

  std::sort(v.begin(), v.end());

  std::cout << "Sorted vector:" << std::endl;
  std::copy(v.begin(), v.end(), std::ostream_iterator<double>(std::cout, "\n"));

  return 0;
}

//----------Menu Code----------
//----------=========----------

void pp6day4_menu() {
  double res; 
  char menu4;

  while(true){
    std::cout << "                          " << std::endl;
    std::cout << "PP6Calculator - Day 4 Menu" << std::endl;
    std::cout << "==========================" << std::endl;
    std::cout << "                          " << std::endl;
    std::cout << "Please enter the operation you wish to perform:" << std::endl;
    std::cout << "Enter '1' to read and display the PDG textfile database" << std::endl;
    std::cout << "Enter '2' to instantiate a ParticleInfo instance and test it" << std::endl;
    std::cout << "Enter '3' to demonstrate use of STL algorithms to sort a random array" 
	      << std::endl;
    std::cout << "Enter '4' to analyse input file for muon pairs (Day 4 version)" 
	      << std::endl;
    std::cout << "Enter 'q' to quit" << std::endl;
    std::cout << "                 " << std::endl;
    
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
  
    else if(menu4 == '1'){
      res = pp6day4_io_pdg();
    }
    
    else if(menu4 == '2'){
      res = pp6day4_check_particleinfo();
    }
    
    else if(menu4 == '3'){
      res = pp6day4_algorithm_demo();
    }
    
    else if(menu4 == '4'){
      res = pp6day4_muonanalysis();
    }

    else{
      std::cerr << "[ERROR] Operation '" << menu4 << "' not recognised."
                << std::endl;
      continue;
    }

    if(res){
      std::cerr << "[ERROR] Operation '" << menu4 << "' returned a non-zero code '" 
		<< res << "'. Please check parameters." << std::endl;
      res = 0;
      continue;
    }
  }
}

