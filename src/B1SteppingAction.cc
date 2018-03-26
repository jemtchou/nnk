#include "B1SteppingAction.hh"

//#include "NGKDetectorConstruction.hh"

#include "B1ParticleInfo.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "B1EventAction.hh"

#include <cassert>

using namespace CLHEP;

B1SteppingAction* B1SteppingAction::fgInstance = 0;

std::ofstream B1SteppingAction::fout;

B1SteppingAction* B1SteppingAction::Instance()
{
//	fout.open("pos.csv");
//	fout<<"id,x,y,z,time,kine"<<std::endl;
	return fgInstance;
}      

B1SteppingAction::B1SteppingAction()
: G4UserSteppingAction(),
  fVolume(0),
  fEnergy(0.)
{ 
  fgInstance = this;
}

B1SteppingAction::~B1SteppingAction()
{ 
//	fout.close();
}

void B1SteppingAction::UserSteppingAction(const G4Step* step)
{
  // if(particleType->GetPDGEncoding()==2112)
     {
       G4ThreeVector pos = step->GetTrack()->GetPosition();
       G4double r = pos.perp();
       ParticleInfo* info = (ParticleInfo*)(step->GetTrack()->GetUserInformation());
       if( info->Rmax < r )
	{
    	    info->Rmax = r;
	    info->PositionMax = pos;
	 //   info->Print(); 
	}
     }
}

void B1SteppingAction::Reset()
{
}

