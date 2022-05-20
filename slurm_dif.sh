#!/bin/bash                                                                                                                                                                                                                            

#SBATCH -J QPIX_Marley      # A single job name for the array                                                                                                                                                                          
#SBATCH -n 1                # Number of cores                                                                                                                                                                                          
#SBATCH -N 1                # All cores on one machine                                                                                                                                                                                 
#SBATCH -p guenette         # Partition                                                                                                                                                                                                
#SBATCH --mem 1000          # Memory request (Mb)                                                                                                                                                                                      
#SBATCH -t 0-8:00           # Maximum execution time (D-HH:MM)
#SBATCH -o %A_%a.out        # Standard output                                                                                                                                                                                          
#SBATCH -e %A_%a.err        # Standard error                                                                                                                                                                                           


## Job options                                                                                                                                                                                                                         
JOBNUMBER=${SLURM_ARRAY_TASK_ID}
GEANT4Path=
SEED=`echo "scale = 2;  $JOBNUMBER" | bc`

## Path to output files and G4Executable
outputDir="/home/ilker/Projects/QPIX/Diffusion"
PathToG4Executable="/home/ilker/Projects/QPIX/Diffusion/Build/app/G4_QPIX "

## Events
NumberOfEvents=2
# particle type
# e-, e+, mu-, mu+, neutron, proton, anti_proton, pi-, pi+, pi0, kaon-, kaon+,
# gamma, opticalphoton, ...
Particle=alpha
ParticleEnergy=5.4


## Pressure in bar,and Driftz in cm
Pressure=1
Driftz=2

### RTDCode
RTDCodeOn="true"
PixelStepX=1
PixelStepY=0.5

## EField V/cm ,DL in cm^2/s, DT in cm^2/s,and Drift Vel in cm/s
EField=100
DL=868.908
DT=6248.992
DriftVel=240400


## Naming Macro and Root Files
NAME="${Particle}_${SEED}"
OUT="${NAME}_${Pressure}_bar_${EField}_Vcm-1.root"
InitMACRO="${NAME}_${Pressure}_bar_${EField}_Vcm-1_init.mac"
configMACRO="${NAME}_${Pressure}_bar_${EField}_Vcm-1_config.mac"


## Paths to the Filles

RootFile="${outputDir}/output/${OUT}"

## InitMacro

## making the macro
init_MACRO="${outputDir}/macros/${InitMACRO}"

## making the macro
config_MACRO="${outputDir}/macros/${configMACRO}"

echo $init_MACRO
#Geometry
echo "/QPIX/RegisterGeometry DiffusionGeometry"  >>${init_MACRO}

#Generator
echo "/QPIX/RegisterGenerator UTA_TPC_ParticleGenerator"  >>${init_MACRO}

#Actions
echo "/QPIX/RegisterTrackingAction TrackingAction"  >>${init_MACRO}
echo "/QPIX/RegisterEventAction EventAction"  >>${init_MACRO}
echo "/QPIX/RegisterRunAction RunAction"  >>${init_MACRO}
echo "/QPIX/RegisterSteppingAction SteppingAction"  >>${init_MACRO}
echo "/QPIX/RegisterMacro ${config_MACRO}"  >>${init_MACRO}

rm config_MACRO
echo $config_MACRO

## Configurations
echo "/control/verbose 1"  >>${config_MACRO}
echo  "/run/verbose 1"     >>${config_MACRO}
echo  "/tracking/verbose 0" >>${config_MACRO}
echo "/QPIX/Action/RunAction/root_output ${RootFile}" >>${config_MACRO}

#GEOMETRY
echo "/Geometry/DiffusionGeometry/world_size 1 m"  >>${config_MACRO}
echo "/Geometry/DiffusionGeometry/MaterialName GasAr"  >>${config_MACRO}
echo "/Geometry/DiffusionGeometry/Pressure ${Pressure} bar"  >>${config_MACRO}
echo "/Geometry/DiffusionGeometry/Temperature 300 kelvin"  >>${config_MACRO}

## Detector Dimensions
echo "/Geometry/DiffusionGeometry/Det_rmin 0 cm"  >>${config_MACRO}
echo "/Geometry/DiffusionGeometry/Det_rmax 40 cm"  >>${config_MACRO}
echo "/Geometry/DiffusionGeometry/Det_z 12 cm"  >>${config_MACRO}

### Detector Active Area
echo "/Geometry/DiffusionGeometry/DetAct_rmin 0 cm"  >>${config_MACRO}
echo "/Geometry/DiffusionGeometry/DetAct_rmax 3 cm"  >>${config_MACRO}
echo "/Geometry/DiffusionGeometry/DetAct_z 5.5 cm"  >>${config_MACRO}

### Source Holder Dimensions
echo "/Geometry/DiffusionGeometry/HideSourceHolder true"  >>${config_MACRO}
echo "/Geometry/DiffusionGeometry/SourceHolder_rmin 0 cm"  >>${config_MACRO}
echo "/Geometry/DiffusionGeometry/SourceHolder_rmax 0.5 cm"  >>${config_MACRO}
echo "/Geometry/DiffusionGeometry/SourceHolder_z 0.2 cm"  >>${config_MACRO}

#### Position of the Source
echo "/Geometry/DiffusionGeometry/vtx 4 4 5.5 cm"  >>${config_MACRO}

### Offset for active region
echo "/Geometry/DiffusionGeometry/offset 4 4 5.5 cm"  >>${config_MACRO}


# limit radioactive decay chains
# use if needed
#/grdm/nucleusLimits 1 35 1 17  # aMin aMax zMin zMax
echo "/random/setSeeds 0 31"  >>${config_MACRO}



### Generator Related Settings
echo "/gps/particle ${Particle}"  >>${config_MACRO}
echo "/gps/direction -1 0 0"  >>${config_MACRO}

# energy distribution
#/gps/ene/mono 0.546 MeV ## Sr90
echo "/gps/ene/mono ${ParticleEnergy} MeV "  >>${config_MACRO}


# Circular Source
echo "/gps/pos/type Plane"  >>${config_MACRO}
echo "/gps/pos/shape Circle"  >>${config_MACRO}
echo "/gps/pos/centre 7 4 ${Driftz} cm"  >>${config_MACRO}
echo "/gps/pos/radius 0.04 cm"  >>${config_MACRO}



# Run RTD_Code for Diffusion and Current Profiles
echo "/Actions/EventAction/runRTDCode ${RTDCodeOn}"  >>${config_MACRO}


### Variables for Diffusion and Current in the GAS 50 V/cm
echo "/Actions/RTDManager/Wvalue 26.4 # eV"  >>${config_MACRO}
echo "/Actions/RTDManager/E_vel ${DriftVel} # cm/s"  >>${config_MACRO}
echo "/Actions/RTDManager/DiffusionL ${DL} #cm^2/s"  >>${config_MACRO}
echo "/Actions/RTDManager/DiffusionT ${DT} #cm^2/s"  >>${config_MACRO}
echo "/Actions/RTDManager/Life_Time 0.1"  >>${config_MACRO}
echo "/Actions/RTDManager/Reset 6250"  >>${config_MACRO}
echo "/Actions/RTDManager/SampleTime 10e-9"  >>${config_MACRO}
echo "/Actions/RTDManager/BufferTime 100e-6"  >>${config_MACRO}
echo "/Actions/RTDManager/SensorPos 2 2 7.5 cm"  >>${config_MACRO}
echo "/Actions/RTDManager/NumOfSensors 1"  >>${config_MACRO}
echo "/Actions/RTDManager/SensorSpacing 0.1 cm"  >>${config_MACRO}
echo "/Actions/RTDManager/SensorWidth 0.1 cm"  >>${config_MACRO}
echo "/Actions/RTDManager/PixelStepX ${PixelStepX} cm"  >>${config_MACRO}
echo "/Actions/RTDManager/PixelStepY ${PixelStepY} cm"  >>${config_MACRO}

${PathToG4Executable} -n ${NumberOfEvents} ${init_MACRO}

#mv "${OUTFILE}" "${OUTPUTDIR}/"
