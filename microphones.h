#ifndef MICROPHONE_H
#define MICROPHONE_H

#include <string>
#include <vector>

using namespace std;

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
        return sqrt(x*x + y*y + z*z);
    }
    
    Vector3D normalized() const {
        double mag = magnitude();
        if (mag < 1e-10) return Vector3D(0, 0, 0);
        return Vector3D(x/mag, y/mag, z/mag);
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

struct Microphones {
    vector<Microphone>& mics;
    Microphones(vector<Microphone>& microphones) : mics(microphones) {}
    void addMicrophone(const string& id, const Vector3D& position);
};

#endif // MICROPHONE_H

