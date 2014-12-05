// File - PP6 Four Vector
// Author - Aaron Knight
// Brief - Declaration of PP6FourVector

#ifndef PP6FOURVECTOR_HH
#define PP6FOURVECTOR_HH

//----------Standard Library----------
//----------================----------

#include <string>

class FourVector {
public: 
  FourVector() : t_(0.0), x_(0.0), y_(0.0), z_(0.0), s_(0.0) {}
  FourVector(const FourVector& other) : t_(other.getT()), x_(other.getX()), y_(other.getY()), z_(other.getZ()), s_(other.interval()) {}
  FourVector(const double t, const double x, const double y, const double z)
    : t_(t), x_(x), y_(y), z_(z) {compute_interval();}
  FourVector& operator=(const FourVector& other);

  FourVector& operator+=(const FourVector& rhs);

  FourVector& operator-=(const FourVector& rhs);

  double interval() const;
  int boost_z(const double velocity);
  std::string asString() const;
  double getT() const {return t_;}
  double getX() const {return x_;}
  double getY() const {return y_;}
  double getZ() const {return z_;}
  void setT(const double t) {t_ = t; compute_interval();}
  void setX(const double x) {x_ = x; compute_interval();}
  void setY(const double y) {y_ = y; compute_interval();}
  void setZ(const double z) {z_ = z; compute_interval();}
private:
  static const double c;
  static const double c2;
private:
  void compute_interval();
private:
  double t_;
  double x_;
  double y_;
  double z_;
  double s_; 
};
FourVector* createFourVector();
FourVector* createFourVector(const double t, const double x, const double y,
			     const double z);
void destroyFourVector(FourVector *&p);
std::istream& operator>>(std::istream& in, FourVector& vec);
std::ostream& operator<<(std::ostream& out, const FourVector& vec);

FourVector operator+(const FourVector& lhs, const FourVector& rhs);
FourVector operator-(const FourVector& lhs, const FourVector& rhs);

#endif // PP6FOURVECTOR_HH
