//----------PP6Math----------
//----------=======----------

#include "PP6Math.hpp"

//----------Standard Library----------
//----------================----------

#include <iostream>
#include <limits>
#include <cmath>
#include <cstdlib>

//----------Functions----------
//----------=========----------

//----------Arithmetic----------
//----------==========----------

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

//----------Intercept----------
//----------=========----------
//NOT WORKING
//double intercept(double x1, double x2, double y1, double y2, double m){
//  std::cout << "Enter a value for x1: " << std::endl;
//  std::cin >> x1;
//  std::cout << "Enter a value for x2: " << std::endl;
//  std::cin >> x2;
//  std::cout << "Enter a value for y1: " << std::endl;
//  std::cin >> y1;
//  std::cout << "Enter a value for y2: " << std::endl;
//  std::cin >> y2;
//  m = (y2-y1)/(x2-x1);
//  double y_intercept = y1 - m*x1;
//  double x_intercept = -y_intercept/m;
//  std::cout << "The gradient of the line is " << m << std::endl;
//  std::cout << "The y-intercept of the line is " << y_intercept << std::endl;
//  std::cout << "The x-intercept of the line is " << x_intercept << std::endl;
//}

//----------Quadratic----------
//----------=========----------

int quadratic(double a, double b, double c, double& positive_root,
	      double& negative_root){
  if(a == 0){
    return 1;
  }

  double discriminant(pow(b, 2) - 4 * a * c);

  if(discriminant < 0){
    return 2;
  }

  positive_root = (-b + sqrt(discriminant)) / (2 * a);
  negative_root = (-b - sqrt(discriminant)) / (2 * a);
  
  return 0;
} 

//----------Statistics----------
//----------==========----------

int getMeanAndStdDev(double *x, int size, double& mean, double& stddev){
  if(!x) return 1;

  mean = 0;
  for(int i(0); i < size; ++i){
    mean += x[i];
  }
   
  mean /= size;
   
  stddev = 0;
  for(int i(0); i < size; ++i){
    stddev += (x[i] - mean) * (x[i] - mean);
  }
   
  stddev /= size;
  stddev = sqrt(stddev);
  
  return 0;
}

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

  for(int i(0); i < size; ++i){
    sumX += x[i];
    sumY += y[i];
    sumZ += z[i];
  }
  
  return 0;
}

//----------Invariant Mass----------
//----------==============----------

double inv_mass(double E1, double px1, double py1, double pz1, 
		     double E2, double px2, double py2, double pz2,
		     double& invariantmass){
  double tot_E(E1 + E2);
  double tot_px(px1 + px2);
  double tot_py(py1 + py2);
  double tot_pz(pz1 + pz2);
  
  if(length(tot_E, tot_px, tot_py, tot_pz, invariantmass)){
    return 1;
  }
  return 0; 
}

//----------Swap----------
//----------====----------

int swap(double& a, double& b){
  double tempnumber(a);
  a = b;
  b = tempnumber;
  return 0;
}

int swap(int& a, int& b){
  int tempnumber(a);
  a = b;
  b = tempnumber;
  return 0;
}


//----------Bubble Sort----------
//----------===========----------

int bubblesort(double *arr, int size){
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
    
    for(int i(0); i < size-1; ++i){
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

void printArray(double *arr, int size){
  std::cout << "[array:" << arr << "]{";
  for(int i = 0; i < size - 1; ++i){
    std::cout << arr[i] << ", ";
  }
  std::cout << arr[size - 1] << "}" << std::endl;
}

double getrandom(){
  return (rand() % 10000)/10000.;
}

double input(){
    double res;
    
    std::cin >> res;
  
    while(!std::cin){
      std::cout << "User input error " << std::endl;
      
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
    std::cout << "User input error " << std::endl;
    
    std::cin.clear();
    std::cin.ignore();
    
    std::cin >> res;
  }
  
  return res;
}

