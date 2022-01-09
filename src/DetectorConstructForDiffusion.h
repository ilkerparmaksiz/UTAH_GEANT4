//
// Created by ilker on 1/4/22.
//

#ifndef G4QPIX_DETECTORCONSTRUCTFORDIFFUSION_H
#define G4QPIX_DETECTORCONSTRUCTFORDIFFUSION_H
#include "G4VUserDetectorConstruction.hh"


class G4Material;
class G4GenericMessenger;
class G4MaterialPropertiesTable;

class DetectorConstructForDiffusion: public G4VUserDetectorConstruction{
public:

    DetectorConstructForDiffusion();
    virtual ~DetectorConstructForDiffusion();


private:
     G4VPhysicalVolume * Construct();
     void ConstructSDandField();

    G4MaterialPropertiesTable * GetMyPhotOptSurf();
    G4GenericMessenger* msg_; // Messenger for configuration parameters
    G4String Name_;
    G4double Temperature_;
    G4double Pressure_;
    G4double world_size_;
    //For Detector Dimensions
    G4double  Det_rmin_;
    G4double  Det_rmax_;
    G4double  Det_z_;

    // For Active Area Dimensions in the detector
    G4double  DetAct_rmin_;
    G4double  DetAct_rmax_;
    G4double  DetAct_z_;

    // For Source Holder Dimensions in the detector
    G4double  SourceHolder_rmin_;
    G4double  SourceHolder_rmax_;
    G4double  SourceHolder_z_;

    G4double phi_min  = 0.0;
    G4double phi_max  = 2*M_PI;




#endif //G4QPIX_DETECTORCONSTRUCTFORDIFFUSION_H