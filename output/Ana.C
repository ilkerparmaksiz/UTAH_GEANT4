#define Ana_cxx
#include "Ana.h"
#include <TH2.h>
#include <TH1D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <math.h>

using namespace std;
using namespace chrono;
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

   TH3D * hite=new TH3D("hite","h",100,-30,30,100,-30,30,100,-30,30);
   TH3D * hits=new TH3D("hits","h",100,-30,30,100,-30,30,100,-30,30);
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   int phCount=0;
   int eCount=0;
    //std::vector<double> dists;
    TCanvas *c1= new TCanvas("c1","t",800,800);
    map<double,double> Results;

    vector<double> dr;
    dr=arange(0,35,0.01);
    double TotalNumOfHitsOutFud=0;


    auto start=high_resolution_clock::now();
    for (Long64_t jentry=0; jentry<nentries;jentry++){
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      cout<<"Event " << jentry<<endl;


       /*double dist;
       double max_dist = 1000;
       TPolyLine3D *p1 = new TPolyLine3D(hit_end_x->size());

       for (int it=0; it<hit_end_x->size();it++){
           p1->SetPoint(it, hit_end_x->at(it), hit_end_y->at(it), hit_end_z->at(it));
           hite->Fill(hit_end_x->at(it), hit_end_y->at(it), hit_end_z->at(it));

       }

       p1->Draw("same");
       */


       double distance=0;
       double EventsOutFud=0;
       double EventsInFud=0;


       vector<double>  newHitx;
       vector<double>  newHity;

       for(int i=0;i<hit_end_x->size();i++){
           distance=Distance(hit_end_x->at(i),hit_end_y->at(i));
           if(distance<r) EventsInFud++;
           if(distance>=r){
               EventsOutFud++;
               newHitx.push_back(hit_end_x->at(i));
               newHity.push_back(hit_end_y->at(i));
           }
       }


       if(EventsOutFud>0 and EventsInFud>0){

           TotalNumOfHitsOutFud+=EventsOutFud;

           for(auto &d:dr){
               int QualifEvents=0;
               for(double i=0;i<newHitx.size();i++){
                   distance=Ana::Distance(newHitx.at(i),newHity.at(i));
                   if(distance<r+d){
                       QualifEvents+=1;
                   }
               }

               if(Results.find(d)==Results.end()){
                   Results.insert(pair<double,double>(d,QualifEvents));
               }else{
                   Results[d]+=QualifEvents;
               }
           }
       }

       //if (jentry==3) break;
      // if (Cut(ientry) < 0) continue;
   }
    int n=dr.size();

    cout<<"TotalCount -> "<<TotalNumOfHitsOutFud<<endl;
    vector<vector<double>> Values(2,vector<double>(n,0));
    int Cntr=0;
    for (auto &it:Results){
        Values.at(0).at(Cntr)=it.first;
        Values.at(1).at(Cntr)=it.second/TotalNumOfHitsOutFud;
        Cntr++;
    }
    auto stop=high_resolution_clock::now();
    auto duration=duration_cast<seconds>(stop-start);

    cout<<"Proccessing Time is " << duration.count() <<"(s)"<<endl;
    cout<<"Size ->"<<Values.at(0).at(0)<<endl;
    cout <<"Done!"<<endl;
    TGraph *gr= new TGraph(n,&Values.at(0).at(0),&Values.at(1).at(0));
    gr->SetTitle("Graph;dr(cm);NumberofEvents");
    gr->Draw("AL*");

    c1->Update();



}
