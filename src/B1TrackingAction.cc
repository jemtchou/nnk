#include "B1TrackingAction.hh"

#include "B1ParticleInfo.hh"
#include "G4Track.hh"
#include "G4TrackVector.hh"
#include "G4TrackingManager.hh"
#include "G4EventManager.hh"
#include "G4NeutronHPManager.hh"
#include "G4HadronicProcess.hh"
#include "G4Nucleus.hh"
#include "G4VProcess.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"
#include "G4ParticleTable.hh"
#include "B1EventAction.hh"
#include "B1RunAction.hh"
#include "RootWriter.hh"

#include <map>

G4int mPDG;
G4double mEnergy;
G4double mTime;
G4int mDetId;
G4int mHit;
G4double mXmax;
G4double mYmax;
G4double mZmax;
G4double mRmax;
G4int mTrackId;
G4int mProc;
G4int mWeight;

B1TrackingAction::B1TrackingAction()
{
   RootWriter* rw = RootWriter::GetPointer();
   rw->tree = new TTree("gm","gm");
   rw->tree->Branch("pdgcode",&mPDG,"pdgcode/I");
   rw->tree->Branch("energy",&mEnergy,"energy/D");
   rw->tree->Branch("time",&mTime,"time/D");
   rw->tree->Branch("detId",&mDetId,"detId/I");
   rw->tree->Branch("hit",&mHit,"hit/I");  
   rw->tree->Branch("xmax",&mXmax,"xmax/D");
   rw->tree->Branch("ymax",&mYmax,"ymax/D");
   rw->tree->Branch("zmax",&mZmax,"zmax/D");
   rw->tree->Branch("rmax",&mRmax,"rmax/D");
   rw->tree->Branch("trackId",&mTrackId,"trackId/I");
   rw->tree->Branch("process",&mProc,"process/I");
   rw->tree->Branch("w",&mWeight,"w/D");

}

void B1TrackingAction::PreUserTrackingAction(const G4Track* track)
{
  G4int pdg = track->GetDefinition()->GetPDGEncoding();

  G4int parentid = track->GetParentID();
  G4VUserTrackInformation* info = new ParticleInfo;
  G4Track *  theTrack( const_cast< G4Track * >( track ) );
  theTrack->SetUserInformation(info);
}

void B1TrackingAction::PostUserTrackingAction(const G4Track* track) {
    G4String volname = track->GetVolume()->GetName();

    if(volname == "Detector1")
    { 
      mDetId = 1;
    } 
    else if (volname == "Detector2")
    { 
      mDetId = 2;
    } 
    else
      return;
 
    mPDG = track->GetDefinition()->GetPDGEncoding();
    mEnergy = track->GetTotalEnergy();
//    G4ThreeVector pos = track->GetPosition();
    mTime = track->GetGlobalTime();
    mTrackId = track->GetTrackID();
    mWeight = track->GetWeight();

    G4String pname;
    if(track->GetCreatorProcess())
        pname = track->GetCreatorProcess()->GetProcessName();
    else
        pname = "Generator";
    mProc = B1RunAction::Instance()->process[pname];

    ParticleInfo* info = (ParticleInfo*)(track->GetUserInformation());
    mXmax = info->PositionMax.x();
    mYmax = info->PositionMax.y();
    mZmax = info->PositionMax.z();
    mRmax = info->Rmax;

    mHit = 0;
    G4TrackVector* secondaries = G4EventManager::GetEventManager()->GetTrackingManager()->GimmeSecondaries();
    G4TrackVector::iterator it;
    for(it = secondaries->begin(); it!= secondaries->end(); it++)
    {
       G4int pdgcode = (*it)->GetDefinition()->GetPDGEncoding();
       if(pdgcode == 1000010030) // He3(n,p)H3, tritium detected
         {
           mHit = 1;
          G4cout << "FIREDD" << G4endl;
	 }

    }
    
    RootWriter::GetPointer()->tree->Fill();
}
