//----------PP6FourVector.cpp----------
//----------=================----------

#include <PP6FourVector.hpp>

#include <cmath>
#include <sstream>

//----------Main Code----------
//----------=========----------

const double FourVector::c(1);
const double FourVector::c2(1);

FourVector::FourVector() : t_(0.0), x_(), s_(0.0)
{}

FourVector::FourVector(const FourVector& other)
  : t_(other.getT()), x_(other.getThreeVector()), s_(other.interval())
{}

FourVector::FourVector(const double t, const double x, const double y, const double z) : t_(t), x_(x, y, z)
{
  compute_interval();
}

FourVector::FourVector(const double t, const ThreeVector& x) : t_(t), x_(x){
  compute_interval();
}

FourVector& FourVector::operator=(const FourVector& other){
  if(this != &other){
    t_ = other.getT();
    x_ = other.getThreeVector();
    s_ = other.interval();
  }
  return *this;
}

FourVector& FourVector::operator+=(const FourVector& rhs){
  t_ += rhs.getT();
  x_ += rhs.getThreeVector();
  compute_interval();
  return *this;
}

FourVector& FourVector::operator-=(const FourVector& rhs){
  t_ -= rhs.getT();
  x_ -= rhs.getThreeVector();
  compute_interval();
  return *this;
}

FourVector& FourVector::operator*=(const double rhs){
  t_ *= rhs;
  x_ *= rhs;
  compute_interval();
  return *this;
}

FourVector& FourVector::operator/=(const double rhs){
  t_ /= rhs;
  x_ /= rhs;
  compute_interval();
  return *this;
}

void FourVector::setT(double t){
  t_ = t;
  compute_interval();
}

void FourVector::setThreeVector(const ThreeVector& v){
  x_ = v;
  compute_interval();
}

void FourVector::setX(const double x){
  x_.setX(x);
}

void FourVector::setY(const double y){
  x_.setY(y);
}

void FourVector::setZ(const double z){
  x_.setZ(z);
}

double FourVector::interval() const{
  return s_;
}

int FourVector::boost_z(const double velocity) {
  if(velocity >= c){
    return 1; 
  }

  double gamma = 1.0 / sqrt(1.0 - velocity * velocity / c2);
    
  double z_prime = gamma * ( x_.getZ() - velocity * t_);
  double t_prime = gamma * ( t_ - velocity * x_.getZ() / c2);
  x_.setZ(z_prime);
  t_ = t_prime;

  return 0; 
}

std::string FourVector::asString() const{
  std::ostringstream s;
  s << *this;
  return s.str();
}

void FourVector::compute_interval(){
  s_ = c2*t_*t_ - x_.length()*x_.length();        
} 

FourVector* createFourVector() {
  return new FourVector;
}

FourVector* createFourVector(const double t, const double x, const double y,
                             const double z) {
  FourVector *p = new FourVector(t, x, y, z);
  return p;
}

void destroyFourVector(FourVector *&p) {
  if(p){
    delete p;
    p = 0;
  }
}

std::istream& operator>>(std::istream& in, FourVector& vec){
  double t;
  ThreeVector p3;
  std::string dummy;
  in >> dummy >> t >> dummy >> p3 >> dummy;
  vec.setT(t);
  vec.setThreeVector(p3);
  return in;
}

std::ostream& operator<<(std::ostream& out, const FourVector& vec){
  out << "( " << vec.getT() << " , " << vec.getThreeVector() << " )";
  return out;
}

FourVector operator+(const FourVector& lhs, const FourVector& rhs){
  FourVector temp(lhs);
  temp += rhs;
  return temp;
}

FourVector operator-(const FourVector& lhs, const FourVector& rhs){
  FourVector temp(lhs);
  temp -= rhs;
  return temp;
}

FourVector operator*(const FourVector& lhs, const double rhs){
  FourVector temp(lhs);
  temp *= rhs;
  return temp;
}

FourVector operator*(const double lhs, const FourVector& rhs){
  FourVector temp(rhs);
  temp *= lhs;
  return temp;
}

FourVector operator/(const FourVector& lhs, const double rhs){
  FourVector temp(lhs);
  temp /= rhs;
  return temp;
}

double contraction(const FourVector& lhs, const FourVector& rhs){
  return lhs.getT() * rhs.getT() - lhs.getThreeVector().length() * rhs.getThreeVector().length();
}

