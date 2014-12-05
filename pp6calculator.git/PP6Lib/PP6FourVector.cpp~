//----------PP6 Four Vector----------
//----------===============----------

#include <PP6FourVector.hpp>
#include <cmath>
#include <sstream>

//Speed of light and speed of light squared
const double FourVector::c(3E8);
const double FourVector::c2(9E16);

//----------Member Operators----------
//----------================----------

FourVector& FourVector::operator=(const FourVector& other)
{
  if(this != &other){
    t_ = other.getT();
    x_ = other.getX();
    y_ = other.getY();
    z_ = other.getZ();
    s_ = other.interval();
  }
  return *this;
}

FourVector& FourVector::operator+=(const FourVector& rhs)
{
  t_ += rhs.getT();
  x_ += rhs.getX();
  y_ += rhs.getY();
  z_ += rhs.getZ();
  compute_interval();
  return *this;
}

FourVector& FourVector::operator-=(const FourVector& rhs)
{
  t_ -= rhs.getT();
  x_ -= rhs.getX();
  y_ -= rhs.getY();
  z_ -= rhs.getZ();
  compute_interval();
  return *this;
}

//----------Member Functions----------
//----------================----------

double FourVector::interval() const
{
  return s_;
}
int FourVector::boost_z(const double velocity)
{
  if(velocity >= c){
    return 1; 
  }
  double gamma = 1 / sqrt(1 - velocity * velocity / c2);
  double z_prime = gamma * ( z_ - velocity * t_);
  double t_prime = gamma * ( t_ - velocity * z_ / c2);
  z_ = z_prime;
  t_ = t_prime;
  return 0; 
}
std::string FourVector::asString() const
{
  std::ostringstream s;
  s << *this;
  return s.str();
}
void FourVector::compute_interval()
{

  s_ = c2*t_*t_ - (x_*x_ + y_*y_ + z_*z_);
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



std::istream& operator>>(std::istream& in, FourVector& vec)
{
  double x(0.0), y(0.0), z(0.0), t(0.0);
  in >> t >> x >> y >> z;
  vec.setT(t);
  vec.setX(x);
  vec.setY(y);
  vec.setZ(z);
  return in;
}

std::ostream& operator<<(std::ostream& out, const FourVector& vec)
{
  out << "(" << vec.getT() << ", " << vec.getX() << ", " << vec.getY() << ", " << vec.getZ() << ")";
  return out;
}

FourVector operator+(const FourVector& lhs, const FourVector& rhs)
{
  FourVector temp(lhs);
  temp += rhs;
  return temp;
}

FourVector operator-(const FourVector& lhs, const FourVector& rhs)
{
  FourVector temp(lhs);
  temp -= rhs;
  return temp;
}
