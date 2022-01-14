//
// Created by ilker on 1/11/22.
//

#ifndef G4QPIX_QPIX_RTD_H
#define G4QPIX_QPIX_RTD_H
#include "G4UnitsTable.hh"
#include "MCParticle.h"


// setup the default Qpix paramaters
class QPIX_RTD {

public:
    QPIX_RTD();
    ~QPIX_RTD();

    struct ELECTRON
    {
        int    Pix_ID;
        double   time;
    };

    void Diffuser();
    void MakeCurrent(int SensorID);
    static bool Electron_Pix_Sort(ELECTRON one, ELECTRON two){ return (one.Pix_ID < two.Pix_ID);};

private:
    G4double Wvalue ;
    G4double E_vel ; // cm/s
    G4double DiffusionL   ;  //cm**2/s
    G4double DiffusionT  ; //cm**2/s
    G4double Life_Time ; // in s

    // Number of electrons for reset
    G4int Reset ;
    // time in ns

    G4double Sample_time ; // in s
    G4double Buffer_time ; // in s
    G4double Dead_time ; // in s
    std::vector<ELECTRON> hit_e;
    const G4double ElectronCharge_=1.60217662e-19;
    std::vector<double> InstantaneousCharge;
    std::vector<double> CumulativeCharge;

};


#endif //G4QPIX_QPIX_RTD_H
