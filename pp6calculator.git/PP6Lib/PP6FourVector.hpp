// File - PP6FourVector.hpp
// Author - Aaron Knight
// Brief - Declaration of PP6FourVector

#ifndef PP6FOURVECTOR_HH
#define PP6FOURVECTOR_HH

//----------Standard Library----------
//----------================----------

#include <string>

//----------This project----------
//----------============----------

#include "PP6ThreeVector.hpp"

class FourVector {
 public:
  enum CausalType {
    TIMELIKE = 0,
    SPACELIKE,
    LIGHTLIKE
  };

public:
  FourVector();

  FourVector(const FourVector& other);

  FourVector(const double t, const double x, const double y, const double z);
  FourVector(const double t, const ThreeVector& v);



  FourVector& operator=(const FourVector& other);

  FourVector& operator+=(const FourVector& rhs);

  FourVector& operator-=(const FourVector& rhs);

  FourVector& operator*=(const double rhs);

  FourVector& operator/=(const double rhs);

  double interval() const;

  int boost_z(const double velocity);

  CausalType getCausalType() const;

  std::string asString() const;

  double getT() const {return t_;}
  const ThreeVector& getThreeVector() const {return x_;}
  double getX() const {return x_.getX();}
  double getY() const {return x_.getY();}
  double getZ() const {return x_.getZ();}

  void setT(const double t); 
  void setThreeVector(const ThreeVector& v);
  void setX(const double x);
  void setY(const double y);
  void setZ(const double z);

 private:
  static const double c;
  static const double c2;
 private:
  void compute_interval();
 private:
  double t_;
  ThreeVector x_;
  double s_; 
};

FourVector* createFourVector();

FourVector* createFourVector(const double t, const double x, const double y,
                             const double z);

void destroyFourVector(FourVector *&p);

std::string asString(const FourVector::CausalType k);

std::istream& operator>>(std::istream& in, FourVector& vec);
std::ostream& operator<<(std::ostream& out, const FourVector& vec);

FourVector operator+(const FourVector& lhs, const FourVector& rhs);
FourVector operator-(const FourVector& lhs, const FourVector& rhs);
FourVector operator*(const FourVector& lhs, const double rhs);
FourVector operator*(const double lhs, const FourVector& rhs);
FourVector operator/(const FourVector& lhs, const double rhs);

double contraction(const FourVector& lhs, const FourVector& rhs);

#endif // PP6FOURVECTOR_HH

