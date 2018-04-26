#include"NNKDetectorConstruction.hh"
#include"He3_SD.hh" 
#include<G4NistManager.hh>
#include<G4Box.hh>
#include<G4Tubs.hh>
#include<G4LogicalVolume.hh>
#include<G4PVPlacement.hh>
#include<G4SDManager.hh>
#include<G4VisAttributes.hh>
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4RunManager.hh"
#include "NNKDetectorMessenger.hh"

using namespace std;


NNKDetectorConstruction::NNKDetectorConstruction(int geo)
{
  geometry = geo;
  detectorMessenger = new NNKDetectorMessenger(this);
}

NNKDetectorConstruction::~NNKDetectorConstruction()
{
}

void NNKDetectorConstruction::SetGeometryConfiguration(G4int conf)
{
  G4cout << "Set geometry configuration " << conf << G4endl;
  geometry = conf; 
 
  if(geometry<0 || geometry>16)
    G4Exception("NGKDetectorConstruction","Wrong Layer Geometry",RunMustBeAborted,"Please choose correct rock material");

  Construct();
  
  G4RunManager::GetRunManager()->GeometryHasBeenModified();
}


G4VPhysicalVolume* NNKDetectorConstruction::Construct()
{
  // --- materials ---

  G4NistManager* man = G4NistManager::Instance();
  //H=man->FindOrBuildElement("H");
  B=man->FindOrBuildElement("B");
  C=man->FindOrBuildElement("C");

  Li=man->FindOrBuildElement("Li");
  Cd=man->FindOrBuildElement("Cd");
  Ba=man->FindOrBuildElement("Ba");
  Er=man->FindOrBuildElement("Er");
  Th=man->FindOrBuildElement("Th");
  U=man->FindOrBuildElement("U");

  O=man->FindOrBuildElement("O");
  N=man->FindOrBuildElement("N");
  Na=man->FindOrBuildElement("Na");
  Mg=man->FindOrBuildElement("Mg");
  Al=man->FindOrBuildElement("Al");
  Si=man->FindOrBuildElement("Si");
  P=man->FindOrBuildElement("P");
  S=man->FindOrBuildElement("S");
  Cl=man->FindOrBuildElement("Cl");
  K=man->FindOrBuildElement("K");
  Ca=man->FindOrBuildElement("Ca");
  Ti=man->FindOrBuildElement("Ti");
  Cr=man->FindOrBuildElement("Cr");
  Mn=man->FindOrBuildElement("Mn");	
  Fe=man->FindOrBuildElement("Fe");
  Ni=man->FindOrBuildElement("Ni");
  Cu=man->FindOrBuildElement("Cu");
  Zn=man->FindOrBuildElement("Zn");
  Ge=man->FindOrBuildElement("Ge");
  Sm=man->FindOrBuildElement("Sm");
  Eu=man->FindOrBuildElement("Eu");
  Gd=man->FindOrBuildElement("Gd");
  W=man->FindOrBuildElement("W");
  Pb=man->FindOrBuildElement("Pb");
  Bi=man->FindOrBuildElement("Bi");
//new  
  V = man->FindOrBuildElement("V");
  Mo = man->FindOrBuildElement("Mo");
  Sr = man->FindOrBuildElement("Sr");
  Zr = man->FindOrBuildElement("Zr");
  Sn = man->FindOrBuildElement("Sn");	

  H = new G4Element("TS_H_of_Water","H",1,1*g/mole);

  G4cout << "Geometry configuration " << geometry << G4endl;


  if(geometry==0){
   mRock = G4NistManager::Instance()->FindOrBuildMaterial("G4_WATER");
  }

double shifty1;
  // rock
if (geometry == 1) {
	shifty1 = 0 * mm;
	mRock = new G4Material("mRock", 2.73*g / cm3, 4); // Kp=0.8% CaCO3
	mRock->AddElement(Ca, 40.0*perCent);
	mRock->AddElement(C,  12.0*perCent);
	mRock->AddElement(H,  0.03*perCent);
	mRock->AddElement(O,  47.97*perCent);
}

if (geometry == 2) {
	shifty1 = 0 * mm;
	mRock = new G4Material("mRock", 2.46*g / cm3, 4); // Kp=15.9% CaCO3
	mRock->AddElement(Ca, 37.4*perCent);
	mRock->AddElement(C,  11.3*perCent);
	mRock->AddElement(H,  0.7*perCent);
	mRock->AddElement(O,  50.6*perCent);
}
if (geometry == 3) {
	shifty1 = 0 * mm;
	mRock = new G4Material("mRock", 2.13*g / cm3, 4); // Kp=35.2% CaCO3
	mRock->AddElement(Ca, 33.4*perCent);
	mRock->AddElement(C, 10.0*perCent);
	mRock->AddElement(H, 1.8*perCent);
	mRock->AddElement(O, 54.8*perCent);
}

if (geometry == 4) {
	shifty1 = 9.5 * mm;
	mRock = new G4Material("mRock", 2.73*g / cm3, 4); // Kp=0.8% CaCO3
	mRock->AddElement(Ca, 40.0*perCent);
	mRock->AddElement(C, 12.0*perCent);
	mRock->AddElement(H, 0.03*perCent);
	mRock->AddElement(O, 47.97*perCent);
}

if (geometry == 5) {
	shifty1 = 9.5 * mm;
	mRock = new G4Material("mRock", 2.46*g / cm3, 4); // Kp=15.9% CaCO3
	mRock->AddElement(Ca, 37.4*perCent);
	mRock->AddElement(C, 11.3*perCent);
	mRock->AddElement(H, 0.7*perCent);
	mRock->AddElement(O, 50.6*perCent);
}
if (geometry == 6) {
	shifty1 = 9.5 * mm;
	mRock = new G4Material("mRock", 2.13*g / cm3, 4); // Kp=35.2% CaCO3
	mRock->AddElement(Ca, 33.4*perCent);
	mRock->AddElement(C, 10.0*perCent);
	mRock->AddElement(H, 1.8*perCent);
	mRock->AddElement(O, 54.8*perCent);
}


  G4Material* mTitan0 = new G4Material("mTitan0", 4.55*g / cm3, 10);
     mTitan0->AddElement(Fe, 0.3*perCent);
     mTitan0->AddElement(C, 0.1*perCent);
     mTitan0->AddElement(Si, 0.12*perCent);
     mTitan0->AddElement(Mn, 1.4*perCent);
     mTitan0->AddElement(N, 0.05*perCent);
     mTitan0->AddElement(Ti, 93.37*perCent);
     mTitan0->AddElement(Al, 4.2*perCent);
     mTitan0->AddElement(Zr, 0.3*perCent);
     mTitan0->AddElement(O, 0.15*perCent);
     mTitan0->AddElement(H, 0.01*perCent);

  G4Material* mSteel0 = new G4Material("mSteel0", 7.92*g / cm3, 10);
     mSteel0->AddElement(C, 0.12*perCent);
     mSteel0->AddElement(Si, 0.8*perCent);
     mSteel0->AddElement(Mn, 2 * perCent);
     mSteel0->AddElement(S, 0.02*perCent);
     mSteel0->AddElement(P, 0.035*perCent);
     mSteel0->AddElement(Cr, 18 * perCent);
     mSteel0->AddElement(Ni, 10 * perCent);
     mSteel0->AddElement(Ti, 0.8*perCent);
     mSteel0->AddElement(Cu, 0.3*perCent);
     mSteel0->AddElement(Fe, 67.925*perCent);


  G4Material* mWell = G4NistManager::Instance()->FindOrBuildMaterial("G4_WATER");
  G4Material* mAir = G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR");

   G4Material* mPoly = new G4Material("mPoly", 1.1*g / cm3, 4); //[-NH-(CH2)5-CO-]
     mPoly->AddElement(C, 6);
     mPoly->AddElement(N, 1);
     mPoly->AddElement(O, 1);
     mPoly->AddElement(H, 11);
     
   G4Material* mRubber = new G4Material("mRubber", 1.0*g / cm3, 2);
     mRubber->AddElement(H, 14 * perCent);
     mRubber->AddElement(C, 86 * perCent);
     
   G4Material* mSteel = new G4Material("mSteel", 7.75*g / cm3, 8);
     mSteel->AddElement(C, 0.15*perCent);
     mSteel->AddElement(Cr, 0.17*perCent);
     mSteel->AddElement(Mn, 0.8*perCent);
     mSteel->AddElement(Ni, 2 * perCent);
     mSteel->AddElement(P, 0.03*perCent);
     mSteel->AddElement(S, 0.025*perCent);
     mSteel->AddElement(Si, 0.8*perCent);
     mSteel->AddElement(Fe, 96.025*perCent);
     
   G4Material* mBronze = new G4Material("mBronze", 7.5*g / cm3, 9);
     mBronze->AddElement(Fe, 3 * perCent);
     mBronze->AddElement(Si, 0.1*perCent);
     mBronze->AddElement(Mn, 0.5*perCent);
     mBronze->AddElement(P, 0.01*perCent);
     mBronze->AddElement(Al, 9 * perCent);
     mBronze->AddElement(Cu, 86.28*perCent);
     mBronze->AddElement(Pb, 0.01*perCent);
     mBronze->AddElement(Zn, 1 * perCent);
     mBronze->AddElement(Sn, 0.1*perCent);
     
   G4Material* mTitan = new G4Material("mTitan", 4.45*g / cm3, 10);
     mTitan->AddElement(Fe, 0.6*perCent);
     mTitan->AddElement(C, 0.1*perCent);
     mTitan->AddElement(Si, 0.1*perCent);
     mTitan->AddElement(V, 4 * perCent);
     mTitan->AddElement(N, 0.05*perCent);
     mTitan->AddElement(Ti, 88.635*perCent);
     mTitan->AddElement(Al, 6 * perCent);
     mTitan->AddElement(Zr, 0.3*perCent);
     mTitan->AddElement(O, 0.2*perCent);
     mTitan->AddElement(H, 0.015*perCent);
     
   G4Material* mSLW3 = new G4Material("mSLW3", 7.77*g / cm3, 8);
     mSLW3->AddElement(C, 0.03*perCent);
     mSLW3->AddElement(Si, 1 * perCent);
     mSLW3->AddElement(Mn, 21 * perCent);
     mSLW3->AddElement(Cr, 18 * perCent);
     mSLW3->AddElement(Mo, 0.6*perCent);
     mSLW3->AddElement(Ni, 2 * perCent);
     mSLW3->AddElement(N, 0.6*perCent);
     mSLW3->AddElement(Fe, 56.77*perCent);
     
   G4Material* mAluminium = new G4Material("mAluminium", 13, 26.092*g / mole, 2.7*g / cm3);
     										
   G4Material* mVacuum = new G4Material("mVacuum", 1, 1, universe_mean_density, kStateGas, 0.1*kelvin, 1.e-19*pascal); // vacuum
     
   G4Material* mCd = new G4Material("mCd", 48, 112 * g / mole, 8.65*g / cm3);  //Cd
      
 // He3 counter
  G4Isotope* izHe3 = new G4Isotope("izHe3",2, 3);
  G4Element* elHe3= new G4Element("He3", "He3",1);
  elHe3->AddIsotope(izHe3, 100*perCent);
  G4double density = 1 *mg/cm3;
  G4double pressure = 5.*atmosphere;
  G4double temperature = 300.*kelvin;
  mDet = new G4Material("He3", density, 1, kStateGas, temperature, pressure);
  mDet->AddElement(elHe3,1);
 

//Geometry
// Мировой объем 
  G4Tubs* sWorld = new G4Tubs("World", 0, 1001*mm, 1001*mm, 0, 360.*deg);
  lWorld = new G4LogicalVolume( sWorld, mVacuum, "World", 0, 0, 0);
  G4PVPlacement* pWorld = new G4PVPlacement(0, G4ThreeVector(), lWorld, "World",
					    0, false, 0);      

  //Порода C2 H=2000.0 R=1000.0 r=108.0
  G4Tubs *solid2 = new G4Tubs("C2", 63.5 * mm, 1000.0 * mm, 1000.0*mm, 0, 360 * deg);
  G4LogicalVolume *logic2 = new G4LogicalVolume(solid2, mRock, "logic2");
  new G4PVPlacement(0, G4ThreeVector(), logic2, "phys2", lWorld, false, 0);
  logic2->SetVisAttributes(new G4VisAttributes(G4Colour::Yellow()));

  //Обсадка  C2.1 H=2000.0 R=63.5 r=62.0
  G4Tubs *solid2_1 = new G4Tubs("C2.1", 62.0 * mm, 63.5 * mm, 1000*mm, 0, 360 * deg);
  G4LogicalVolume *logic2_1 = new G4LogicalVolume(solid2_1, mAluminium, "logic2.1");
  new G4PVPlacement(0, G4ThreeVector(), logic2_1, "phys2.1", lWorld, false, 0);
  logic2_1->SetVisAttributes(new G4VisAttributes(G4Colour::Green()));

  //Скважина C3 H=2000.0 R=62.0 r=0.0
  G4Tubs *solid3 = new G4Tubs("C3", 0.0 * mm, 62.0 * mm, 1000.0*mm, 0, 360 * deg);
  G4LogicalVolume *logic3 = new G4LogicalVolume(solid3, mWell, "logic3");
  new G4PVPlacement(0, G4ThreeVector(), logic3, "phys3", lWorld, false, 0);
  logic3->SetVisAttributes(new G4VisAttributes(G4Colour::Blue()));

  //УБТ C4 r=28.5 R=52.5 H=2000.0 # УБТ
  G4Tubs *solid4 = new G4Tubs("C4", 28.5 * mm, 52.5 * mm, 1000.0*mm, 0, 360 * deg);
  G4LogicalVolume *logic4 = new G4LogicalVolume(solid4, mSLW3, "logic4");
  new G4PVPlacement(0, G4ThreeVector(0, shifty1, 0.0*mm), logic4, "phys4", logic3, false, 0);
  logic4->SetVisAttributes(new G4VisAttributes(G4Colour::Grey()));
  //объем прибора C5 r=0.0 R=24.0 H=1400.0 # объем прибора
  G4Tubs *solid5 = new G4Tubs("C5", 0.0 * mm, 24.0 * mm, 700.0*mm, 0, 360 * deg);
  G4LogicalVolume *logic5 = new G4LogicalVolume(solid5, mAir, "logic5");
  new G4PVPlacement(0, G4ThreeVector(0, shifty1, 0.0*mm), logic5, "phys5", logic3, false, 0);
  logic5->SetVisAttributes(new G4VisAttributes(G4Colour::Green()));

  //Обтекатель C6 r=0.0 R=20.0 H=162.0 # Обтекатель
  G4Tubs *solid6 = new G4Tubs("C6", 0.0 * mm, 20.0 * mm, 81.0*mm, 0, 360 * deg);
  G4LogicalVolume *logic6 = new G4LogicalVolume(solid6, mBronze, "logic6");
  new G4PVPlacement(0, G4ThreeVector(0, 0, 619.0*mm), logic6, "phys6", logic5, false, 0);
  logic6->SetVisAttributes(new G4VisAttributes(G4Colour::Cyan()));
  //Наконечник прибора C7 r=20.0 R=24.0 H=62.0 # Наконечник прибора
  G4Tubs *solid7 = new G4Tubs("C7", 20.0 * mm, 24.0 * mm, 31.0*mm, 0, 360 * deg);
  G4LogicalVolume *logic7 = new G4LogicalVolume(solid7, mTitan, "logic7");
  new G4PVPlacement(0, G4ThreeVector(0, 0, 569.0*mm), logic7, "phys7", logic5, false, 0);
  logic7->SetVisAttributes(new G4VisAttributes(G4Colour::Black()));
  //Наконечник прибора С8 r=14.0 R=24.0 H=50.0 # Наконечник прибора
  G4Tubs *solid8 = new G4Tubs("C8", 14.0 * mm, 24.0 * mm, 25.0*mm, 0, 360 * deg);
  G4LogicalVolume *logic8 = new G4LogicalVolume(solid8, mTitan, "logic8");
  new G4PVPlacement(0, G4ThreeVector(0, 0, 513.0*mm), logic8, "phys8", logic5, false, 0);
  logic8->SetVisAttributes(new G4VisAttributes(G4Colour::Black()));
  //Бронзовый корпус источника C9 r=0.0 R=14.0 H=28.0 # Бронзовый корпус источника
  G4Tubs *solid9 = new G4Tubs("C9", 0.0 * mm, 14.0 * mm, 14.0*mm, 0, 360 * deg);
  G4LogicalVolume *logic9 = new G4LogicalVolume(solid9, mBronze, "logic9");
  new G4PVPlacement(0, G4ThreeVector(0, 0, 524.0*mm), logic9, "phys9", logic5, false, 0);
  logic9->SetVisAttributes(new G4VisAttributes(G4Colour::Cyan()));
  //Бронзовый корпус источника С10 r=9.0 R=14.0 H=22.0 # Бронзовый корпус источника
  G4Tubs *solid10 = new G4Tubs("C10", 9.0 * mm, 14.0 * mm, 11.0*mm, 0, 360 * deg);
  G4LogicalVolume *logic10 = new G4LogicalVolume(solid10, mBronze, "logic10");
  new G4PVPlacement(0, G4ThreeVector(0, 0, 499.0*mm), logic10, "phys10", logic5, false, 0);
  logic10->SetVisAttributes(new G4VisAttributes(G4Colour::Cyan()));
  //Корпус источника C11 r=0.0 R=9.0 H=6.0 # Корпус источника
  G4Tubs *solid11 = new G4Tubs("C11", 0.0 * mm, 9.0 * mm, 3.0*mm, 0, 360 * deg);
  G4LogicalVolume *logic11 = new G4LogicalVolume(solid11, mSteel, "logic11");
  new G4PVPlacement(0, G4ThreeVector(0, 0, 507.0*mm), logic11, "phys11", logic5, false, 0);
  logic11->SetVisAttributes(new G4VisAttributes(G4Colour::Red()));
  //Корпус источника C12 r=5.0 R=9.0 H=10.0 # Корпус источника
  G4Tubs *solid12 = new G4Tubs("C12", 5.0 * mm, 9.0 * mm, 5.0*mm, 0, 360 * deg);
  G4LogicalVolume *logic12 = new G4LogicalVolume(solid12, mSteel, "logic12");
  new G4PVPlacement(0, G4ThreeVector(0, 0, 499.0*mm), logic12, "phys12", logic5, false, 0);
  logic12->SetVisAttributes(new G4VisAttributes(G4Colour::Red()));
  //Корпус источника C13 r=0.0 R=9.0 H=6.0 # Корпус источника
  G4Tubs *solid13 = new G4Tubs("C13", 0.0 * mm, 9.0 * mm, 3.0*mm, 0, 360 * deg);
  G4LogicalVolume *logic13 = new G4LogicalVolume(solid13, mSteel, "logic13");
  new G4PVPlacement(0, G4ThreeVector(0, 0, 491.0*mm), logic13, "phys13", logic5, false, 0);
  logic13->SetVisAttributes(new G4VisAttributes(G4Colour::Red()));
  //Источник С14 r=0.0 R=5.0 H=10.0 # Источник
  G4Tubs *solid14 = new G4Tubs("C14", 0.0 * mm, 5.0 * mm, 5.0*mm, 0, 360 * deg);
  G4LogicalVolume *logic14 = new G4LogicalVolume(solid14, mAluminium, "logic14");
  new G4PVPlacement(0, G4ThreeVector(0, 0, 499.0*mm), logic14, "Source", logic5, false, 0);
  logic14->SetVisAttributes(new G4VisAttributes(G4Colour::White()));
  //Наконечник прибора C15 r=0.0 R=24.0 H=25.0 # Наконечник прибора
  G4Tubs *solid15 = new G4Tubs("C15", 0.0 * mm, 24.0 * mm, 12.5*mm, 0, 360 * deg);
  G4LogicalVolume *logic15 = new G4LogicalVolume(solid15, mTitan, "logic15");
  new G4PVPlacement(0, G4ThreeVector(0, 0, 475.5*mm), logic15, "phys15", logic5, false, 0);
  logic15->SetVisAttributes(new G4VisAttributes(G4Colour::Black()));
  //Корпус прибора С16 r=19.75 R=24.0 H=822.0 # Корпус прибора
  G4Tubs *solid16 = new G4Tubs("C16", 19.75 * mm, 24.0 * mm, 411.0*mm, 0, 360 * deg);
  G4LogicalVolume *logic16 = new G4LogicalVolume(solid16, mTitan0, "logic16");
  new G4PVPlacement(0, G4ThreeVector(0, 0, 52.0*mm), logic16, "phys16", logic5, false, 0);
  logic16->SetVisAttributes(new G4VisAttributes(G4Colour::Magenta()));
  //Наконечник прибора C17 r=0.0 R=19.75 H=44.0 # Наконечник прибора
  G4Tubs *solid17 = new G4Tubs("C17", 0.0 * mm, 19.75 * mm, 22.0*mm, 0, 360 * deg);
  G4LogicalVolume *logic17 = new G4LogicalVolume(solid17, mTitan, "logic17");
  new G4PVPlacement(0, G4ThreeVector(0, 0, 441.0*mm), logic17, "phys17", logic5, false, 0);
  logic17->SetVisAttributes(new G4VisAttributes(G4Colour::Black()));
  //Наконечник прибора C18 r=9.25 R=19.75 H=18.0 # Наконечник прибора
  G4Tubs *solid18 = new G4Tubs("C18", 9.25 * mm, 19.75 * mm, 9.0*mm, 0, 360 * deg);
  G4LogicalVolume *logic18 = new G4LogicalVolume(solid18, mTitan, "logic18");
  new G4PVPlacement(0, G4ThreeVector(0, 0, 410.0*mm), logic18, "phys18", logic5, false, 0);
  logic18->SetVisAttributes(new G4VisAttributes(G4Colour::Black()));
  //Экран C19 r=0.0 R=9.25 H=18.0 # Экран
  G4Tubs *solid19 = new G4Tubs("C19", 0.0 * mm, 9.25 * mm, 9.0*mm, 0, 360 * deg);
  G4LogicalVolume *logic19 = new G4LogicalVolume(solid19, mPoly, "logic19");
  new G4PVPlacement(0, G4ThreeVector(0, 0, 410.0*mm), logic19, "phys19", logic5, false, 0);
  logic19->SetVisAttributes(new G4VisAttributes(G4Colour::Brown()));
  //Экран С20 r=0.0 R=19.75 H=98.0 # Экран
  G4Tubs *solid20 = new G4Tubs("C20", 0.0 * mm, 19.75 * mm, 49.0*mm, 0, 360 * deg);
  G4LogicalVolume *logic20 = new G4LogicalVolume(solid20, mPoly, "logic20");
  new G4PVPlacement(0, G4ThreeVector(0, 0, 352.0*mm), logic20, "phys20", logic5, false, 0);
  logic20->SetVisAttributes(new G4VisAttributes(G4Colour::Brown()));
  //Гайка С21 r=0.0 R=19.75 H=36.0 # Гайка
  G4Tubs *solid21 = new G4Tubs("C21", 0.0 * mm, 19.75 * mm, 18.0*mm, 0, 360 * deg);
  G4LogicalVolume *logic21 = new G4LogicalVolume(solid21, mSteel, "logic21");
  new G4PVPlacement(0, G4ThreeVector(0, 0, 285.0*mm), logic21, "phys21", logic5, false, 0);
  logic21->SetVisAttributes(new G4VisAttributes(G4Colour::Magenta()));
  //Кожух С22 r=17.0 R=19.0 H=389.0 # Кожух
  G4Tubs *solid22 = new G4Tubs("C22", 17.0 * mm, 19.0 * mm, 194.5*mm, 0, 360 * deg);
  G4LogicalVolume *logic22 = new G4LogicalVolume(solid22, mSteel0, "logic22");
  new G4PVPlacement(0, G4ThreeVector(0, 0, 72.5*mm), logic22, "phys22", logic5, false, 0);
  logic22->SetVisAttributes(new G4VisAttributes(G4Colour::Blue()));
  //Амортизатор C23 r=8.5 R=16.5 H=7.0 # Амортизатор
  G4Tubs *solid23 = new G4Tubs("C23", 8.5 * mm, 16.5 * mm, 3.5*mm, 0, 360 * deg);
  G4LogicalVolume *logic23 = new G4LogicalVolume(solid23, mRubber, "logic23");
  new G4PVPlacement(0, G4ThreeVector(0, 0, 263.5*mm), logic23, "phys23", logic5, false, 0);
  logic23->SetVisAttributes(new G4VisAttributes(G4Colour::Green()));

  //Изолятор С24 r=0.0 R=17.0 H=10.0 # Изолятор
  G4Tubs *solid24 = new G4Tubs("C24", 0.0 * mm, 17.0 * mm, 4.75*mm, 0, 360 * deg);
  G4LogicalVolume *logic24 = new G4LogicalVolume(solid24, mPoly, "logic24");
  new G4PVPlacement(0, G4ThreeVector(0, 0, 255.25*mm), logic24, "phys24", logic5, false, 0);
  logic24->SetVisAttributes(new G4VisAttributes(G4Colour::Brown()));
  //Детектор 1 C25 r=0.0 R=16.0 H=123.0 # Детектор 1
  G4Tubs *solid25 = new G4Tubs("C25", 0.0 * mm, 16.0 * mm, 61.5*mm, 0, 360 * deg);
  G4LogicalVolume *logic25 = new G4LogicalVolume(solid25, mDet, "logic25");
  new G4PVPlacement(0, G4ThreeVector(0, 0, 188.5*mm), logic25, "phys25", logic5, false, 0);
  logic25->SetVisAttributes(new G4VisAttributes(G4Colour::Yellow()));

  //Кадмиевый экран торец C26.1 r=0.0 R=17.0 H=0.5 # Детектор 1
  G4Tubs *solid26_1 = new G4Tubs("C26.1", 0.0 * mm, 17.0 * mm, 0.25*mm, 0, 360 * deg);
  G4LogicalVolume *logic26_1 = new G4LogicalVolume(solid26_1, mPoly, "logic26.1");
  new G4PVPlacement(0, G4ThreeVector(0, 0, 250.25*mm), logic26_1, "phys26.1", logic5, false, 0);
  logic26_1->SetVisAttributes(new G4VisAttributes(G4Colour::Red()));

  //Кадмиевый экран 1 C26 r=16.0 R=16.5 H=15.0 # Кадмиевый экран 1
  G4Tubs *solid26 = new G4Tubs("C26", 16.0 * mm, 16.5 * mm, 7.5*mm, 0, 360 * deg);
  G4LogicalVolume *logic26 = new G4LogicalVolume(solid26, mCd, "logic26");
  new G4PVPlacement(0, G4ThreeVector(0, 0, 242.5*mm), logic26, "phys26", logic5, false, 0);
  logic26->SetVisAttributes(new G4VisAttributes(G4Colour::Red()));
  //Кадмиевый экран 2 C27 r=16.0 R=16.5 H=15.0 # Кадмиевый экран 2
  G4Tubs *solid27 = new G4Tubs("C27", 16.0 * mm, 16.5 * mm, 7.5*mm, 0, 360 * deg);
  G4LogicalVolume *logic27 = new G4LogicalVolume(solid27, mCd, "logic27");
  new G4PVPlacement(0, G4ThreeVector(0, 0, 134.5*mm), logic27, "phys27", logic5, false, 0);
  logic27->SetVisAttributes(new G4VisAttributes(G4Colour::Red()));
  //Колпачок C28 r=0.0 R=17.0 H=34.0 # Колпачок
  G4Tubs *solid28 = new G4Tubs("C28", 0.0 * mm, 17.0 * mm, 17.0*mm, 0, 360 * deg);
  G4LogicalVolume *logic28 = new G4LogicalVolume(solid28, mPoly, "logic28");
  new G4PVPlacement(0, G4ThreeVector(0, 0, 110.0*mm), logic28, "phys28", logic5, false, 0);
  logic28->SetVisAttributes(new G4VisAttributes(G4Colour::Brown()));
  //Соединитель С29 r=0.0 R=17.0 H=29.0 # Соединитель
  G4Tubs *solid29 = new G4Tubs("C29", 0.0 * mm, 17.0 * mm, 14.5*mm, 0, 360 * deg);
  G4LogicalVolume *logic29 = new G4LogicalVolume(solid29, mSteel, "logic29");
  new G4PVPlacement(0, G4ThreeVector(0, 0, 78.5*mm), logic29, "phys29", logic5, false, 0);
  logic29->SetVisAttributes(new G4VisAttributes(G4Colour::Red()));
  //Колпачок С30 r=0.0 R=17.0 H=23.5 # Колпачок
  G4Tubs *solid30 = new G4Tubs("C30", 0.0 * mm, 17.0 * mm, 11.75*mm, 0, 360 * deg);
  G4LogicalVolume *logic30 = new G4LogicalVolume(solid30, mPoly, "logic30");
  new G4PVPlacement(0, G4ThreeVector(0, 0, 52.25*mm), logic30, "phys30", logic5, false, 0);
  logic30->SetVisAttributes(new G4VisAttributes(G4Colour::Brown()));
  //Детектор 2 C31 r=0.0 R=16.0 H=123.0 # Детектор 2
  G4Tubs *solid31 = new G4Tubs("C31", 0.0 * mm, 16.0 * mm, 61.5*mm, 0, 360 * deg);
  G4LogicalVolume *logic31 = new G4LogicalVolume(solid31, mDet, "logic31");
  new G4PVPlacement(0, G4ThreeVector(0, 0, -21.5*mm), logic31, "phys31", logic5, false, 0);
  logic31->SetVisAttributes(new G4VisAttributes(G4Colour::Yellow()));

  //Кадмиевый экран торец C32.1 r=0.0 R=17.0 H=0.5 # Детектор 2
  G4Tubs *solid32_1 = new G4Tubs("C32.1", 0.0 * mm, 17.0 * mm, 0.25*mm, 0, 360 * deg);
  G4LogicalVolume *logic32_1 = new G4LogicalVolume(solid32_1, mPoly, "logic32.1");
  new G4PVPlacement(0, G4ThreeVector(0, 0, 40.25*mm), logic32_1, "phys32.1", logic5, false, 0);
  logic32_1->SetVisAttributes(new G4VisAttributes(G4Colour::Red()));


  //Кадмиевый экран 1 C32 r=16.0 R=16.5 H=15.0 # Кадмиевый экран 1
  G4Tubs *solid32 = new G4Tubs("C32", 16.0 * mm, 16.5 * mm, 7.5*mm, 0, 360 * deg);
  G4LogicalVolume *logic32 = new G4LogicalVolume(solid32, mCd, "logic32");
  new G4PVPlacement(0, G4ThreeVector(0, 0, 32.5*mm), logic32, "phys32", logic5, false, 0);
  logic32->SetVisAttributes(new G4VisAttributes(G4Colour::Red()));
  //Кадмиевый экран 2 C33 r=16.0 R=16.5 H=15.0 # Кадмиевый экран 2
  G4Tubs *solid33 = new G4Tubs("C33", 16.0 * mm, 16.5 * mm, 7.5*mm, 0, 360 * deg);
  G4LogicalVolume *logic33 = new G4LogicalVolume(solid33, mCd, "logic33");
  new G4PVPlacement(0, G4ThreeVector(0, 0, -75.5*mm), logic33, "phys33", logic5, false, 0);
  logic33->SetVisAttributes(new G4VisAttributes(G4Colour::Red()));
  //Колпачок C34 r=0.0 R=17.0 H=32.0 # Колпачок
  G4Tubs *solid34 = new G4Tubs("C34", 0.0 * mm, 17.0 * mm, 16.0*mm, 0, 360 * deg);
  G4LogicalVolume *logic34 = new G4LogicalVolume(solid34, mPoly, "logic34");
  new G4PVPlacement(0, G4ThreeVector(0, 0, -99.0*mm), logic34, "phys34", logic5, false, 0);
  logic34->SetVisAttributes(new G4VisAttributes(G4Colour::Brown()));
  //Амортизатор C35 r=8.5 R=16.5 H=7.0 # Амортизатор
  G4Tubs *solid35 = new G4Tubs("C35", 8.5 * mm, 16.5 * mm, 3.5*mm, 0, 360 * deg);
  G4LogicalVolume *logic35 = new G4LogicalVolume(solid35, mRubber, "logic35");
  new G4PVPlacement(0, G4ThreeVector(0, 0, -118.5*mm), logic35, "phys35", logic5, false, 0);
  logic35->SetVisAttributes(new G4VisAttributes(G4Colour::Green()));
  //Гайка C36 r=0.0 R=19.0 H=125.0 # Гайка
  G4Tubs *solid36 = new G4Tubs("C36", 0.0 * mm, 19.0 * mm, 62.5*mm, 0, 360 * deg);
  G4LogicalVolume *logic36 = new G4LogicalVolume(solid36, mSteel, "logic36");
  new G4PVPlacement(0, G4ThreeVector(0, 0, -184.5*mm), logic36, "phys36", logic5, false, 0);
  logic36->SetVisAttributes(new G4VisAttributes(G4Colour::Red()));
  //Заглушка C37 r=0.0 R=19.0 H=125.0 # Заглушка
  G4Tubs *solid37 = new G4Tubs("C37", 0.0 * mm, 19.0 * mm, 62.5*mm, 0, 360 * deg);
  G4LogicalVolume *logic37 = new G4LogicalVolume(solid37, mSteel, "logic37");
  new G4PVPlacement(0, G4ThreeVector(0, 0, -309.5*mm), logic37, "phys37", logic5, false, 0);
  logic37->SetVisAttributes(new G4VisAttributes(G4Colour::Red()));
 
  He3_SD *detector = new He3_SD("Detector");
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  SDman->AddNewDetector(detector);
  logic25->SetSensitiveDetector(detector);
  logic31->SetSensitiveDetector(detector);

  return pWorld;
}
