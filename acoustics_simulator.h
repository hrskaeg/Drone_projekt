#pragma once

#include <vector>
#include <cmath>
#include <string>
#include <memory>
#include "microphones.h"


using namespace std;


#define DEFAULT_SPEED_OF_SOUND 343.0 // in meters per second
#define SAMPLE_RATE 50000 // in Hz
#define TIME_BLOCK 0.1 // in seconds  

extern double timeBlockSamples;

enum sound_event_type {
    TRANSIENT,
    CONTINUOUS
};



class soundSource {
    public:
    Vector3D position;
    double transient_amplitude;
    sound_event_type event_type;
    string id;
    soundSource(double amplitude = 1.0)
    {
        transient_amplitude = amplitude;
    }
};




class AcousticsSimulator {
    private:
    double speed_of_sound;
    double time_block_duration;
    Microphones& micArray;
    std::shared_ptr<soundSource> sound_event;
    double calculateDistance(Microphone& mic) const;
    
    public:
    AcousticsSimulator(Microphones& micArray, double speed_of_sound = DEFAULT_SPEED_OF_SOUND, sound_event_type event_type = sound_event_type::TRANSIENT, double time_block_duration = TIME_BLOCK)
        : micArray(micArray), speed_of_sound(speed_of_sound), time_block_duration(time_block_duration){};

    //setup methods
    void addSoundSource(const string& id, const Vector3D& position, double amplitude, sound_event_type event_type);

    //simulation methods
    double delayCalculator(Microphone& mic, soundSource& event); //Returns delay in seconds for sound to reach microphone.
    vector<double> generateTimeblock(Microphone& mic, soundSource& event); //Generates the simulated audio data for a given microphone.

    //getters
    Microphones& getMicrophones(){
        return micArray;
    };
    std::shared_ptr<soundSource> getSoundEvent(){
        return sound_event;
    }

};
