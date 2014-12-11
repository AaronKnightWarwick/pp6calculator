//----------PP6Math.cpp----------
//----------===========----------

#include "PP6Math.hpp"

//----------Standard Library----------
//----------================----------

#include <iostream>
#include <limits>
#include <cmath>
#include <cstdlib>

//----------Arithmetic Operations----------
//----------=====================----------

int add(double a, double b, double& answer){
  answer = a + b;
  return 0;
}

int subtract(double a, double b, double& answer){
  answer = a - b;
  return 0;
}

int multiply(double a, double b, double& answer){
  answer = a * b;
  return 0;
}

int divide(double a, double b, double& answer){
  if(b == 0){
    return 1;
  }
  
  answer = a / b;
  return 0;
}

//----------Arithmetic Operation----------
//----------====================----------

int intercept(double m, double c, double& answer){
  return divide(-c, m, answer);
}

//----------Quadratic Operation----------
//----------===================----------

int quadratic(double a, double b, double c, double& positiveRoot,
              double& negativeRoot){
  if(a == 0){
    return 1;
  }

  double discriminant(pow(b, 2) - 4 * a * c);

  if(discriminant < 0){
    return 2;
  }

  positiveRoot = (-b + sqrt(discriminant)) / (2 * a);
  negativeRoot = (-b - sqrt(discriminant)) / (2 * a);

  return 0;
} 

//----------Statistical Operations----------
//----------======================----------

int getMeanAndStdDev(double *x, int size, double& mean, double& stddev){
  if(!x) return 1;

  mean = 0;
  for(int i; i < size; ++i){
    mean += x[i];
  }

  mean /= size;

  stddev = 0;
  for(int i; i < size; ++i){
    stddev += (x[i] - mean) * (x[i] - mean);
  }

  stddev /= size;
  stddev = sqrt(stddev);

  return 0;
}

//----------Vector Operations----------
//----------=================----------

double length(double x, double y, double z, double& vectorlength){
  vectorlength = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
  return 0;
}

double length(double t, double x, double y, double z, double& vectorlength){
  double spacelength;
  if(length(x, y, z, spacelength)){
    return 1;
  }

  double timesquared(pow(t, 2));
  double spacesquared(pow(spacelength, 2));

  if(timesquared < spacesquared){
    return 2;
  }

  vectorlength = sqrt(timesquared - spacesquared);
  return 0;
}

int sumVectors(double *x, double *y, double *z, int size, 
               double &sumX, double &sumY, double &sumZ){

  if((!x) || (!y) || (!z)){
    return 1;
  }

  sumX = 0;
  sumY = 0;
  sumZ = 0;

  for(int i; i < size; ++i){
    sumX += x[i];
    sumY += y[i];
    sumZ += z[i];
  }

  return 0;
}

//----------Invariant Mass Operation----------
//----------========================----------

double inv_mass(double E1, double px1, double py1, double pz1, 
                double E2, double px2, double py2, double pz2,
                double& invariantMass){
  double tot_E(E1 + E2);
  double tot_px(px1 + px2);
  double tot_py(py1 + py2);
  double tot_pz(pz1 + pz2);

  if(length(tot_E, tot_px, tot_py, tot_pz, invariantMass)){
    return 1;
  }
  return 0; 
}

//----------Algorithm Operations----------
//----------====================----------

int swap(double& a, double& b){
  double temp;
  a = b;
  b = temp;
  return 0;
}

int swap(int& a, int& b){
  int temp;
  a = b;
  b = temp;
  return 0;
}

int basic_sort(double *arr, int size){
  bool done(true);

  while(true){
    done = true;

    for(int i = 0; i < size-1; ++i){
      if(arr[i] < arr[i+1]){
        swap(arr[i], arr[i+1]);
        done = false;
      }
    }

    if(done){
      break;
    }
  }
  return 0;
}

int associative_sort(double *arr, int *index, int size){
  double *arr_t = new double[size];
  for(int i(0); i < size; i++){
    arr_t[i] = arr[i];
  }

  bool done(true);

  while(true){
    done = true;

    for(int i; i < size-1; ++i){
      if(arr_t[i] < arr_t[i+1]){
        swap(index[i], index[i+1]);
        swap(arr_t[i], arr_t[i+1]);
        done = false;
      }
    }
    if(done){
      break;
    }
  }

  delete [] arr_t;
  return 0;
}
  
//----------Other Operations----------
//----------================----------

void printArray(double *arr, int size){
  std::cout << "[array:" << arr << "]{";
  for(int i = 0; i < size - 1; ++i){
    std::cout << arr[i] << ", ";
  }
  std::cout << arr[size - 1] << "}" << std::endl;
}

double getRandom(){
  return (rand() % 10000)/10000.;
}

double getNumber(){
  double res;

  std::cin >> res;

  while(!std::cin){
    std::cout << "Error in input. Please re-enter >> ";
    std::cin.clear();
    std::cin.ignore();

    std::cin >> res;
  }

  return res;
}

std::string getString(){
  std::string res;

  std::cin >> res;

  while(!std::cin){
    std::cout << "Error in input. Please re-enter >> ";
    std::cin.clear();
    std::cin.ignore();

    std::cin >> res;
  }

  return res;
}

