//----------PP6Day5Menu.cpp----------
//----------===============----------

#include "PP6Day5Menu.hpp"

//----------Standard Library----------
//----------================----------

#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>

//----------Third Party----------
//----------===========----------

#include <boost/shared_ptr.hpp>

//----------This Project----------
//----------============----------

#include "PP6Math.hpp"
#include "PP6ParticleInfo.hpp"
#include "PP6EnergyCut.hpp"
#include "PP6MassCut.hpp"
#include "PP6MomentumCut.hpp"
#include "FileReader.hpp"

bool initialize_database(){
  static bool dbIsUninitialized(true);
  if(dbIsUninitialized){
    std::string dbtFilename;
    std::cout << "Enter path to .dbt file for initializing ParticleInfo: ";
    dbtFilename = getString();

    const ParticleInfo& dataBase = ParticleInfo::Instance(dbtFilename);

    std::cout << "Checking ParticleInfo contains entries... ";
    if(!dataBase.size()){
      std::cout << "fail" << std::endl;
      return false;
    } 

    else{
      std::cout << "ok" << std::endl;
      dbIsUninitialized = false;
    }
  }

  return !dbIsUninitialized;
}

std::vector<Particle> pp6day5_read_particles_from_file( const std::string& fileName ){
  Particle particle;
  std::vector<Particle> particles;

  std::ifstream reader(fileName.c_str());
  if(!reader){
    std::cerr << "[pp6day5_read_particles_from_file:error] "
              << fileName
              << " is not a valid file"
              << std::endl;
    return particles;
  }

  while(true){
    reader >> particle;
    if(!reader.good()){
      break;
    }
    particles.push_back( particle );
  }

  return particles;
}

int pp6day5_test_masscut(){
  if(!initialize_database()){
    return 1;
  }

  std::string particleListFile;
  std::cout << "Enter path to .dat file for loading particles: ";
  particleListFile = getString();

  std::vector<Particle> allParticles = pp6day5_read_particles_from_file( particleListFile );
  if( allParticles.empty() ){
    return 1;
  }

  MassCut cut( Cut::GreaterThan, 0.4 );

  std::vector<Particle> selectedParticles = cut.select( allParticles );

  std::vector<Particle>::const_iterator iter = selectedParticles.begin();
  std::vector<Particle>::const_iterator end = selectedParticles.end();
  for( ; iter != end; ++iter ){
    std::cout << (*iter) << std::endl;
  }

  return 0;
}

int pp6day5_test_energycut(){
  if(!initialize_database()){
    return 1;
  }

  std::string particleListFile;
  std::cout << "Enter path to .dat file for loading particles: ";
  particleListFile = getString();

  std::vector<Particle> allParticles = pp6day5_read_particles_from_file( particleListFile );
  if( allParticles.empty() ){
    return 1;
  }

  EnergyCut cut( 2.0, 2.5 );

  std::vector<Particle> selectedParticles = cut.select( allParticles );

  std::vector<Particle>::const_iterator iter = selectedParticles.begin();
  std::vector<Particle>::const_iterator end = selectedParticles.end();
  for( ; iter != end; ++iter ){
    std::cout << (*iter) << std::endl;
  }

  return 0;
}

int pp6day5_test_dynamiccuts(){
  if(!initialize_database()){
    return 1;
  }

  std::string particleListFile;
  std::cout << "Enter path to .dat file for loading particles: ";
  particleListFile = getString();

  std::vector<Particle> allParticles = pp6day5_read_particles_from_file( particleListFile );
  if( allParticles.empty() ){
    return 1;
  }

  std::string cutsFile;
  std::cout << "Enter path to .dat file for loading cuts: ";
  cutsFile = getString();

  FileReader reader(cutsFile);
  if(!reader.isValid()){
    std::cerr << "[pp6day5_test_dynamiccuts:error] "
              << cutsFile
              << " is not a valid file"
              << std::endl;
    return 1;
  }

  typedef boost::shared_ptr<Cut> CutPtr;
  typedef std::vector<CutPtr> CutCollection;
  CutCollection cuts;
  std::string cutvar;
  Cut::CutType cuttype;
  double lowervalue;
  double uppervalue;

  while(reader.nextLine()){
    cutvar = reader.getField<std::string>(1);
    if(reader.inputFailed()) continue;

    cuttype = reader.getField<Cut::CutType>(2);
    if(reader.inputFailed()) continue;

    lowervalue = reader.getField<double>(3);
    if(reader.inputFailed()) continue;

    if( cuttype == Cut::Range ) {
      uppervalue = reader.getField<double>(4);
      if(reader.inputFailed()) continue;

      if( cutvar == "mass" ) {
	CutPtr ptr(new MassCut( lowervalue, uppervalue ));
	cuts.push_back( ptr );
      } 

      else if( cutvar == "energy" ){
	CutPtr ptr(new EnergyCut( lowervalue, uppervalue ));
	cuts.push_back( ptr );
      } 

      else if( cutvar == "momentum" ){
	CutPtr ptr(new MomentumCut( lowervalue, uppervalue ));
	cuts.push_back( ptr );
      }
    }

    else{
      if( cutvar == "mass" ){
	CutPtr ptr(new MassCut( cuttype, lowervalue ));
	cuts.push_back( ptr );
      } 
      else if( cutvar == "energy" ){
	CutPtr ptr(new EnergyCut( cuttype, lowervalue ));
	cuts.push_back( ptr );
      } 
      else if( cutvar == "momentum" ){
	CutPtr ptr(new MomentumCut( cuttype, lowervalue ));
	cuts.push_back( ptr );
      }
    }
  }

  CutCollection::const_iterator cut_iter = cuts.begin();
  CutCollection::const_iterator cut_end = cuts.end();
  std::vector<Particle> selectedParticles = allParticles;
  for( ; cut_iter != cut_end; ++cut_iter ){
    selectedParticles = (*cut_iter)->select( selectedParticles );
    if( selectedParticles.empty() ){
      break;
    }
  }

  std::vector<Particle>::const_iterator particle_iter = selectedParticles.begin();
  std::vector<Particle>::const_iterator particle_end = selectedParticles.end();
  for( ; particle_iter != particle_end; ++particle_iter ){
    std::cout << (*particle_iter) << std::endl;
  }

  return 0;
}

//----------Main Code----------
//----------=========----------

void pp6day5_menu(){
  double res; 
  char menu5;

  while(true){
    std::cout << "                          " << std::endl;
    std::cout << "PP6Calculator - Day 5 Menu" << std::endl;
    std::cout << "==========================" << std::endl;
    std::cout << "                          " << std::endl;
    std::cout << "Enter the operation you would like to perform:" << std::endl;
    std::cout << "Enter '1' to test MassCut with kaons and pions" << std::endl;
    std::cout << "Enter '2' to test EnergyCut with kaons and pions" << std::endl;
    std::cout << "Enter '3' to test dynamic dispatch to collection of cuts" << std::endl;
    std::cout << "Enter 'q' to quit" << std::endl;
    std::cout << "                 " << std::endl;
    
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

    else if(menu5 == '1'){
      res = pp6day5_test_masscut();
    }

    else if(menu5 == '2'){
      res = pp6day5_test_energycut();
    }
    
    else if(menu5 == '3'){
      res = pp6day5_test_dynamiccuts();
    }

    else{
      std::cerr << "[ERROR] Operation '" << menu5 << "' not recognised."
                << std::endl;
      continue;
    }

    if(res){
      std::cerr << "[ERROR] Operation '" << menu5 << "' returned a non-zero code '" 
		<< res << "'. Please check parameters." << std::endl;
      res = 0;
      continue;
    }
  }
}

