//
// Created by ilker on 1/13/22.
//

#ifndef G4QPIX_RTDCODEMANAGER_H
#define G4QPIX_RTDCODEMANAGER_H
#include "Randomize.hh"
#include "G4Exception.hh"
#include <G4GenericMessenger.hh>
#include "G4String.hh"
#include <vector>
#include <map>
#include <G4ThreeVector.hh>
#include <CLHEP/Units/SystemOfUnits.h>
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
    struct SENSORS
    {
        int Sensor_ID;
        double innerRad;
        double OutterRad;
        CLHEP::Hep3Vector Pos;
        std::vector<double> CumulativeCur;
        std::vector<double> InstantenousCur;
    };
    struct Pixels{
        G4long PixelID;
        double PixelX,PixelY,Q,time;
    };
    struct ELECTRON
    {
        int    Pix_ID;
        double   time;
    };

    void PrintSensorInfo(std::map<int,SENSORS*> sr);

    std::map<int,SENSORS*>CreateTheSensors(int NumOf,double spacing , double width,CLHEP::Hep3Vector Pos);
    int GetTheSensorID(double electronX,double electronY,std::map<int,SENSORS*> sensors);
    static bool Electron_Pix_Sort(ELECTRON one, ELECTRON two){ return (one.Pix_ID < two.Pix_ID);};
     static RTDCodeManager * Instance();

     const G4double getDriftVelocity(){return E_vel;}
     const G4double getDL(){return DiffusionL;}
     const G4double getDT(){return DiffusionT;}
     const G4double getPixelStepX(){return PixelStepX;}
     const G4double getPixelStepY(){return PixelStepY;}
     const G4double getEfield(){return Efield_;}
    const G4double getDriftDistance(){return DriftDistance_;}



private:
    static RTDCodeManager * instance;
    G4GenericMessenger * msg_;
    G4double Wvalue ;
    G4double E_vel ; // cm/s
    G4double DiffusionL   ;  //cm**2/s
    G4double DiffusionT  ; //cm**2/s
    G4double Life_Time ; // in s
    G4double Efield_;
    G4double DriftDistance_;
    bool HideSensors_;

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
    CLHEP::Hep3Vector SensorPos_;
    int NumofSensors_;
    G4double sensorspacing_;
    G4double sensorwidth_;
    G4double PixelStepX;
    G4double PixelStepY;
};


#endif //G4QPIX_RTDCODEMANAGER_H
