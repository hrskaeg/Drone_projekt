#include "acoustics_simulator.h"
#include <cmath>


double AcousticsSimulator::delayCalculator(Microphone& mic, source_sound_event& event){
    double dx = mic.position.x - event.position.x;
    double dy = mic.position.y - event.position.y;
    double dz = mic.position.z - event.position.z;
    double distance = sqrt(dx * dx + dy * dy + dz * dz);
    return distance / DEFAULT_SPEED_OF_SOUND;
}


vector<double> AcousticsSimulator::generateTimeblock(Microphone& mic, source_sound_event& event){
    vector<double> timeBlockSamples(static_cast<size_t>(SAMPLE_RATE * TIME_BLOCK), 0.0);
    double delay = AcousticsSimulator::delayCalculator(mic, event);
    int delaySamples = delay * SAMPLE_RATE;

    if(event.event_type == TRANSIENT){
        if(delaySamples < timeBlockSamples.size()){
            timeBlockSamples[delaySamples] = event.transient_amplitude;
        }

    return timeBlockSamples;

}
}