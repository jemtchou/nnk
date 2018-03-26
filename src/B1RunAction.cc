#include "B1RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "B1EventAction.hh"
#include "B1SteppingAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

B1RunAction* B1RunAction::fgInstance = 0;

B1RunAction* B1RunAction::Instance()
{
  return fgInstance;
}

B1RunAction::B1RunAction()
: G4UserRunAction()
{
  fgInstance = this;
  // add new units for dose
  // 
  const G4double milligray = 1.e-3*gray;
  const G4double microgray = 1.e-6*gray;
  const G4double nanogray  = 1.e-9*gray;  
  const G4double picogray  = 1.e-12*gray;
   
  new G4UnitDefinition("milligray", "milliGy" , "Dose", milligray);
  new G4UnitDefinition("microgray", "microGy" , "Dose", microgray);
  new G4UnitDefinition("nanogray" , "nanoGy"  , "Dose", nanogray);
  new G4UnitDefinition("picogray" , "picoGy"  , "Dose", picogray);        
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1RunAction::~B1RunAction()
{}

void B1RunAction::BeginOfRunAction(const G4Run* aRun)
{ 
  process["Generator"] = 0;
  int j = 1;
  G4ParticleTable* ptable = G4ParticleTable::GetParticleTable();
  int k =0;
  for(k=0; k< ptable->entries(); k++)
  {
    G4ParticleDefinition* particle = ptable->GetParticle(k);
    if(! particle) continue;
    G4ProcessManager* pmanager = particle->GetProcessManager();
    int i;
    for (i=0; i<pmanager->GetProcessListLength();i++){
      j++;
     // G4cout << "Process " << j << " " << (*(pmanager->GetProcessList()))[i]->GetProcessName() << " of " << particle->GetParticleName() << G4endl;
      process[(*(pmanager->GetProcessList()))[i]->GetProcessName()] = j;
    }
  }

  G4cout << "Process list" << G4endl;
  std::map<G4String,int>::iterator it;
  j=0;
  for(it=process.begin(); it!=process.end(); it++)
  {
     (*it).second=j++;
  }
  for(it=process.begin(); it!=process.end(); it++)
  {
     G4cout << (*it).first << " " << (*it).second << G4endl;
  }

  

  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;

  //inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
    
  //initialize event cumulative quantities
  B1EventAction::Instance()->Reset();
}

void B1RunAction::EndOfRunAction(const G4Run* aRun)
{
/*  G4int nofEvents = aRun->GetNumberOfEvent();
  if (nofEvents == 0) return;
  
  // Compute dose
  //
  G4double energySum  = B1EventAction::Instance()->GetEnergySum();
  G4double energy2Sum = B1EventAction::Instance()->GetEnergy2Sum();
  G4double rms = energy2Sum - energySum*energySum/nofEvents;
  if (rms > 0.) rms = std::sqrt(rms); else rms = 0.;

  G4double mass = B1SteppingAction::Instance()->GetVolume()->GetMass();
  G4double dose = energySum/mass;
  G4double rmsDose = rms/mass;

  // Run conditions
  //
  const G4ParticleGun* particleGun 
    = PrimaryGeneratorAction::Instance()->GetParticleGun();
  G4String particleName 
    = particleGun->GetParticleDefinition()->GetParticleName();                       
  G4double particleEnergy = particleGun->GetParticleEnergy();
        
  // Print
  //  
  G4cout
     << "\n--------------------End of Run------------------------------\n"
     << " The run consists of " << nofEvents << " "<< particleName << " of "
     <<   G4BestUnit(particleEnergy,"Energy")      
     << "\n Dose in scoring volume " 
     << B1SteppingAction::Instance()->GetVolume()->GetName() << " : " 
     << G4BestUnit(dose,"Dose")
     << " +- "                   << G4BestUnit(rmsDose,"Dose")
     << "\n------------------------------------------------------------\n"
     << G4endl;
*/
}
