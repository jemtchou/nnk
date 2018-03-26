#ifndef PARTICLE_INFO_HH
#define PARTICLE_INFO_HH

#include "G4VUserTrackInformation.hh"
#include "G4ThreeVector.hh"

class  ParticleInfo : public G4VUserTrackInformation
{
    public:
        ParticleInfo( ){Rmax=0; PositionMax=G4ThreeVector(0,0,0);};

    public:
        void Print( void ) const { G4cout << "ParticleInfo::Rmax " << Rmax << G4endl;};

	G4ThreeVector   PositionMax;
	G4double 	Rmax;
};

#endif
