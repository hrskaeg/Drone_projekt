#include "acoustics_simulator.h"
#include <iostream>
using namespace std;



int main() {
 

    AcousticsSimulator simulator;
    simulator.addMicrophone("mic1", Vector3D(0, 0, 0));
    simulator.addMicrophone("mic2", Vector3D(1, 0, 0));
    simulator.addMicrophone("mic3", Vector3D(0, 1, 0));
    simulator.addMicrophone("mic4", Vector3D(0, 0, 1));
    simulator.addMicrophone("mic5", Vector3D(1, 1, 1));
    simulator.addSoundEvent("event1", Vector3D(7, 3, 1), 1.0, TRANSIENT);

    for (const auto& mic : simulator.getMicrophones()) {
        mic->updateRecordedData(simulator.generateTimeblock(*mic, *simulator.getSoundEvent()));
        }
    }