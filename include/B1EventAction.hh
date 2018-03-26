#ifndef B1EventAction_h
#define B1EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include <vector>

//typedef std::vector<int> VTrackId;
//typedef std::pair<int, VTrackId> PTrackId;

class B1SteppingAction;

class B1EventAction : public G4UserEventAction
{
public:
  B1EventAction(int runNumber);
  virtual ~B1EventAction();
  
  // static access method
  static B1EventAction* Instance();
  
  virtual void BeginOfEventAction(const G4Event* event);
  virtual void EndOfEventAction(const G4Event* event);
  
  void Reset();
  
  // get methods
//  B1ParticleRecordVector& GetParticleRecordVector(){return particles;};
  
//  void AddTrackId(int trackid);
//  bool CheckTrackId(int trackid);

//  void AddParticle(int trkid);
//  void AddTrack(int photonid, int trkid);
//  bool CheckParticle(int trkid);
//  int GetParticle(int trkid);
  
  G4double GetRmax(){return Rmax;}
  void SetRmax(G4double rmax) {Rmax=rmax;}

private:
  static B1EventAction* fgInstance;  
  
  G4double Rmax; // maximum radius of neutron travel

  G4int     fPrintModulo;
  
//  B1ParticleRecordVector particles;
//  std::vector<int> vtrackid;
//  std::vector<PTrackId> vp;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
