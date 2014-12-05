// File -  PP6Particle.hpp
// Author -  Aaron Knight
// Brief -  Declaration of Particle class

#ifndef PP6PARTICLE_HPP
#define PP6PARTICLE_HPP

//----------Standard Library----------
//----------================----------

#include <string>
#include <vector>

//----------This Project----------
//----------============----------

#include "PP6FourVector.hpp"
#include "PP6ThreeVector.hpp"

class Particle {
public:
  Particle(); 
  Particle(const Particle& other);
  Particle(const int pdg_code, const double mass); 
  Particle(const int pdg_code, const double mass, const ThreeVector& momentum);
  Particle(const int pdg_code, const double mass, const double px, const double py, const double pz);
  
  Particle& operator=(const Particle& other);
  
  int getPDGCode() const { return pdg_code_; }
  double getMassGeV() const { return mass_; }
  const FourVector& getFourMomentum() const { return momentum_; }
  const ThreeVector& getThreeMomentum() const { return momentum_.getThreeVector(); }
  double getMagMomentum() const { return getThreeMomentum().length(); }
  double getEnergy() const { return momentum_.getT(); }
  
  void setPDGCode(const int pdg_code) { pdg_code_ = pdg_code; }
  void setMass(const double mass);
  void setThreeMomentum(const ThreeVector& p);
  void setThreeMomentum(const double px, const double py, const double pz);
  
private:
  int pdg_code_;
  double mass_;
  FourVector momentum_;
};

double calculate_invariant_mass(const Particle& first, const Particle& second);
double calculate_invariant_mass(const std::vector<Particle>& particles);

#endif // PP6PARTICLE_HPP
