//----------PP6MassCut.cpp----------
//----------==============----------

#include "PP6MassCut.hpp"

#include <cstdlib>
#include <cmath>
#include <iostream>

#include "PP6Math.hpp"
#include "PP6Particle.hpp"
#include "PP6ThreeVector.hpp"

MassCut::MassCut( const double lowerValue, const double upperValue ) :
    type_( Range ),
    lowerValue_( lowerValue ),
    upperValue_( upperValue )
{
  checkValidity();
}

MassCut::MassCut( const CutType type, const double value ) :
    type_( type ),
    lowerValue_( value ),
    upperValue_( value )
{
}

void MassCut::checkValidity(){
  if( lowerValue_ > upperValue_ ){
    swap( lowerValue_, upperValue_ );
  }
}

bool MassCut::select(const Particle& input) const{
  switch ( type_ ) {
    case Range:
      return this->rangeCut( input );
    case LessThan:
      return this->lessThanCut( input );
    case GreaterThan:
      return this->greaterThanCut( input );
    default:
      std::cerr << "Unknown cut type!" << std::endl;
      return false;
  }
}

std::vector<Particle> MassCut::select(const std::vector<Particle>& input) const{
  std::vector<Particle> selected;
  selected.reserve( input.size() );

  std::vector<Particle>::const_iterator iter = input.begin();
  std::vector<Particle>::const_iterator end = input.end();
  for( ; iter != end; ++iter ){
    if( this->select( (*iter) ) ){
      selected.push_back( (*iter) );
    }
  }

  return selected;
}

bool MassCut::rangeCut(const Particle& input) const{
  double mass = input.getMassGeV();
  if( mass > lowerValue_ && mass < upperValue_ ){
    return true;
  } 

  else{
    return false;
  }
}

bool MassCut::lessThanCut(const Particle& input) const{
  double mass = input.getMassGeV();
  if( mass < upperValue_ ){
    return true;
  } 
  
  else {
    return false;
  }
}

bool MassCut::greaterThanCut(const Particle& input) const{
  double mass = input.getMassGeV();
  if( mass > lowerValue_ ){
    return true;
  } 

  else {
    return false;
  }
}

