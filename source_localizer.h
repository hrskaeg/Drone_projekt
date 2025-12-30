#include <string>
#include <vector>
#include <Eigen/Dense>
#include "acoustics_simulator.h"



struct TDOAFunctor {
    using Scalar = double;
    using InputType = Eigen::VectorXd;
    using ValueType = Eigen::VectorXd;
    using JacobianType = Eigen::MatrixXd;

    const std::vector<Microphone::position>& micpos;
    const std::vector<double>& tdoa;
    double v;  // speed of sound

    TDOAFunctor(const std::vector<Microphone::position>& m,
                const std::vector<double>& t,
                double soundSpeed)
        : micpos(m), tdoa(t), v(soundSpeed) {}

    int inputs() const { return 3; }                 // x, y, z
    int values() const { return int(mics.size()) - 1; } // N-1 residuals

    int operator()(const Eigen::VectorXd& p,
                   Eigen::VectorXd& fvec) const {

        double x = p[0];
        double y = p[1];
        double z = p[2];

        // Reference microphone (index 0)
        double d0 = std::hypot(x - micpos[0].x, y - micpos[0].y, z - micpos[0].z);

        for (size_t i = 1; i < micpos.size(); ++i) {
            double di = std::hypot(x - micpos[i].x, y - micpos[i].y, z - micpos[i].z);
            fvec[int(i - 1)] = v * tdoa[i] - (di - d0);
        }

        return 0;
    }
};


//LevenbergMarquardt 
struct vector3d 
{
    double x, y, z;
};



class Localizer 
{   
    private:

    public:

};





std::vector<Microphone::position> getMicrophonePositions(const Microphones& microphones)
{
    std::vector<Microphone::position> positions;
    for (const auto& mic : microphones.mics)
    {
        positions.push_back(mic.position);
    }
    return positions;
}

std::vector<double> calRelativeTDOA(const std::vector<int>& triggerIndexes, double triggerLevel)
{

    std::vector<double> relativeTDOA(triggerIndexes.size());
    for (int i = 0; i < triggerIndexes.size(); i++)
    {
        double relTime = (triggerIndexes[i] - triggerIndexes[0]) / SAMPLE_RATE;
        relativeTDOA[i] = relTime;
    }
    return relativeTDOA;
}

std::vector<int> findTriggerIndexes(const std::vector<std::vector<double>>& signals, double triggerLevel)
{
    std::vector<int> triggerIndexes(signals.size());
    for (const auto& signal : signals)
    {
        int index = trigger_detector(signal, triggerLevel);
        triggerIndexes.push_back(index);
    }

    return triggerIndexes;
}

int trigger_detector(const std::vector<double>& signal, double triggerLevel)
{
    for(int i = 0; i < signal.size(); ++i)
    {
        if(signal[i] >= triggerLevel){
            return i;
        }
    }
    
    return -1; // No trigger found  
}




