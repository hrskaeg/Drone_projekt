#include "acoustics_simulator.h"
#include <cmath>

double timeblockSamples = SAMPLE_RATE * TIME_BLOCK;

void AcousticsSimulator::addSoundSource(const string& id, const Vector3D& position, double amplitude, sound_event_type event_type){
    sound_event = std::make_shared<soundSource>(amplitude);
    sound_event->id = id;
    sound_event->position = position;
    sound_event->event_type = event_type;
}


double AcousticsSimulator::delayCalculator(Microphone& mic, soundSource& event){
    double dx = mic.position.x - event.position.x;
    double dy = mic.position.y - event.position.y;
    double dz = mic.position.z - event.position.z;
    double distance = sqrt(dx * dx + dy * dy + dz * dz);
    return distance / DEFAULT_SPEED_OF_SOUND;
}


vector<double> AcousticsSimulator::generateTimeblock(Microphone& mic, soundSource& event){
    vector<double> timeBlockSamples(static_cast<size_t>(SAMPLE_RATE * TIME_BLOCK), 0.0);
    double delay = AcousticsSimulator::delayCalculator(mic, event);
    int delaySamples = delay * SAMPLE_RATE;

    if(event.event_type == TRANSIENT)
    {
        if(delaySamples < timeBlockSamples.size())
        {
            timeBlockSamples[delaySamples] = event.transient_amplitude;
        }
    
        return timeBlockSamples; //midlertidlig for at compileren ikke brokker sig
    }

    if(event.event_type == CONTINUOUS)
    {
        return timeBlockSamples;
    }
}



