#include "source_localizer.h"
#include <vector>
#include <cmath>
#include <iostream>
#include "acoustics_simulator.h"



std::vector<double> calRelativeTDOA(const std::vector<int>& triggerIndexes, double triggerLevel)
{

    std::vector<double> relativeTDOA(triggerIndexes.size());
    for (int i = 0; i < triggerIndexes.size(); i++)
    {
        double relTime = (double)(triggerIndexes[i] - triggerIndexes[0]) / (double)SAMPLE_RATE;
        relativeTDOA[i] = relTime;
    }
    return relativeTDOA;
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


std::vector<int> findTriggerIndexes(const Microphones& mics, double triggerLevel)
{

    std::vector<int> triggerIndexes;
    for (const auto& mic : mics.mics)
    {
        int index = trigger_detector(mic.getRecordedData(), triggerLevel);
        triggerIndexes.push_back(index);
    }

    return triggerIndexes;
}
