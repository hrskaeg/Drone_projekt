#include <string>
#include <vector>
#include <Eigen/Dense>
#include "acoustics_simulator.h"




struct TDOAFunctor {
    using Scalar = double;

    enum {
        InputsAtCompileTime = 3,
        ValuesAtCompileTime = Eigen::Dynamic
    };

    using InputType = Eigen::VectorXd;
    using ValueType = Eigen::VectorXd;
    using JacobianType = Eigen::MatrixXd;

    const std::vector<Vector3D>& micpos;
    const std::vector<double>& tdoa;
    double v;  // speed of sound

    TDOAFunctor(const std::vector<Vector3D>& m,
                const std::vector<double>& t,
                double soundSpeed)
        : micpos(m), tdoa(t), v(soundSpeed) {}

    int inputs() const { return 3; }                 // x, y, z
    int values() const { return int(micpos.size()) - 1; } // N-1 residuals

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

std::vector<double> calRelativeTDOA(const std::vector<int>& triggerIndexes, double triggerLevel);
int trigger_detector(const std::vector<double>& signal, double triggerLevel);
std::vector<int> findTriggerIndexes(const Microphones& mics, double triggerLevel);




