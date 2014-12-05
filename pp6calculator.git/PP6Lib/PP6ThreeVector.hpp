// File - ThreeVector.hpp
// Author - Aaron Knight
// Brief - Declaration of ThreeVector

#ifndef PP6THREEVECTOR_HH
#define PP6THREEVECTOR_HH


#include <iosfwd> 
#include <string>


class ThreeVector {
 public:
  ThreeVector();

  ThreeVector(const ThreeVector& other);

  ThreeVector(const double x, const double y, const double z);

  ThreeVector& operator=(const ThreeVector& other);
  
  ThreeVector& operator+=(const ThreeVector& rhs);

  ThreeVector& operator-=(const ThreeVector& rhs);
  
  ThreeVector& operator*=(const double rhs);

  ThreeVector& operator/=(const double rhs);

  double length() const;

  std::string asString() const;

  double getX() const {return x_;}
  double getY() const {return y_;}
  double getZ() const {return z_;}

  void setX(const double x);
  void setY(const double y);
  void setZ(const double z);

  double getR() const;
  double getTheta() const;
  double getPhi() const;

  void setR(const double r);
  void setTheta(const double theta);
  void setPhi(const double phi);

 private:
  void compute_length();
 private:
  
  double x_;
  double y_;
  double z_;
  double l_; 
};

std::istream& operator>>(std::istream& in, ThreeVector& vec);
std::ostream& operator<<(std::ostream& out, const ThreeVector& vec);

ThreeVector operator+(const ThreeVector& lhs, const ThreeVector& rhs);
ThreeVector operator-(const ThreeVector& lhs, const ThreeVector& rhs);
ThreeVector operator*(const ThreeVector& lhs, const double rhs);
ThreeVector operator*(const double lhs, const ThreeVector& rhs);
ThreeVector operator/(const ThreeVector& lhs, const double rhs);
ThreeVector operator-(const ThreeVector& vec);

double scalarProduct(const ThreeVector& a, const ThreeVector& b);


#endif // PP6FOURVECTOR_HH

