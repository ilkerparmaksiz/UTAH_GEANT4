//
// Created by ilker on 1/13/22.
//

#ifndef G4QPIX_RTDCODEMANAGER_H
#define G4QPIX_RTDCODEMANAGER_H
#include "G4String.hh"
#include <vector>
class G4GenericMessenger;
class AnalysisManager;
class RTDCodeManager {
public:
    RTDCodeManager();
    ~RTDCodeManager();
    void Diffuser();
    //void Diffuser(AnalysisManager*  AnaMngr);
    void MakeCurrent(int SensorID);
    //void MakeCurrent(int SensorID,AnalysisManager* AnaMngr);
    struct ELECTRON
    {
        int    Pix_ID;
        double   time;
    };

    static bool Electron_Pix_Sort(ELECTRON one, ELECTRON two){ return (one.Pix_ID < two.Pix_ID);};
     static RTDCodeManager * Instance();

private:
    static RTDCodeManager * instance;
    G4GenericMessenger * msg_;
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
    G4double ElectronCharge_;

    std::vector<G4double> InstantaneousCharge;
    std::vector<double> CumulativeCharge;
    G4double cumulativeCharge_;
};


#endif //G4QPIX_RTDCODEMANAGER_H
