// File - PP6Particle.hpp
// Author - Aaron Knight
// Brief - Declaration of Particle class

#ifndef PP6PARTICLE_HPP
#define PP6PARTICLE_HPP

#include <iosfwd>
#include <string>
#include <vector>

#include "PP6FourVector.hpp"
class ThreeVector;

class Particle {
 public:
  Particle();  
  Particle(const Particle& other); 
  explicit Particle(const int pdg_code);
  Particle(const int pdg_code, const ThreeVector& momentum);
  Particle(const int pdg_code, const double px, const double py, const double pz);
  explicit Particle(const std::string& name);
  Particle(const std::string& name, const ThreeVector& momentum);
  Particle(const std::string& name, const double px, const double py, const double pz);

  Particle& operator=(const Particle& other);

  int getPDGCode() const { return pdg_code_; }
  std::string getName() const { return name_; }
  double getMassGeV() const { return mass_; }
  int getCharge() const { return charge_; }
  const FourVector& getFourMomentum() const { return momentum_; }
  const ThreeVector& getThreeMomentum() const { return momentum_.getThreeVector(); }
  double getMagMomentum() const { return getThreeMomentum().length(); }
  double getEnergy() const { return momentum_.getT(); }

  void setPDGCode(const int pdg_code);
  void setThreeMomentum(const ThreeVector& p);
  void setThreeMomentum(const double px, const double py, const double pz);

  int boost_z( const double velocity );


 private:
  int pdg_code_;
  std::string name_;
  double mass_;
  int charge_;
  FourVector momentum_;
};

std::ostream& operator<<( std::ostream& out, const Particle& particle );
std::istream& operator>>( std::istream& out, Particle& particle );

double calculate_invariant_mass(const Particle& first, const Particle& second);
double calculate_invariant_mass(const std::vector<Particle>& particles);

#endif // PP6PARTICLE_HPP
