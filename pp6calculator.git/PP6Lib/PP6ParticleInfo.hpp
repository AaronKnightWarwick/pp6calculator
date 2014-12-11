// File - PP6ParticleInfo.hpp
// Author - Aaron Knight 
// Brief - Declaration of PP6 ParticleInfo class

#ifndef PP6PARTICLEINFO_HPP
#define PP6PARTICLEINFO_HPP

#include <map>
#include <string>

class ParticleInfo {
 public:
  static const ParticleInfo& Instance( const std::string& dbFile = std::string("pdg.dbt") );

  size_t size() const;
  int getPDGCode(const std::string& name) const;
  int getCharge(const int id) const;
  std::string getName(const int id) const;
  double getMassMeV(const int id) const;
  double getMassGeV(const int id) const;

 private:
  explicit ParticleInfo( const std::string& dbFile );
  ParticleInfo(const ParticleInfo&);
  ~ParticleInfo() {}
  ParticleInfo& operator=(const ParticleInfo&);

  static ParticleInfo* theInstance;

  std::map<std::string, int> name_to_id;
  std::map<int, std::string> id_to_name;
  std::map<int, int> id_to_charge;
  std::map<int, double> id_to_mass;
};

#endif // PP6PARTICLEINFO_HPP
