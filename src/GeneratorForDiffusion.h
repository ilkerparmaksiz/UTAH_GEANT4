//
// Created by ilker on 1/5/22.
//

#ifndef G4QPIX_GENERATORFORDIFFUSION_H
#define G4QPIX_GENERATORFORDIFFUSION_H

// GEANT4 includes
#include "G4VUserPrimaryGeneratorAction.hh"

#include "G4Box.hh"
#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4String.hh"


class G4ParticleDefinition;
class G4GenericMessenger;

class GeneratorForDiffusion : public G4VUserPrimaryGeneratorAction{
public:
    GeneratorForDiffusion();
    virtual ~GeneratorForDiffusion();
    virtual void GeneratePrimaries(G4Event*);
    //virtual void GENIEGeneratePrimaries(G4Event*);

    // This method is invoked at the beginning of the event,
    // setting a primary vertex that contains the chosen ion
    void GeneratePrimaryVertex(G4Event*);
    void EventsWithWindow(G4Event *,G4double decay_time);

protected:

    // GEANT4 dictionary of particles
    G4ParticleTable* particle_table_;

private:
    G4ParticleDefinition* IonDefinition();
    G4GenericMessenger* msg_; // Messenger for configuration parameters
    G4int atomic_number_,atomic_mass_;
    G4double energy_level_;
    G4bool decay_at_time_zero_;
    G4double Event_window_;
    G4int N_Decays_per_s_;
    G4String region_;
    G4int NDecays;
    G4String Particle_Type_;
    G4String Detector_Geometry_;
    G4double decay_time_;

    G4GeneralParticleSource * particle_gun_;

    double detector_length_x_;
    double detector_length_y_;
    double detector_length_z_;
    G4Box* detector_solid_vol_;
};

#endif //G4QPIX_GENERATORFORDIFFUSION_H
