#include "acoustics_simulator.h"
#include "source_localizer.h"
#include "microphones.h"
#include <iostream>
using namespace std;



int main() 
{
    
 
    //initialize microphone positions and sound event
    Microphones micArray;
    simulator.addMicrophone("mic0_ref", Vector3D(0, 0, 0));
    simulator.addMicrophone("mic1", Vector3D(1, 0, 0));
    simulator.addMicrophone("mic2", Vector3D(0, 1, 0));
    simulator.addMicrophone("mic3", Vector3D(0, 0, 1));
    simulator.addMicrophone("mic4", Vector3D(1, 1, 1));
    
    AcousticsSimulator simulator; 
    
    simulator.addSoundEvent("event0", Vector3D(7, 3, 1), 1.0, TRANSIENT);

    //simulate recorded data for each microphone
    for (const auto& mic : simulator.getMicrophones()) 
    {
        mic->updateRecordedData(simulator.generateTimeblock(*mic, *simulator.getSoundEvent()));
    }


    //initialize microphone array
    Microphones micArray;
    //calculate TDOAs


    



    
    
}