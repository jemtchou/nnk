#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  PrimaryGeneratorAction(std::string src);    
  virtual ~PrimaryGeneratorAction();
  
  // static access method
  static PrimaryGeneratorAction* Instance();
  
  // method from the base class
  virtual void GeneratePrimaries(G4Event*);         
  
  // method to access particle gun
  const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
  
  int GetParticleCode(){ return particlecode; }
  double GetParticleEnergy() { return particleenergy; }
  void SetParticleCode( int code)  { particlecode=code;}
  void SetParticleEnergy( double energy)  {particleenergy = energy;} 
    
private:
  static PrimaryGeneratorAction* fgInstance;
  int particlecode;
  double particleenergy;
  G4ParticleGun*  fParticleGun; // pointer a to G4 gun class
  G4String type;
};

#endif


