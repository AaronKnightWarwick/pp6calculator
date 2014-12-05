#include "PP6Day4MuonAnalysis.hpp"



// Standard Library

#include <algorithm>

#include <iostream>

#include <vector>

#include <map>





// Third Party

#include "FileReader.hpp"



// This Project

#include "PP6Math.hpp"

#include "PP6Particle.hpp"

#include "PP6ParticleInfo.hpp"



namespace InvMass {

  typedef std::pair<int, Particle> Event;



  typedef std::vector<Event> EventVector; 



  typedef std::map<std::string, std::vector<Event> > RunMap;



  typedef std::pair<Event, Event> InvMassPair;

  typedef std::multimap<double, 

			InvMassPair,

			std::greater<double> > InvMassTable;

}



std::ostream& operator<<(std::ostream& out, const InvMass::Event& e) {

  out << "{" 

      << "Event : " << e.first << ", "

      << "Particle(" << e.second.getPDGCode()

      << ", " 

      << "(E, p) : " << e.second.getFourMomentum()

      << "}";

  return out;

}



class IsNotPDGCode {

public:

  explicit IsNotPDGCode(int pdgCode) : pdgCode_(pdgCode) {;}

  ~IsNotPDGCode() {;}



  bool operator()(const InvMass::Event& p) const {

    return (p.second).getPDGCode() != pdgCode_;

  }



private:

  int pdgCode_;

};



bool read_run_data(const std::string& runFile, const ParticleInfo& db, 

                   InvMass::RunMap& runTable) {



  FileReader reader(runFile);

  if (!reader.isValid()) {

    std::cerr << "[read_run_data:error] "

              << runFile

              << " is not valid"

              << std::endl;  

    return false;

  }



  reader.nextLine();



  std::string name(""), run("");

  int eventId;

  double px, py, pz;



  int pdgCode;



  while (reader.nextLine()) {

    eventId = reader.getField<int>(1);

    if (reader.inputFailed()) {

      std::cerr << "[read_run_data:error] Failed to to read event field from "

                << runFile

                << std::endl;

      return false;

    }

    name = reader.getField<std::string>(2);

    if (reader.inputFailed()) {

      std::cerr << "[read_run_data:error] Failed to to read name field from "

                << runFile

                << std::endl;

      return false;

    }



    px = reader.getField<double>(3);

    if (reader.inputFailed()) {

      std::cerr << "[read_run_data:error] Failed to to read p_x field from "

                << runFile

                << std::endl;

      return false;

    }



    py = reader.getField<double>(4);

    if (reader.inputFailed()) {

      std::cerr << "[read_run_data:error] Failed to to read p_y field from "

                << runFile

                << std::endl;

      return false;

    }



    pz = reader.getField<double>(5);

    if (reader.inputFailed()) {

      std::cerr << "[read_run_data:error] Failed to to read p_z field from "

                << runFile

                << std::endl;

      return false;

    }



    run = reader.getField<std::string>(6);

    if (reader.inputFailed()) {

      std::cerr << "[read_run_data:error] Failed to to read Data Source field from "

                << runFile

                << std::endl;

      return false;

    }



    pdgCode = db.getPDGCode(name);



    Particle tmp(pdgCode, px, py, pz);

    runTable[run].push_back(InvMass::Event(eventId,tmp));

  }



  return true;

}





int pp6day4_muonanalysis() {

  std::string dbtFilename;

  std::cout << "Enter path to .dbt file for initializing ParticleInfo: ";

  dbtFilename = getString();



  const ParticleInfo& particleDB = ParticleInfo::Instance(dbtFilename);

  std::cout << "Checking ParticleInfo contains entries... ";

  if (!particleDB.size()) {

    std::cout << "fail" << std::endl;

    return 1;

  } else {

    std::cout << "ok" << std::endl;

  }



  std::string muonFile;

  std::cout << "Enter filename to analyse: ";

  muonFile = getString();

 

  InvMass::RunMap allRuns;



  if (!read_run_data(muonFile, particleDB, allRuns)) {

    std::cerr << "[pp6day4_muonanalysis:error] Failed to read data from "

              << muonFile

              << std::endl;

    return 1;

  }



  InvMass::RunMap::iterator requiredRun = allRuns.find("run4.dat");

  if (requiredRun == allRuns.end()) {

    std::cerr << "[pp6day4_muonanalysis:error] No run4.dat records found in "

              << muonFile

              << std::endl;

    return 1;

  } 



  InvMass::EventVector negativeMuons;

  InvMass::EventVector positiveMuons;

  InvMass::RunMap::mapped_type::iterator start = (*requiredRun).second.begin();

  InvMass::RunMap::mapped_type::iterator stop = (*requiredRun).second.end();



  std::remove_copy_if(start, 

                      stop, 

                      std::back_inserter(negativeMuons), 

                      IsNotPDGCode(particleDB.getPDGCode("mu-")));



  std::remove_copy_if(start, 

                      stop, 

                      std::back_inserter(positiveMuons), 

                      IsNotPDGCode(particleDB.getPDGCode("mu+")));



  InvMass::InvMassTable invMasses;



  InvMass::EventVector::iterator negIter = negativeMuons.begin();

  InvMass::EventVector::iterator negEnd = negativeMuons.end();

  InvMass::EventVector::iterator posIter = positiveMuons.begin();

  InvMass::EventVector::iterator posEnd = positiveMuons.end();

  double invMass(0.0);



  for ( ; negIter != negEnd; ++negIter ) {

    // reset the positive muon vector

    posIter = positiveMuons.begin();



    for ( ; posIter != posEnd; ++posIter ) {

      invMass = calculate_invariant_mass((*negIter).second, (*posIter).second);

      invMasses.insert(std::make_pair(invMass, InvMass::InvMassPair(*negIter, *posIter)));

    }

  }

  InvMass::InvMassTable::iterator imIter = invMasses.begin();

  InvMass::InvMassTable::iterator imStop = invMasses.end();



  for (size_t i(0) ; imIter != imStop, i < 10 ; ++imIter, ++i) {

    std::cout << "{InvariantMass : " << (*imIter).first 

              << ",\n\t"

              << (*imIter).second.first 

              << "\n\t"

              << (*imIter).second.second

              << std::endl;

  }



  return 0;

}
