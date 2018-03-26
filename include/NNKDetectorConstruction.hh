#ifndef NNKDetectorConstruction_h
#define NNKDetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include <vector>

class G4GeometrySampler;
class NNKDetectorMessenger;
class G4LogicalVolume;
class G4Element;
class G4Material;
class G4IStore;
class G4VImportanceAlgorithm;

class NNKDetectorConstruction : public G4VUserDetectorConstruction
{
public:
  NNKDetectorConstruction(int geo);
  ~NNKDetectorConstruction();

  G4VPhysicalVolume* Construct();

 // void DefineMaterials();
 // void SetupSonde();
 // void SetupLayer(G4String conf="WaterTank");
 // void InitializeImportanceSampling();
  void SetGeometryConfiguration(G4int conf);

  G4GeometrySampler* sampler;
protected:
  std::vector<G4VPhysicalVolume*> physvols;
  G4IStore* istore;
  G4VImportanceAlgorithm* ialg;

  NNKDetectorMessenger* detectorMessenger;

  G4int geometry;

  G4String layer;
  bool layerSetup;

  G4LogicalVolume *logicRock; 
  G4LogicalVolume *logicWell; 
  G4LogicalVolume *lWorld;
private:
  G4Element* H;
  G4Element* B; 
  G4Element* C; 
  G4Element* O;
  G4Element* Na; 
  G4Element* Mg; 
  G4Element* Al;
  G4Element* Si; 
  G4Element* S;
  G4Element* Cl;
  G4Element* K;
  G4Element* Ca;
  G4Element* Ti;
  G4Element* Cr;
  G4Element* Fe;
  G4Element* Ni;
  G4Element* Cu;
  G4Element* Zn;
  G4Element* Ge;
  G4Element* Sm;
  G4Element* Eu;
  G4Element* Gd;
  G4Element* W;
  G4Element* Pb;
  G4Element* Bi;
  G4Element* P; 
  G4Element* Mn;
  G4Element* Li;
  G4Element* Cd;
  G4Element* Ba;
  G4Element* Er;
  G4Element* Th;
  G4Element* U;
  G4Element* N;
  G4Element* V;
  G4Element* Mo;
  G4Element* Sr;
  G4Element* Zr;
  G4Element* Sn;

  G4Material* mRock; 
  G4Material* mCement; 
  G4Material* mPipe; 
  G4Material* mWellWater; 
  G4Material* mShield; 
  G4Material* mCase; 
  G4Material* mGenCase; 
  G4Material* mGenSteel; 
  G4Material* mOil; 
  G4Material* mGenVacuum; 
  G4Material* mNShield1; 
  G4Material* mNShield2; 
  G4Material* mNShield3; 
  G4Material* mSteel; 
  G4Material* mVacuum; 
  G4Material* mBi; 
  G4Material* mCd; 
  G4Material* mPolyamide;
  G4Material* mAluminium;
  G4Material* mStSteel;
  G4Material* mDet;
  G4Material* mBGO;
};

#endif
