//----------PP6Day3MuonAnalysis.cpp-----------
//----------=======================-----------

#include "PP6Day3MuonAnalysis.hpp"

//----------Standard Library----------
//----------================----------

#include <iostream>

//----------Third Party----------
//----------===========----------

#include "FileReader.hpp"

//----------This Project----------
//----------============----------

#include "PP6Math.hpp"
#include "PP6Particle.hpp"

//----------Main Code----------
//----------=========----------

struct EventArray {
  size_t size;
  int *ids;
  Particle *particles;
};

EventArray* createEventArray(const size_t s) {
  EventArray* p = new EventArray;
  p->size = s;
  p->ids = new int[s];
  p->particles = new Particle[s];
  return p;
}

void destroyEventArray(EventArray *&p) {
  if(p){
    p->size = 0;
    delete [] p->ids;
    p->ids = 0;
    delete [] p->particles;
    p->particles = 0;
    delete p;
    p = 0;
  }
}

int getPDGCode(const std::string& name) {
  if(name == "mu-"){
    return 13;
  } 

  else if(name == "mu+"){
    return -13;
  }
  return 0;
}

int countParticles(const std::string& inputFile, const std::string& particle,
                   const std::string& runId, size_t& count) {
  FileReader counter(inputFile);
  if(!counter.isValid()){
    std::cerr << "[countParticles:error] " << inputFile << " is not valid"
              << std::endl;
    return 1;
  }

  count = 0;
  std::string particleName, dataID;

  while(counter.nextLine()){
    counter.getFieldAsInt(1);
    if(counter.inputFailed()) continue;

    particleName = counter.getFieldAsString(2);
    if(counter.inputFailed()){
      std::cerr << "[countParticles:error] Field 2 of " << inputFile
                << " is not a string" << std::endl;
      return 1;
    }

    dataID = counter.getFieldAsString(6);
    if(counter.inputFailed()){
      std::cerr << "[countParticles:error] Field 6 of "<< inputFile
                << " is not a string" << std::endl;
      return 1;
    }
    if(dataID == runId){
      if(particleName == particle) count++;
    }
  }
  return 0;
}
  
EventArray* createParticles(const std::string& inputFile,
                            const size_t knownNumber, 
                            const std::string& particle, 
                            const double, const std::string& runId) {
  FileReader counter(inputFile);
  if(!counter.isValid()){
    std::cerr << "[createParticles:error] " << inputFile
              << " is not valid" << std::endl;
    return 0;
  }
 
  EventArray* pEA = createEventArray(knownNumber);
  std::string particleName, dataID;
  int eventId;
  int pdgCode;
  int currentParticle;
  double px, py, pz;

  while(counter.nextLine()){
    eventId = counter.getFieldAsInt(1);
    if(counter.inputFailed()) continue;

    particleName = counter.getFieldAsString(2);
    if(counter.inputFailed()){
      std::cerr << "[countParticles:error] Field 2 of " << inputFile
                << " is not a string" << std::endl;
      destroyEventArray(pEA);
      return pEA;
    }

    dataID = counter.getFieldAsString(6);
    if(counter.inputFailed()){
      std::cerr << "[countParticles:error] Field 6 of " << inputFile
                << " is not a string" << std::endl;
      destroyEventArray(pEA);
      return pEA;
    }

    if(dataID == runId){
      if(particleName == particle){
        px = counter.getFieldAsDouble(3);
        if(counter.inputFailed()){
          std::cerr << "[createParticles:error] Field 3 of " << inputFile
                    << " is not a double" << std::endl;
          destroyEventArray(pEA);
          return pEA;
        }

        py = counter.getFieldAsDouble(4);
        if(counter.inputFailed()){
          std::cerr << "[countParticles:error] Field 4 of " << inputFile
                    << " is not a double" << std::endl;
          destroyEventArray(pEA);
          return pEA;
        }

        pz = counter.getFieldAsDouble(5);
        if(counter.inputFailed()){
          std::cerr << "[countParticles:error] Field 5 of " << inputFile
                    << " is not a double" << std::endl;
          destroyEventArray(pEA);
          return pEA;
        }
        
        pdgCode = getPDGCode(particle);
        (pEA->ids)[currentParticle] = eventId;
        (pEA->particles)[currentParticle] = Particle(pdgCode, px, py, pz);
        ++currentParticle;
      }
    }
  }
  
  return pEA;
}
  
EventArray* readParticles(const std::string& file, 
                          const std::string& particle, 
                          const double mass, const std::string& runId) {
  
  int res;
  size_t numberOf; 
  res = countParticles(file, particle, runId, numberOf);
  if(res){
    std::cerr << "[pp6day3_muonanalysis:error] Failed to count particles in file "
              << file << std::endl;
    return 0;
  }

  return createParticles(file, numberOf, particle, mass, runId);
}

int pp6day3_muonanalysis() {
  std::string muonFile;

  std::cout << "Enter filename to analyse: ";
  muonFile = getString();

  std::string runID("run4.dat");
  double muonMass = 0.105658366; 
  EventArray* p = readParticles(muonFile, "mu-", muonMass, runID);
  EventArray* q = readParticles(muonFile, "mu+", muonMass, runID);

  int combinations = p->size * q->size;
  double *invMasses = new double[combinations];
  int *indices = new int[combinations];

  for(size_t i; i < q->size; ++i){
    for (size_t j; j < p->size; ++j){
      int flatIndex = i * p->size + j;
      indices[flatIndex] = flatIndex;
      invMasses[flatIndex] = calculate_invariant_mass(q->particles[i],
                                                      p->particles[j]);
    }
  }

  associative_sort(invMasses, indices, combinations);

  std::cout << "Results:" << std::endl;
  std::cout << "========" << std::endl;
  std::cout << "Analysed File : " << muonFile << std::endl;
  std::cout << "Number of Muons     = " << p->size << std::endl;
  std::cout << "Number of AntiMuons = " << q->size << std::endl;
  std::cout << "----------------------------" << std::endl;

  for(int i; i < 10; ++i){
    int muonIndex(indices[i] % p->size);
    int antimuonIndex((indices[i] - muonIndex) / p->size);
    std::cout << "{InvariantMass : " << invMasses[indices[i]] << ",\n\t" << "{Muon : "
              << "Event = " << p->ids[muonIndex] << ", " << "(E, P) = ("
              << (p->particles[muonIndex]).getFourMomentum() << ")}\n\t"
              << "{AntiMuon : " << "Event = " << q->ids[antimuonIndex] << ", "
              << "(E, P) = (" << (q->particles[antimuonIndex]).getFourMomentum()
              << ")}\n" << "}" << std::endl;
    
  }

  destroyEventArray(p);
  destroyEventArray(q);
  delete [] invMasses;
  delete [] indices;
  return 0;
}

