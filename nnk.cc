#include "NNKDetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"

#include "B1RunAction.hh"
#include "B1EventAction.hh"
#include "B1SteppingAction.hh"
#include "B1TrackingAction.hh"

#include "RootWriter.hh"

#include "G4GeometrySampler.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "Shielding.hh"
#include "Earth.hh"
#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
  int runNumber = 1;
  int geometry = 0;
  if (argc>2) {
    geometry = atoi(argv[2]);
    runNumber = atoi(argv[3]);
    G4cout << "RunNumber " << runNumber << G4endl;
  }
  // Choose the Random engine
  //
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
  
  RootWriter* rw = RootWriter::GetPointer();
  rw->Initialize(true);

  // Construct the default run manager
  //
  G4RunManager * runManager = new G4RunManager;

  // Set mandatory initialization classes
  // Physics list
  G4VModularPhysicsList* physicsList = new Earth;
  physicsList->SetVerboseLevel(1);
  runManager->SetUserInitialization(physicsList);

  // Detector construction
  NNKDetectorConstruction* geom = new NNKDetectorConstruction(geometry);
  runManager->SetUserInitialization(geom);

  // Primary generator action
  runManager->SetUserAction(new PrimaryGeneratorAction("PuBe",geometry));

  // Set user action classes
  // Tracking action
  runManager->SetUserAction(new B1TrackingAction());

  // Stepping action
  runManager->SetUserAction(new B1SteppingAction());     

  // Event action
  runManager->SetUserAction(new B1EventAction(runNumber));

  // Run action
  runManager->SetUserAction(new B1RunAction());
     
  // Initialize G4 kernel
  //
  runManager->Initialize();
  //geom->sampler->Configure();


  long rand[2];
  rand[0] = long(runNumber*1000000 + 123456);
  rand[1] = 123456789;
  const long* rand1 = rand;
  CLHEP::HepRandom::setTheSeeds(rand1);
  
#ifdef G4VIS_USE
  // Initialize visualization
  G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();
#endif

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if (argc!=1) {
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else {
    // interactive mode : define UI session
#ifdef G4UI_USE
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
#ifdef G4VIS_USE
    UImanager->ApplyCommand("/control/execute init_vis.mac"); 
#else
    UImanager->ApplyCommand("/control/execute init.mac"); 
#endif
    ui->SessionStart();
    delete ui;
#endif
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted 
  // in the main() program !
  
  rw->Finalize();

#ifdef G4VIS_USE
  delete visManager;
#endif
  delete runManager;

  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
