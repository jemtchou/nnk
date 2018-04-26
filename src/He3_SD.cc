#include "He3_SD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "B1EventAction.hh"
#include "G4VProcess.hh"
#include "G4EventManager.hh"

using namespace CLHEP;

bool fired;

He3_SD::He3_SD(const G4String& name) 
  : G4VSensitiveDetector(name)
{
}

He3_SD::~He3_SD() 
{}

void He3_SD::Initialize(G4HCofThisEvent* hce)
{
  fired=false;
}

G4bool He3_SD::ProcessHits(G4Step* step, 
			   G4TouchableHistory*)
{  
  // energy deposit
  G4double edep = step->GetTotalEnergyDeposit();
  G4int pdgcode =  step->GetTrack()->GetDefinition()->GetPDGEncoding();
  G4double energy =  step->GetTrack()->GetKineticEnergy();
  G4double time =  step->GetPostStepPoint()->GetGlobalTime();

  G4int detector = 0;
  G4String detname = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName();
  if(detname=="Detector1") detector = 1;
  if(detname=="Detector2") detector = 2;

//  G4cout << " HIT " << step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName() << " " << pdgcode << " " << energy << " " << time/ns << " " << step->GetTrack()->GetTrackID() << G4endl;

  // get volume of the current step
  G4LogicalVolume* prevolume
    = step->GetPreStepPoint()->GetTouchableHandle()
    ->GetVolume()->GetLogicalVolume();
  G4LogicalVolume* postvolume = 0;
  if( step->GetPostStepPoint()->GetTouchableHandle()->GetVolume() )
    postvolume = step->GetPostStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();

//  G4cout << "VOLS1 " << prevolume->GetName() << G4endl;
//  if(postvolume>0) G4cout << "VOLS2 " << postvolume->GetName() << G4endl;

 // G4int fired = false;
  if(pdgcode == 1000010030) // He3(n,p)H3, tritium detected
    {
//      G4cout << "DETECTOR FIRED" << G4endl;
      fired = true;
    }

  return true;
}

void He3_SD::EndOfEvent(G4HCofThisEvent*)
{
// if(fired) G4cout << "Rmax " <<  B1EventAction::Instance()->GetRmax()/mm << G4endl;
}

