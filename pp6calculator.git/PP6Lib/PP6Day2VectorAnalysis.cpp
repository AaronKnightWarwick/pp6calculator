//----------PP6 Day 2 Vector Analysis----------
//----------=========================----------

#include "PP6Day2VectorAnalysis.hpp"

//----------Standard Library----------
//----------================----------

#include <iostream>
#include <cmath>

//----------This Project----------
//----------============----------

#include "PP6Math.hpp"

//----------Main Code----------
//----------=========----------

int pp6day2_vectoranalysis() {
  int numberOfVectors(0);
  std::cout << "Enter number of vectors to generate: ";
  numberOfVectors = getNumber();
  if((numberOfVectors > 0) && (numberOfVectors < 1001)){
    double *energy = new double[numberOfVectors];
    double *momnX = new double[numberOfVectors];
    double *momnY = new double[numberOfVectors];
    double *momnZ = new double[numberOfVectors];
    int *indices = new int[numberOfVectors];
    double mass(0);
    double momnMagnitude(0), totalMomnX(0), totalMomnY(0), totalMomnZ(0);
    double meanEnergy(0), stddevEnergy(0);

    for(int i(0); i < numberOfVectors; ++i){
      indices[i] = i;

      momnX[i] = 100.0 * getRandom();
      momnY[i] = 100.0 * getRandom();
      momnZ[i] = 100.0 * getRandom();

      mass = 100.0 * getRandom();

      length(momnX[i], momnY[i], momnY[i], momnMagnitude);
      energy[i] = sqrt(mass * mass + momnMagnitude);
    }

    if(sumVectors(momnX, momnY, momnZ, numberOfVectors,
                   totalMomnX, totalMomnY, totalMomnZ)){
      std::cerr << "[ERROR]: Failed to calculate total 3-momentum" << std::endl;
      
      delete [] energy;
      delete [] momnX;
      delete [] momnY;
      delete [] momnZ;
      delete [] indices;
      return 1;
    }

    if(length(totalMomnX, totalMomnY, totalMomnZ, momnMagnitude)){
      std::cerr << "[ERROR]: Failed to calculate 3-momentum magnitude" << std::endl;
      
      delete [] energy;
      delete [] momnX;
      delete [] momnY;
      delete [] momnZ;
      delete [] indices;
      return 1;
    }

    std::cout << "[Total 3-Momentum] : P("
        << totalMomnX << ", "
        << totalMomnY << ", "
        << totalMomnZ << "), "
        << "|P| = "
        << momnMagnitude 
        << std::endl;

    if(getMeanAndStdDev(energy, numberOfVectors, meanEnergy, stddevEnergy)){
      std::cerr << "[ERROR]: Failed to calculate energy statistics" << std::endl;
      
      delete [] energy;
      delete [] momnX;
      delete [] momnY;
      delete [] momnZ;
      delete [] indices;
      return 1;
    }

    std::cout << "[Mean Energy] : E = "
	      << meanEnergy 
	      << " +/- "
	      << stddevEnergy
	      << std::endl;

    if(associative_sort(energy, indices, numberOfVectors)){
      std::cerr << "[ERROR]: Failed to sort energy array" << std::endl;
      
      delete [] energy;
      delete [] momnX;
      delete [] momnY;
      delete [] momnZ;
      delete [] indices;
      return 1;
    }

    std::cout << "[Maximum Energy] : E = "
	      << energy[indices[0]] 
	      << ", found at index "
	      << indices[0]
	      << " of " 
	      << numberOfVectors
	      << std::endl;
    
    delete [] energy;
    delete [] momnX;
    delete [] momnY;
    delete [] momnZ;
    delete [] indices;
  }
  else{
    std::cerr << "[ERROR]: Number must be between 1 and 1000" << std::endl;
    return 1;
  }

  return 0;
}

