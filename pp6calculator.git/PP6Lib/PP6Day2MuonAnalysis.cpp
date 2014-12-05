//----------PP6 Day 2 Muon Analysis----------
//----------=======================----------

#include "PP6Day2MuonAnalysis.hpp"

//----------Standard Library----------
//----------================----------

#include <iostream>
#include <cmath>

//----------File Reader----------
//----------===========----------

#include "FileReader.hpp"

//----------This Project----------
//----------============----------

#include "PP6Math.hpp"

int countmuons(const std::string& input, const std::string& runname,
               int& numofmuons, int& numofantimuons){
  
  FileReader counter(input);
  if(!counter.isValid()){
    std::cerr << "[ERROR] " << input << " is not valid" << std::endl;
    return 1;
  }

  numofmuons = 0;
  numofantimuons = 0;

  int eventnumber;
  std::string particlename, dataID;

  while(counter.nextLine()){
   
    eventnumber = counter.getFieldAsInt(1);
    if(counter.inputFailed()) continue;

    particlename = counter.getFieldAsString(2);
    if(counter.inputFailed()){
      std::cerr << "[ERROR] Field 2 of " << input << " is not a string"
                << std::endl;
      return 1;
    }

    dataID = counter.getFieldAsString(6);
    if(counter.inputFailed()){
      std::cerr << "[ERROR] Field 6 of " << input << " is not a string"
                << std::endl;
      return 1;
    }

    if(dataID == runname){
      if(particlename == "mu-") numofmuons++;
      if(particlename == "mu+") numofantimuons++;
    }
  }
  return 0;
}

int pp6day2_muonanalysis(){
  std::string muonfile;
  int res;

  std::cout << "Enter filename to analyse: ";
  muonfile = getString();

  std::string runID("run4.dat");
  int numofmuons, numofantimuons;

  res = countmuons(muonfile, runID, numofmuons, numofantimuons);
  if(res){
    std::cerr << "[ERROR] Failed to count muons in "<< muonfile
              << std::endl;
    return res;
  }

  int *muonEventNumber(new int[numofmuons]);
  double *muonEnergy(new double[numofmuons]);
  double *muonPx(new double[numofmuons]);
  double *muonPy(new double[numofmuons]);
  double *muonPz(new double[numofmuons]);
  
  int *antimuonEventNumber(new int[numofantimuons]);
  double *antimuonEnergy(new double[numofantimuons]);
  double *antimuonPx(new double[numofantimuons]);
  double *antimuonPy(new double[numofantimuons]);
  double *antimuonPz(new double[numofantimuons]);

  int eventnumber;
  std::string particlename, dataID;
  double particlePx, particlePy, particlePz;
  double particlePtot;
  double muonMass;

  FileReader muonReader(muonfile);
  int muonCounter;
  int antimuonCounter;
  
  while(muonReader.nextLine()){
    eventnumber = muonReader.getFieldAsInt(1);
    if(muonReader.inputFailed()) continue;

    particlename = muonReader.getFieldAsString(2);
    if (muonReader.inputFailed()) {
      std::cerr << "[ERROR] Field 2 of " << muonfile << " is not a string"
                << std::endl;
      break;
    }
    
    dataID = muonReader.getFieldAsString(6);
    if(muonReader.inputFailed()){
      std::cerr << "[ERROR] Field 6 of " << muonfile << " is not a string"
                << std::endl;
      break;
    }

    if(dataID == runID){
      particlePx = muonReader.getFieldAsDouble(3);
      if(muonReader.inputFailed()){
	std::cerr << "[ERROR] Field 3 of " << muonfile << " is not a double"
		  << std::endl;
	break;
      }
      
      particlePy = muonReader.getFieldAsDouble(4);
      if(muonReader.inputFailed()){
	std::cerr << "[ERROR] Field 4 of " << muonfile << " is not a double"
		  << std::endl;
	break;
      }
      
      particlePz = muonReader.getFieldAsDouble(5);
      if(muonReader.inputFailed()){
	std::cerr << "[ERROR] Field 5 of " << muonfile << " is not a double"
		  << std::endl;
	break;
      }
      
      if(particlename == "mu-"){
        
        muonEventNumber[muonCounter] = eventnumber; 
        muonPx[muonCounter] = particlePx;
        muonPy[muonCounter] = particlePy;
        muonPz[muonCounter] = particlePz;
        length(particlePx, particlePy, particlePz, particlePtot);
        muonEnergy[muonCounter] = sqrt(particlePtot * particlePtot + 
                                       muonMass*muonMass); 
        ++muonCounter;
      }
      if(particlename == "mu+"){
	antimuonEventNumber[antimuonCounter] = eventnumber; 
        antimuonPx[antimuonCounter] = particlePx;
        antimuonPy[antimuonCounter] = particlePy;
        antimuonPz[antimuonCounter] = particlePz;
        length(particlePx, particlePy, particlePz, particlePtot);
        antimuonEnergy[antimuonCounter] = sqrt(particlePtot * particlePtot + 
					       muonMass*muonMass); 
        ++antimuonCounter;
      }
    }
  }
  
  if(muonReader.inputFailed()){
    std::cerr << "[ERROR] Failed to extract physics data from " << muonfile 
              << std::endl;
    delete [] muonEventNumber;
    delete [] muonEnergy;
    delete [] muonPx;
    delete [] muonPy;
    delete [] muonPz;

    delete [] antimuonEventNumber;
    delete [] antimuonEnergy;
    delete [] antimuonPx;
    delete [] antimuonPy;
    delete [] antimuonPz;
    return 1;
  }

  double *invariantMass(new double[numofmuons * numofantimuons]);
  int *muonPairIndex(new int[numofmuons * numofantimuons]);
  
  for(int i; i < numofantimuons; ++i){
    for(int j; j < numofmuons; ++j){
      inv_mass(muonEnergy[i], muonPx[i], muonPy[i], muonPz[i],
               antimuonEnergy[j], antimuonPx[j], antimuonPy[j], 
               antimuonPz[j],
               invariantMass[i*numofmuons + j]);
      muonPairIndex[i*numofmuons + j] = i*numofmuons + j;
    }
  }
  
  associative_sort(invariantMass, muonPairIndex, 
                   numofmuons * numofantimuons);
  
  std::cout << "Results:" << std::endl;
  std::cout << "========" << std::endl;
  std::cout << "Analysed File : " << muonfile << std::endl;
  std::cout << "Number of Muons     = " << numofmuons << std::endl;
  std::cout << "Number of AntiMuons = " << numofantimuons << std::endl;
  std::cout << "----------------------------" << std::endl;
  
  for(int i; i < 10; ++i){
    int muonIndex(muonPairIndex[i] % numofmuons);
    int antimuonIndex((muonPairIndex[i] - muonIndex) / numofmuons);
    
    std::cout << "{InvariantMass : " << invariantMass[muonPairIndex[i]]
              << ",\n\t"
              << "{Muon : "
              << "Event = " << muonEventNumber[muonIndex] << ", "
              << "(E, P) = ("
              << muonEnergy[muonIndex] << ", "
              << muonPx[muonIndex] << ", "
              << muonPy[muonIndex] << ", "
              << muonPz[muonIndex] << ")}\n\t"
              << "{AntiMuon : "
              << "Event = " << antimuonEventNumber[antimuonIndex] << ", "
              << "(E, P) = ("
              << antimuonEnergy[antimuonIndex] << ", "
              << antimuonPx[antimuonIndex] << ", "
              << antimuonPy[antimuonIndex] << ", "
              << antimuonPz[antimuonIndex] << ")}\n"
              << "}"
              << std::endl;
  }


  delete [] muonEventNumber;
  delete [] muonEnergy;
  delete [] muonPx;
  delete [] muonPy;
  delete [] muonPz;
  
  delete [] antimuonEventNumber;
  delete [] antimuonEnergy;
  delete [] antimuonPx;
  delete [] antimuonPy;
  delete [] antimuonPz;
  
  delete [] invariantMass;
  delete [] muonPairIndex;
  
  return 0;
}
