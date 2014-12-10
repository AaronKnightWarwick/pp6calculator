//----------PP6Day1Menu.cpp----------
//----------===============----------

#include "PP6Day1Menu.hpp"

//----------Standard Library----------
//----------================----------

#include <iostream>
#include <limits>

//----------This Project----------
//----------============----------

#include "PP6Math.hpp"

//----------Main Code----------
//----------=========----------

void pp6day1_menu() {

  double res, ans1, ans2;
  char menu1;
  
  while(true){
    std::cout << "                          " << std::endl;
    std::cout << "PP6Calculator - Day 1 Menu" << std::endl;
    std::cout << "==========================" << std::endl;
    std::cout << "                          " << std::endl;
    std::cout << "Please enter the operation you wish to perform:" << std::endl;
    std::cout << "Enter '1' for addition" << std::endl;
    std::cout << "Enter '2' for subtraction" << std::endl;
    std::cout << "Enter '3' for multiplication" << std::endl;
    std::cout << "Enter '4' for division" << std::endl;
    std::cout << "Enter '5' for the intercept of a straight" << std::endl;
    std::cout << "Enter '6' for a quadratic solver" << std::endl;
    std::cout << "Enter '7' for the length of 3-Vector" << std::endl;
    std::cout << "Enter '8' for the length of 4-Vector" << std::endl;
    std::cout << "Enter '9' for the invariant mass of two particles" << std::endl;
    std::cout << "Enter 'q' to quit" << std::endl;
    std::cout << "                 " << std::endl;
    
    std::cin >> menu1;
    if(!std::cin){
      std::cerr << "[ERROR] User input error" << std::endl;
      std::cin.clear();
      std::cin.ignore();
      continue;
    }

    if(menu1 == 'q'){
      break;
    }
    else if((menu1 == '1') || (menu1 == '2') || (menu1 == '3') || (menu1 == '4'))
    {
      double a, b;
      std::cout << "Enter a value for 'a': ";
      a = getNumber();
      std::cout << "Enter a value for 'b': ";
      b = getNumber();
       
      if(menu1 == '1'){
        res = add(a, b, ans1);
      }
      else if(menu1 == '2'){
        res = subtract(a, b, ans1);
      }
      else if(menu1 == '3'){
        res = multiply(a, b, ans1);
      }
      else if(menu1 == '4'){
        res = divide(a, b, ans1);
      }
    }
    else if(menu1 == '5'){
      double m, c;

      std::cout << "Enter the gradient: ";
      m = getNumber();
      std::cout << "Enter the y intercept: ";
      c = getNumber();
      res = intercept(m, c, ans1);
    }
    else if(menu1 == '6'){
      double a, b, c;

      std::cout << "Enter the square coefficient: ";
      a = getNumber();
      std::cout << "Enter the linear coefficient: ";
      b = getNumber();
      std::cout << "Enter the constant coefficient: ";
      c = getNumber();
      
      res = quadratic(a, b, c, ans1, ans2);
    }
    else if(menu1 == '7'){
      double x, y, z;

      std::cout << "Enter the x-component: ";
      x = getNumber();
      std::cout << "Enter the y-component: ";
      y = getNumber();
      std::cout << "Enter the z-component: ";
      z = getNumber();

      res = length(x, y, z, ans1);
    }
    else if(menu1 == '8'){
      double x, y, z, t;

      std::cout << "Enter the x-component: ";
      x = getNumber();
      std::cout << "Enter the y-component: ";
      y = getNumber();
      std::cout << "Enter the z-component: ";
      z = getNumber();
      std::cout << "Enter the t-component: ";
      t = getNumber();
      
      res = length(t, x, y, z, ans1);
    }
    else if(menu1 == '9'){
      double E1, px1, py1, pz1, E2, px2, py2, pz2;

      std::cout << "Enter the px value for the first particle: ";
      px1 = getNumber();
      std::cout << "Enter the py value for the first particle: ";
      py1 = getNumber();
      std::cout << "Enter the pz value for the first particle: ";
      pz1 = getNumber();
      std::cout << "Enter the e value for the first particle: ";
      E1 = getNumber();

      std::cout << "Enter the px value for the second particle: ";
      px2 = getNumber();
      std::cout << "Enter the py value for the second particle: ";
      py2 = getNumber();
      std::cout << "Enter the pz value for the second particle: ";
      pz2 = getNumber();
      std::cout << "Enter the e value for the second particle: ";
      E2 = getNumber();

      res = inv_mass(E1, px1, py1, pz1, E2, px2, py2, pz2, ans1);
    }
    else{
      std::cerr << "[ERROR] Operation '" << menu1 << "' not recognised."
                << std::endl;
      continue;
    }

    if(res){
      std::cerr << "[ERROR] Operation '" << menu1 << "' returned a non-zero code '" 
		<< res << "'. Please check parameters." << std::endl;
      continue;
    }

    if(menu1 == '6'){
      std::cout << "[RESULT]: positive_root: " << ans1 << std::endl;
      std::cout << "[RESULT]: negative_root: " << ans2 << std::endl;
    }
    else{
      std::cout << "[RESULT]: " << ans1 << std::endl;
    }
  }
}

