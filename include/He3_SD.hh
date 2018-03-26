#ifndef He3_SD_h
#define He3_SD_h 1

#include "G4VSensitiveDetector.hh"

#include <vector>

class G4Step;
class G4HCofThisEvent;

class He3_SD : public G4VSensitiveDetector
{
  public:
    He3_SD(const G4String& name);
    virtual ~He3_SD();
  
    // methods from base class
    virtual void   Initialize(G4HCofThisEvent* hitCollection);
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
    virtual void   EndOfEvent(G4HCofThisEvent* hitCollection);

  private:

};

#endif
