#define Ana_cxx
#include "Ana.h"
#include <TH2.h>
#include <TH1F.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

using namespace std;
void Ana::Loop()
{
//   In a ROOT session, you can do:
//      root> .L Ana.C
//      root> Ana t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   TH1F * hite=new TH1F("h","h",10,0,100);
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   int phCount=0;
   int eCount=0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      cout<<"Event " << jentry<<endl;
      cout<<"Number Of Particles " << number_particles<<endl;
      cout<<"number_hits" << number_hits<<endl;

      for (auto i:*particle_pdg_code) {
          if(i==0){
              phCount++;
              continue;
          }else if (i==11) eCount++;
      }
      float hited=0;
      for (auto i:*hit_energy_deposit) hited+=i;

      hite->Fill(hited*1000);
      if (jentry==-1) break;
      // if (Cut(ientry) < 0) continue;
   }
   cout<<"Number of Photons "<<phCount<<endl;
    cout<<"Number of e- "<<eCount<<endl;
    hite->Draw();

}
