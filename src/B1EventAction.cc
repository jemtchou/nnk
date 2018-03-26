#include "B1EventAction.hh"

#include "B1RunAction.hh"
#include "B1SteppingAction.hh"
#include "PrimaryGeneratorAction.hh"
#include <time.h>

#include "RootWriter.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4Run.hh"

#include "TH1F.h"
#include "TTree.h"

B1EventAction* B1EventAction::fgInstance = 0;

B1EventAction* B1EventAction::Instance()
{
  return fgInstance;
}      

B1EventAction::B1EventAction(int runNumber)
: G4UserEventAction(),
  fPrintModulo(100)
{ 
  fgInstance = this;

  RootWriter* rw = RootWriter::GetPointer();
}

B1EventAction::~B1EventAction()
{ 
  fgInstance = 0;
}

void B1EventAction::BeginOfEventAction(const G4Event* event)
{
  Rmax = 0.;
  G4long total = G4RunManager::GetRunManager()->GetCurrentRun()->GetNumberOfEventToBeProcessed();
  fPrintModulo = G4int(total/20);
  if(fPrintModulo<1) fPrintModulo=1;
  
  G4int eventNb = event->GetEventID();
  if (eventNb%fPrintModulo == 0) {  
       char outstr[200];
       time_t t;
       struct tm *tmp;

       t = time(NULL);
       tmp = localtime(&t);
       strftime(outstr, sizeof(outstr), "%H%M%S.%d%m%Y", tmp);
  
       G4cout << "\n---> Begin of event: " << eventNb << " " << outstr << G4endl;
     } 
}

void B1EventAction::EndOfEventAction(const G4Event* /*event*/)
{
  Reset();

} 

void B1EventAction::Reset()
{
}
