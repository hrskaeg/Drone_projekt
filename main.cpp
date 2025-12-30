#include "acoustics_simulator.h"
#include "source_localizer.h"
#include "microphones.h"
#include <iostream>
#include <Eigen/Dense>
#include <unsupported/Eigen/NumericalDiff>
#include <unsupported/Eigen/NonLinearOptimization>
using namespace std;



int main() 
{
    
 
    //initialize microphone positions and sound event
    Microphones micArray;
    
    micArray.addMicrophone("mic0_ref", Vector3D(1, 44, 8));
    micArray.addMicrophone("mic1", Vector3D(9, 28, 6));
    micArray.addMicrophone("mic2", Vector3D(4, 17, 30));
    micArray.addMicrophone("mic3", Vector3D(15, 10, 20));
    micArray.addMicrophone("mic4", Vector3D(0, 9, 17));
    
    AcousticsSimulator simulator(micArray);
    
    simulator.addSoundSource("event0", Vector3D(20, 4, 2), 1.0, sound_event_type::TRANSIENT);

    //simulate recorded data for each microphone
    for (auto& mic : micArray.mics) 
    {
        mic.updateRecordedData(simulator.generateTimeblock(mic, *simulator.getSoundEvent()));
    }

    

    //calculate TDOAs
    std::vector<double> relTDOA = calRelativeTDOA(findTriggerIndexes(micArray, 0.5),0.5);

    std::cout<< "Relative TDOAs:\n";
    for(const auto& tdoa : relTDOA)
    {
        std::cout << tdoa << " ";
    }
    
    std::vector<Vector3D> micPos = micArray.getMicrophonePositions(micArray); //Find ud af hvordan man kalder funktionen på objektet uden parametre.


    TDOAFunctor functor(micPos, relTDOA, DEFAULT_SPEED_OF_SOUND);

    Eigen::NumericalDiff<TDOAFunctor> numDiff(functor);
    Eigen::LevenbergMarquardt<Eigen::NumericalDiff<TDOAFunctor>> lm(numDiff);

    lm.parameters.maxfev = 500;
    lm.parameters.xtol = 1e-6;
    lm.parameters.ftol = 1e-6;

     Eigen::VectorXd p(3);
    p << 10.0, 5, 3;  // initial guess

    auto status = lm.minimize(p);

    std::cout << "\n Estimated position: ("
              << p[0] << ", " << p[1] << ", " << p[2] << ")\n";
    std::cout << "Status: " << status << std::endl;
}