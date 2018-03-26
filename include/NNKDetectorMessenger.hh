#ifndef NNKDetectorMessenger_h
#define NNKDetectorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class NNKDetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithABool;
class G4UIcmdWithAnInteger;

class NNKDetectorMessenger: public G4UImessenger
{
  public:
    NNKDetectorMessenger(NNKDetectorConstruction* );
    virtual ~NNKDetectorMessenger();
    
    virtual void SetNewValue(G4UIcommand*, G4int);
    
  private:
    NNKDetectorConstruction* NNKDetector;
    
    G4UIdirectory*             NNKDir;
    G4UIcmdWithAnInteger*        geometryConfCmd;
};

#endif

