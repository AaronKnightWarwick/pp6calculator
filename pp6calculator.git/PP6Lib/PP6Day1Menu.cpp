//-----------Day 1 Menu----------
//-----------==========----------

#include "PP6Day1Menu.hpp"

//----------Standard Library----------
//----------================----------

#include <iostream>

//----------This Project----------
//----------============----------

#include "PP6Math.hpp"

//----------Main Code----------
//----------=========----------

void pp6day1_menu()
{ 
  double res, ans1, ans2;
  char menu1;
  
  while(true){
    
    std::cout << "                          " << std::endl;
    std::cout << "PP6Calculator - Day 1 Menu" << std::endl;
    std::cout << "==========================" << std::endl;
    std::cout << "                          " << std::endl;
    std::cout << "Enter the operation you wish to perform:" << std::endl;
    std::cout << "Enter 1 for addition" << std::endl;
    std::cout << "Enter 2 for subtraction" << std::endl;
    std::cout << "Enter 3 for multiplication" << std::endl;
    std::cout << "Enter 4 for division" << std::endl;
    std::cout << "Enter 5 for intercept" << std::endl;
    std::cout << "Enter 6 for quadratic" << std::endl;
    std::cout << "Enter 7 for length of 3-vector" << std::endl;
    std::cout << "Enter 8 for length of 4-vector" << std::endl;
    std::cout << "Enter 9 for invariant mass of two particles" << std::endl;
    std::cout << "Enter q quit back to the main menu" << std::endl;
    std::cout << "                                  " << std::endl;
    std::cout << "Enter you choice here:" << std::endl;
    
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
    
    else if((menu1 == '1') || (menu1 == '2') || (menu1 == '3') || (menu1 == '4')){

      double a, b;
      std::cout << "Enter your value for a: " << std::endl;
      a = input();
      std::cout << "Enter your value for b: " << std::endl;
      b = input();
       
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
      
      std::cout << "Currently not working, working on a fix" << std::endl;

      //double x1, x2, y1, y2, m, x_intercept, y_intercept;

      //std::cout << "Enter your value for x1: " << std::endl;
      //x1 = input();
      //std::cout << "Enter your value for x2: " << std::endl;
      //x2 = input();
      //std::cout << "Enter your value for y1 " << std::endl;
      //y1 = input();
      //std::cout << "Enter your value for y2: " << std::endl;
      //y2 = input();
      
      //res = intercept(x1, x2, y1, y2, ans1);
      
      //std::cout << "Your gradient is: " << m << std::endl;
      //std::cout << "Your y-intercept is: " << y_intercept << std::endl;
      //std::cout << "Your x-intercept is: " << x_intercept << std::endl;
    }
    
    else if(menu1 == '6'){
      
      double a, b, c;

      std::cout << "Enter your x*x coefficient: " << std::endl;
      a = input();
      std::cout << "Enter your x coefficient: " << std::endl;
      b = input();
      std::cout << "Enter your constant coefficient: " << std::endl;
      c = input();
      
      res = quadratic(a, b, c, ans1, ans2);
    }

    else if(menu1 == '7'){
      
      double x, y, z;

      std::cout << "Enter the x-component: " << std::endl;
      x = input();
      std::cout << "Enter the y-component: " << std::endl; 
      y = input();
      std::cout << "Enter the z-component: " << std::endl;
      z = input();

      res = length(x, y, z, ans1);
    }

    else if(menu1 == '8'){

      double x, y, z, t;

      std::cout << "Enter the x-component: ";
      x = input();
      std::cout << "Enter the y-component: ";
      y = input();
      std::cout << "Enter the z-component: ";
      z = input();
      std::cout << "Enter the t-component: ";
      t = input();
      res = length(t, x, y, z, ans1);
    }
    
    else if(menu1 == '9'){
      
      double E1, px1, py1, pz1, E2, px2, py2, pz2;
      
      std::cout << "Enter the px value for the first particle: ";
      px1 = input();
      std::cout << "Enter the py value for the first particle: ";
      py1 = input();
      std::cout << "Enter the pz value for the first particle: ";
      pz1 = input();
      std::cout << "Enter the e value for the first particle: ";
      E1 = input();
      std::cout << "Enter the px value for the second particle: ";
      px2 = input();
      std::cout << "Enter the py value for the second particle: ";
      py2 = input();
      std::cout << "Enter the pz value for the second particle: ";
      pz2 = input();
      std::cout << "Enter the e value for the second particle: ";
      E2 = input();

      res = inv_mass(E1, px1, py1, pz1, E2, px2, py2, pz2, ans1);
    }
    
    else{
      std::cerr << "[ERROR] The operation '" << menu1 << "' is not valid"
		<< std::endl;
      continue;
    }

    if(menu1 == '6'){
      std::cout << "Positive root = " << ans1 << std::endl;
      std::cout << "Negative root = " << ans2 << std::endl;
    }
        
    else{
      std::cout << "Answer = " << ans1 << std::endl;
    }
  }
}

    

