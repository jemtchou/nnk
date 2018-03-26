#include "NNKDetectorMessenger.hh"

#include "NNKDetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4Material.hh"

NNKDetectorMessenger::NNKDetectorMessenger(NNKDetectorConstruction* NNKDet)
:NNKDetector(NNKDet)
{ 
  NNKDir = new G4UIdirectory("/nnk/");
  NNKDir->SetGuidance("UI commands specific for carotage");
  
  geometryConfCmd = new G4UIcmdWithAnInteger("/nnk/geometry",this);
  geometryConfCmd->SetGuidance("Select geometry configuration");
  geometryConfCmd->SetParameterName("configuration",false);
  geometryConfCmd->AvailableForStates(G4State_Idle);
//  geometryConfCmd->SetCandidates("0-16");
}

NNKDetectorMessenger::~NNKDetectorMessenger()
{
  delete geometryConfCmd;
  delete NNKDir;  
}

void NNKDetectorMessenger::SetNewValue(G4UIcommand* command, G4int newValue)
{ 
  if( command == geometryConfCmd ) {
    NNKDetector->SetGeometryConfiguration(newValue);
  }
}

