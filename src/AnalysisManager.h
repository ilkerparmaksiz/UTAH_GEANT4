// -----------------------------------------------------------------------------
//  AnalysisManager.h
//
//  Class definition of the analysis manager
//   * Author: Everybody is an author!
//   * Creation date: 4 August 2020
// -----------------------------------------------------------------------------

#ifndef AnalysisManager_h
#define AnalysisManager_h 1

// Q-Pix includes
#include "GeneratorParticle.h"
#include "MCParticle.h"

// GEANT4 includes
#include "globals.hh"

// ROOT includes
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"

// C++ includes
#include <map>
#include <set>

class AnalysisManager {

    public:

        AnalysisManager();
        ~AnalysisManager();

        void Book(std::string const);
        void Save();
        void EventFill();
        void EventReset();

        void SetRun(int const);
        void SetEvent(int const);

        void FillMetadata(double const & detector_length_x,double const & detector_length_y,double const & detector_length_z,double const & Efield,double const & DriftV,double const & DL,double const & DT,double const & DriftDistance,double const & Pressure,double const & PixelXStep,double const & PixelYStep);

        void AddInitialGeneratorParticle(GeneratorParticle const *);
        void AddFinalGeneratorParticle(GeneratorParticle const *);

        void AddMCParticle(MCParticle const *);
        void AddInstCurrenttoFile(std::vector<double>);
        void AddCumCurrenttoFile(std::vector<double>);
        int ProcessToKey(std::string const &);
        void AddElectronLocation(std::vector<double> x,std::vector<double> y,std::vector<double> z,std::vector<double>t);
        void SavePixels(std::vector<double> pixid,std::vector<double> pixx,std::vector<double>pixy ,std::vector<double> pixq,int pixn,std::vector<double> time);




        inline void AddProcess(std::string const & process) { process_names_.insert(process); }
        inline std::set< std::string > GetProcessNames() const { return process_names_; }
        const std::vector<double> Get_hit_start_x  () {return hit_start_x_;}
        const std::vector<double> Get_hit_start_y  () {return hit_start_y_;}
        const std::vector<double> Get_hit_start_z  () {return hit_start_z_;}
        const std::vector<double> Get_hit_start_t  () {return hit_start_t_;}

        const std::vector<double> Get_hit_end_x  () {return hit_end_x_;}
        const std::vector<double> Get_hit_end_y  () {return hit_end_y_;}
        const std::vector<double> Get_hit_end_z  () {return hit_end_z_;}
        const std::vector<double> Get_hit_end_t  () {return hit_end_t_;}
        const std::vector<double> Get_Energy     () {return hit_energy_deposit_;}

        static AnalysisManager* Instance();




private:

        static AnalysisManager * instance_;

        std::set< std::string > process_names_;

        // ROOT objects
        TFile * tfile_;
        TTree * metadata_;
        TTree * event_tree_;

        // variables that will go into the metadata tree
        double detector_length_x_;
        double detector_length_y_;
        double detector_length_z_;

        double EField_;
        double DiffusionT_;
        double DiffusionL_;
        double DriftVelocity_;
        double DriftDistance_;
        double Pressure_;
        double PixelXStep_;
        double PixelYStep_;


        // variables that will go into the event trees
        int run_;
        int event_;

        int number_particles_;
        int number_hits_;

        double energy_deposit_;

        std::vector< int >    particle_track_id_;
        std::vector< int >    particle_parent_track_id_;
        std::vector< int >    particle_pdg_code_;
        std::vector< double > particle_mass_;
        std::vector< double > particle_charge_;
        std::vector< int >    particle_process_key_;
        std::vector< int >    particle_total_occupancy_;

        std::vector< double > particle_initial_x_;
        std::vector< double > particle_initial_y_;
        std::vector< double > particle_initial_z_;
        std::vector< double > particle_initial_t_;

        std::vector< double > particle_initial_px_;
        std::vector< double > particle_initial_py_;
        std::vector< double > particle_initial_pz_;
        std::vector< double > particle_initial_energy_;

        std::vector< int >    hit_track_id_;
        std::vector< double > hit_start_x_;
        std::vector< double > hit_start_y_;
        std::vector< double > hit_start_z_;
        std::vector< double > hit_start_t_;
        std::vector< double > hit_end_x_;
        std::vector< double > hit_end_y_;
        std::vector< double > hit_end_z_;
        std::vector< double > hit_end_t_;
        std::vector< double > hit_length_;
        std::vector< double > hit_energy_deposit_;
        std::vector< int >    hit_process_key_;


        std::vector< double > phit_start_x_;
        std::vector< double > phit_start_y_;
        std::vector< double > phit_start_z_;
        std::vector< double > phit_start_t_;
        std::vector< double > phit_end_x_;
        std::vector< double > phit_end_y_;
        std::vector< double > phit_end_z_;
        std::vector< double > phit_end_t_;

        // number of generator particles
        int generator_initial_number_particles_;
        int generator_final_number_particles_;

        // vectors for initial generator particles
        std::vector< double > generator_initial_particle_x_;
        std::vector< double > generator_initial_particle_y_;
        std::vector< double > generator_initial_particle_z_;
        std::vector< double > generator_initial_particle_t_;
        std::vector< double > generator_initial_particle_px_;
        std::vector< double > generator_initial_particle_py_;
        std::vector< double > generator_initial_particle_pz_;
        std::vector< double > generator_initial_particle_energy_;
        std::vector< int >    generator_initial_particle_pdg_code_;
        std::vector< double > generator_initial_particle_mass_;
        std::vector< double > generator_initial_particle_charge_;

        // vectors for final generator particles
        std::vector< double > generator_final_particle_x_;
        std::vector< double > generator_final_particle_y_;
        std::vector< double > generator_final_particle_z_;
        std::vector< double > generator_final_particle_t_;
        std::vector< double > generator_final_particle_px_;
        std::vector< double > generator_final_particle_py_;
        std::vector< double > generator_final_particle_pz_;
        std::vector< double > generator_final_particle_energy_;
        std::vector< int >    generator_final_particle_pdg_code_;
        std::vector< double > generator_final_particle_mass_;
        std::vector< double > generator_final_particle_charge_;
        std::vector< std::vector<double> > InstCurrent;
        std::vector< std::vector<double> > CumCurrent;
        std::vector<double> ElocX;
        std::vector<double> ElocY;
        std::vector<double> ElocZ;
        std::vector<double> ElocT;
        int NumberOfPixels;
        std::vector<double> PixelID;
        std::vector<double> PixelX;
        std::vector<double> PixelY;
        std::vector<double> PixelQ;
        std::vector<double> PixelTime;


};

#endif
