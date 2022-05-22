// -----------------------------------------------------------------------------
//  G4Basic | RunAction.h
//
//
//   * Author: Everybody is an author!
//   * Creation date: 15 Aug 2019
// -----------------------------------------------------------------------------

#include "RunAction.h"
#include "FactoryBase.h"
// Q-Pix includes
#include "AnalysisManager.h"
#include "MCTruthManager.h"
#include "RTDCodeManager.h"

// GEANT4 includes
#include "G4Box.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4Run.hh"

REGISTER_CLASS(RunAction,G4UserRunAction)
RunAction::RunAction(): G4UserRunAction()//, Detector_Geometry_("APA")
{
    msg_ = new G4GenericMessenger(this, "/QPIX/Action/RunAction/");

    msg_->DeclareProperty("root_output", root_output_path_,
                                "path to output ROOT file");
}


RunAction::~RunAction()
{
    delete msg_;
}


void RunAction::BeginOfRunAction(const G4Run* run)
{
    G4cout << "RunAction::BeginOfRunAction: Run #" << run->GetRunID() << " start." << G4endl;
    // get run number
    AnalysisManager * analysis_manager = AnalysisManager::Instance();
    analysis_manager->Book(root_output_path_);
    analysis_manager->SetRun(run->GetRunID());

    // reset event variables
    analysis_manager->EventReset();

    // get MC truth manager
    MCTruthManager * mc_truth_manager = MCTruthManager::Instance();


    // reset event in MC truth manager
    mc_truth_manager->EventReset();

}


void RunAction::EndOfRunAction(const G4Run*)
{
    // get analysis manager
    AnalysisManager * analysis_manager = AnalysisManager::Instance();

    //RTDManager
    RTDCodeManager * rtd=RTDCodeManager::Instance();

    // get detector dimensions
    G4LogicalVolume* detector_logic_vol
      = G4LogicalVolumeStore::GetInstance()->GetVolume("detector.logical");
    G4LogicalVolume* detector_active_vol= G4LogicalVolumeStore::GetInstance()->GetVolume("detectorActive.logical");

    if (detector_logic_vol)
    {

      analysis_manager->FillMetadata(1,1,1,rtd->getEfield(),rtd->getDriftVelocity(),rtd->getDL(),rtd->getDT(),rtd->getDriftDistance(),detector_active_vol->GetMaterial()->GetPressure()/CLHEP::bar,rtd->getPixelStepX(),rtd->getPixelStepY());
      // if (Detector_Geometry_ == "APA")
      // {G4Box * detector_solid_vol
      //   = dynamic_cast<G4Box*>(detector_logic_vol->GetSolid());

      //   double const detector_length_x = detector_solid_vol->GetXHalfLength() * 2. / CLHEP::cm;
      //   double const detector_length_y = detector_solid_vol->GetYHalfLength() * 2. / CLHEP::cm;
      //   double const detector_length_z = detector_solid_vol->GetZHalfLength() * 2. / CLHEP::cm;

      //   // save detector dimensions as metadata
      //   analysis_manager->FillMetadata(detector_length_x,
      //                                 detector_length_y,
      //                                 detector_length_z);
      // }
      // else
      // {
      //   analysis_manager->FillMetadata(777.,
      //                                  777.,
      //                                  777.);
      // }
    }

    // save run to ROOT file
    analysis_manager->Save();
}
