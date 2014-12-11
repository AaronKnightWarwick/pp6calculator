//----------PP6Day2MuonAnalysis.cpp----------
//----------=======================----------

#include "PP6Day2MuonAnalysis.hpp"

//----------Standard Library----------
//----------================----------

#include <iostream>
#include <cmath>

//----------Third Party----------
//----------===========----------

#include "FileReader.hpp"

//----------This Project----------
//----------============----------

#include "PP6Math.hpp"

//----------Main Code----------
//----------=========----------

int countMuons(const std::string& inputFile, const std::string& runName,
               int& numberOfMuons, int& numberOfAntiMuons) {
  FileReader counter(inputFile);
  if(!counter.isValid()){
    std::cerr << "[countMuonPairs:error] " << inputFile << " is not valid"
              << std::endl;
    return 1;
  }

  numberOfMuons = 0;
  numberOfAntiMuons = 0;

  std::string particleName, dataID;

  while(counter.nextLine()){
    counter.getFieldAsInt(1);
    if(counter.inputFailed()) continue;

    particleName = counter.getFieldAsString(2);
    if(counter.inputFailed()){
      std::cerr << "[countMuonPairs:error] Field 2 of " << inputFile << " is not a string"
                << std::endl;
      return 1;
    }

    dataID = counter.getFieldAsString(6);
    if(counter.inputFailed()){
      std::cerr << "[countMuonPairs:error] Field 6 of " << inputFile << " is not a string"
                << std::endl;
      return 1;
    }

    if(dataID == runName){
      if(particleName == "mu-") numberOfMuons++;
      if(particleName == "mu+") numberOfAntiMuons++;
    }
  }
  return 0;
}

int pp6day2_muonanalysis() {
  std::string muonFile;
  int res;

  std::cout << "Enter filename to analyse: ";
  muonFile = getString();

  std::string runID("run4.dat");
  int numberOfMuons, numberOfAntiMuons;

  res = countMuons(muonFile, runID, numberOfMuons, numberOfAntiMuons);
  if(res){
    std::cerr << "[pp6day2_muonanalysis:error] Failed to count muons in " << muonFile
              << std::endl;
    return res;
  }

  int *muonEventNumber(new int[numberOfMuons]);
  double *muonEnergy(new double[numberOfMuons]);
  double *muonPx(new double[numberOfMuons]);
  double *muonPy(new double[numberOfMuons]);
  double *muonPz(new double[numberOfMuons]);

  int *antimuonEventNumber(new int[numberOfAntiMuons]);
  double *antimuonEnergy(new double[numberOfAntiMuons]);
  double *antimuonPx(new double[numberOfAntiMuons]);
  double *antimuonPy(new double[numberOfAntiMuons]);
  double *antimuonPz(new double[numberOfAntiMuons]);

  int eventNumber;
  std::string particleName, dataID;
  double particlePx, particlePy, particlePz;
  double particlePtot;
  const double muonMass(0.105658366);

  FileReader muonReader(muonFile);
  int muonCounter;
  int antimuonCounter;
  
  while(muonReader.nextLine()){
    eventNumber = muonReader.getFieldAsInt(1);
    if(muonReader.inputFailed()) continue;

    particleName = muonReader.getFieldAsString(2);
    if(muonReader.inputFailed()){
      std::cerr << "[pp6day2_muonanalysis:error] Field 2 of " << muonFile
                << " is not a string" << std::endl;
      break;
    }

    dataID = muonReader.getFieldAsString(6);
    if(muonReader.inputFailed()){
      std::cerr << "[pp6day2_muonanalysis:error] Field 6 of " << muonFile
                << " is not a string" << std::endl;
      break;
    }

    if(dataID == runID){
      particlePx = muonReader.getFieldAsDouble(3);
      if(muonReader.inputFailed()){
      std::cerr << "[pp6day2_muonanalysis:error] Field 3 of " << muonFile
                << " is not a double" << std::endl;
      break;
      }

      particlePy = muonReader.getFieldAsDouble(4);
      if(muonReader.inputFailed()){
      std::cerr << "[pp6day2_muonanalysis:error] Field 4 of " << muonFile 
		<< " is not a double" << std::endl;
      break;
      }

      particlePz = muonReader.getFieldAsDouble(5);
      if(muonReader.inputFailed()){
      std::cerr << "[pp6day2_muonanalysis:error] Field 5 of " << muonFile
                << " is not a double" << std::endl;
      break;
      }

      if(particleName == "mu-"){
        muonEventNumber[muonCounter] = eventNumber; 
        muonPx[muonCounter] = particlePx;
        muonPy[muonCounter] = particlePy;
        muonPz[muonCounter] = particlePz;
        length(particlePx, particlePy, particlePz, particlePtot);
        muonEnergy[muonCounter] = sqrt(particlePtot * particlePtot + 
                                       muonMass*muonMass); 
        ++muonCounter;
      }

      if(particleName == "mu+"){
        antimuonEventNumber[antimuonCounter] = eventNumber; 
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
    std::cerr << "[pp6day2_muonanalysis:error] Failed to extract physics data from "
              << muonFile << std::endl;

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

  double *invariantMass(new double[numberOfMuons * numberOfAntiMuons]);
  int *muonPairIndex(new int[numberOfMuons * numberOfAntiMuons]);
  
  for(int i; i < numberOfAntiMuons; ++i){
    for(int j; j < numberOfMuons; ++j){
      inv_mass(muonEnergy[j], muonPx[j], muonPy[j], muonPz[j], antimuonEnergy[i],
	       antimuonPx[i], antimuonPy[i], antimuonPz[i],
	       invariantMass[i*numberOfMuons + j]);
      muonPairIndex[i*numberOfMuons + j] = i*numberOfMuons + j;
    }
  }

  associative_sort(invariantMass, muonPairIndex, 
                   numberOfMuons * numberOfAntiMuons);
  
  std::cout << "Results:" << std::endl;
  std::cout << "========" << std::endl;
  std::cout << "Analysed File : " << muonFile << std::endl;
  std::cout << "Number of Muons     = " << numberOfMuons << std::endl;
  std::cout << "Number of AntiMuons = " << numberOfAntiMuons << std::endl;
  std::cout << "----------------------------" << std::endl;

  for(int i; i < 10; ++i){
    int muonIndex(muonPairIndex[i] % numberOfMuons);
    int antimuonIndex((muonPairIndex[i] - muonIndex) / numberOfMuons);

    std::cout << "{InvariantMass : " << invariantMass[muonPairIndex[i]] << ",\n\t"
              << "{Muon : " << "Event = " << muonEventNumber[muonIndex] << ", "
              << "(E, P) = (" << muonEnergy[muonIndex] << ", "
              << muonPx[muonIndex] << ", " << muonPy[muonIndex] << ", "
              << muonPz[muonIndex] << ")}\n\t" << "{AntiMuon : "
              << "Event = " << antimuonEventNumber[antimuonIndex] << ", "
              << "(E, P) = (" << antimuonEnergy[antimuonIndex] << ", "
              << antimuonPx[antimuonIndex] << ", " << antimuonPy[antimuonIndex] << ", "
              << antimuonPz[antimuonIndex] << ")}\n" << "}" << std::endl;
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

