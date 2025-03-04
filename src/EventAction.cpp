// -----------------------------------------------------------------------------
//  G4_QPIX | EventAction.cpp
//
//
//   * Author: Everybody is an author!
//   * Creation date: 15 Aug 2019
// -----------------------------------------------------------------------------

#include "EventAction.h"
#include "FactoryBase.h"
#include <G4GenericMessenger.hh>

// Q-Pix includes
#include "AnalysisManager.h"
#include "MCTruthManager.h"
#include "RTDCodeManager.h"

// GEANT4 includes
#include "G4Event.hh"

REGISTER_CLASS(EventAction,G4UserEventAction)
EventAction::EventAction(): G4UserEventAction(),runRTDCode_(false)
{
    msg_ = new G4GenericMessenger(this, "/Actions/EventAction/");
    msg_->DeclareProperty("runRTDCode",runRTDCode_ ,  "This is running RTD code to simulate diffusion");


}


EventAction::~EventAction()
{
    delete msg_;
}


void EventAction::BeginOfEventAction(const G4Event*)
{}


void EventAction::EndOfEventAction(const G4Event* event)
{
    // get MC truth manager
    MCTruthManager * mc_truth_manager = MCTruthManager::Instance();

    RTDCodeManager * rtd=RTDCodeManager::Instance();

    // get analysis manager
    AnalysisManager * analysis_manager = AnalysisManager::Instance();

    // set event number
    analysis_manager->SetEvent(event->GetEventID());

    // add initial generator particles to analysis manager
    for (auto const& particle : mc_truth_manager->GetInitialGeneratorParticles())
    {
        analysis_manager->AddInitialGeneratorParticle(particle);
    }

    // add final generator particles to analysis manager
    for (auto const& particle : mc_truth_manager->GetFinalGeneratorParticles())
    {
        analysis_manager->AddFinalGeneratorParticle(particle);
    }

    // get map of particles from MC truth manager
    auto const MCParticleMap = mc_truth_manager->GetMCParticleMap();

    // add particle to analysis manager
    for (auto const& p : MCParticleMap)
    {
        auto const& particle = p.second;
        // if (particle->PDGCode() != 0)
        // {
        //     analysis_manager->AddMCParticle(particle);
        //     G4cout << "particle" <<"\t"<< particle->PDGCode() <<  G4endl;
        // }
        analysis_manager->AddMCParticle(particle);
        // G4cout << "particle" <<"\t"<< particle->PDGCode() <<  G4endl;
        // G4cout << "particle" <<"\t"<< particle->Hits().size() <<  G4endl;
        
        // auto const& hmmm = p.first;
        // G4cout << "hmmm" <<"\t"<< hmmm <<  G4endl;
    }


    //RTD Code here
    if(runRTDCode_){
        std::cout<<"Running RTD Code for Event: "<< event->GetEventID()<<std::endl;
        rtd->Diffuser();
    }

    // write event to ROOT file and reset event variables
    analysis_manager->EventFill();
    analysis_manager->EventReset();

    // reset event in MC truth manager
    mc_truth_manager->EventReset();
}

