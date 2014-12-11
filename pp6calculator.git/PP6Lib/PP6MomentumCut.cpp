//----------PP6MomentumCut.cpp----------
//----------==================----------

#include "PP6MomentumCut.hpp"

#include <cstdlib>
#include <cmath>
#include <iostream>

#include "PP6Math.hpp"
#include "PP6Particle.hpp"
#include "PP6ThreeVector.hpp"

MomentumCut::MomentumCut(const double lowerValue, const double upperValue) :
    type_(Range),
    lowerValue_(lowerValue),
    upperValue_(upperValue)
{
  checkValidity();
}

MomentumCut::MomentumCut(const CutType type, const double value) :
    type_(type),
    lowerValue_(value),
    upperValue_(value)
{
}

void MomentumCut::checkValidity(){
  if(lowerValue_ > upperValue_) {
    swap(lowerValue_, upperValue_);
  }
}

bool MomentumCut::select(const Particle& input) const{
  switch (type_) {
    case Range:
      return this->rangeCut(input);
    case LessThan:
      return this->lessThanCut(input);
    case GreaterThan:
      return this->greaterThanCut(input);
    default:
      std::cerr << "Unknown cut type!" << std::endl;
      return false;
  }
}

std::vector<Particle> MomentumCut::select(const std::vector<Particle>& input) const{
  std::vector<Particle> selected;
  selected.reserve(input.size());

  std::vector<Particle>::const_iterator iter = input.begin();
  std::vector<Particle>::const_iterator end = input.end();
  for(; iter != end; ++iter){
    if(this->select((*iter))){
      selected.push_back((*iter));
    }
  }

  return selected;
}

bool MomentumCut::rangeCut(const Particle& input) const{
  double mass = input.getMagMomentum();
  if(mass > lowerValue_ && mass < upperValue_){
    return true;
  } 

  else{
    return false;
  }
}

bool MomentumCut::lessThanCut(const Particle& input) const{
  double mass = input.getMagMomentum();
  if(mass < upperValue_){
    return true;
  } 
  
  else {
    return false;
  }
}

bool MomentumCut::greaterThanCut(const Particle& input) const{
  double mass = input.getMagMomentum();
  if(mass > lowerValue_){
    return true;
  } 

  else {
    return false;
  }
}

