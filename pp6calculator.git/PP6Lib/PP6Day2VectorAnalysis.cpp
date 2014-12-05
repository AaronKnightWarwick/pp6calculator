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

int pp6day2_vectoranalysis()
{
  int numvectors;
  std::cout << "Enter number of vectors to generate: ";
  numvectors = input();
  if((numvectors > 0) && (numvectors < 1001)){
    
    double *E = new double[numvectors];
    double *pX = new double[numvectors];
    double *pY = new double[numvectors];
    double *pZ = new double[numvectors];
    int *indices = new int[numvectors];
    double mass;
    double pmag, totpx, totpy, totpz;
    double meanE, stddevE;

    for(int i(0); i < numvectors; ++i){
      indices[i] = i;
      
      pX[i] = 100.0 * getRandom();
      pY[i] = 100.0 * getRandom();
      pZ[i] = 100.0 * getRandom();
      
      mass = 100.0 * getRandom();

      length(pX[i], pY[i], pY[i], pmag);
      E[i] = sqrt(mass * mass + pmag);
    }
    
    if(sumVectors(pX, pY, pZ, numvectors, totpx, totpy, totpz)){
      std::cerr << "[ERROR]: Failed to calculate total 3-momentum" << std::endl;
      delete [] E;
      delete [] pX;
      delete [] pY;
      delete [] pZ;
      delete [] indices;
      return 1;
    }

    if(length(totpx, totpy, totpz, pmag)){
      std::cerr << "[ERROR]: Failed to calculate 3-momentum magnitude" 
		<< std::endl;
      delete [] E;
      delete [] pX;
      delete [] pY;
      delete [] pZ;
      delete [] indices;
      return 1;
    }
    
    std::cout << "[Total 3-Momentum] : P(" << totpx << ", " << totpy << ", "
	      << totpz << "), " << "|P| = " << pmag << std::endl;
    
    if(getMeanAndStdDev(E, numvectors, meanE, stddevE)){
      std::cerr << "[ERROR]: Failed to calculate energy statistics" << std::endl;
      delete [] E;
      delete [] pX;
      delete [] pY;
      delete [] pZ;
      delete [] indices;
      return 1;
    }

    std::cout << "[Mean Energy] : E = " << meanE << " +/- " << stddevE 
	      << std::endl;

    if(associative_sort(E, indices, numvectors)){
      std::cerr << "[ERROR]: Failed to sort energy array" << std::endl;
      delete [] E;
      delete [] pX;
      delete [] pY;
      delete [] pZ;
      delete [] indices;
      return 1;
    }

    std::cout << "[Maximum Energy] : E = " << E[indices[0]]<< ", found at index "
	      << indices[0] << " of " << numvectors << std::endl;

    delete [] E;
    delete [] pX;
    delete [] pY;
    delete [] pZ;
    delete [] indices;
  }
  else{
    std::cerr << "[ERROR]: Number must be between 1 and 1000" << std::endl;
    return 1;
  }
  
  return 0;
}

