#ifndef RootWriter_H
#define RootWriter_H 1

#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TFile.h"
#include <string>

class RootWriter{
  public:
    void Initialize(bool SaveTree=false);	
    void Fill();		// store an event
    void Finalize();	// write tree to a file
    static RootWriter* GetPointer(){
      if(pInstance==0) pInstance = new RootWriter();
      return pInstance;
    };

  std::string source;
  float abundance;
  std::string material;

  private:
    RootWriter(){fSaveTree = false;};	// empty constructor
    static RootWriter* pInstance;

    bool fSaveTree;

  public:

    TH1F*  h1[500];
    TH2F*  h2[100];
     
    TTree* tree;

  private:
    TFile* file;

};

#endif
