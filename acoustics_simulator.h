#include <vector>
#include <string>
#include <memory>

using namespace std;


#define DEFAULT_SPEED_OF_SOUND 343.0 // in meters per second
#define SAMPLE_RATE 50000 // in Hz
#define TIME_BLOCK 0.1 // in seconds  

double timeBlockSamples = SAMPLE_RATE * TIME_BLOCK;

enum sound_event_type {
    TRANSIENT,
    CONTINUOUS
};

struct Vector3D {
    double x, y, z;
    
    Vector3D() : x(0), y(0), z(0) {}
    Vector3D(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}
    
    // Vector operations
    Vector3D operator+(const Vector3D& other) const {
        return Vector3D(x + other.x, y + other.y, z + other.z);
    }
    
    Vector3D operator-(const Vector3D& other) const {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }
    
    Vector3D operator*(double scalar) const {
        return Vector3D(x * scalar, y * scalar, z * scalar);
    }
    
    double dot(const Vector3D& other) const {
        return x * other.x + y * other.y + z * other.z;
    }
    
    double magnitude() const {
        return std::sqrt(x*x + y*y + z*z);
    }
    
    Vector3D normalized() const {
        double mag = magnitude();
        if (mag < 1e-10) return Vector3D(0, 0, 0);
        return Vector3D(x/mag, y/mag, z/mag);
    }
};


class source_sound_event {
    public:
    Vector3D position;
    double transient_amplitude;
    sound_event_type event_type;
    string id;
    source_sound_event(double amplitude = 1.0){
        transient_amplitude = amplitude;
        }
};

class Microphone {
    public:
    Vector3D position;
    string id;
    vector<double> recorded_data;
    void updateRecordedData(const vector<double>& new_data){
        recorded_data = new_data;
    }
};



class AcousticsSimulator {
    private:
    double speed_of_sound;
    double time_block_duration;
    vector<std::shared_ptr<Microphone>> microphones;
    std::shared_ptr<source_sound_event> sound_event;
    double calculateDistance(Microphone& mic) const;
    
    public:
    AcousticsSimulator(double speed_of_sound = DEFAULT_SPEED_OF_SOUND, sound_event_type event_type = TRANSIENT, double time_block_duration = TIME_BLOCK)
        : speed_of_sound(speed_of_sound), time_block_duration(time_block_duration){};

    //setup methods
    void addMicrophone(const string& id, const Vector3D& position);
    void addSoundEvent(const string& id, const Vector3D& position, double amplitude, sound_event_type event_type);

    //simulation methods
    double delayCalculator(Microphone& mic, source_sound_event& event); //Returns delay in seconds for sound to reach microphone.
    vector<double> generateTimeblock(Microphone& mic, source_sound_event& event); //Generates the simulated audio data for a given microphone.

    //getters
    vector<std::shared_ptr<Microphone>> getMicrophones(){
        return microphones;
    };
    std::shared_ptr<source_sound_event> getSoundEvent(){
        return sound_event;
    }

};
