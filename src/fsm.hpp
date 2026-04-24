#pragma once
#include <srl.hpp>
#include <vector>
#include <algorithm>

class fsm 
{
    // FSM
    public :
        
        enum class states : int {scene01 , scene02, scene03, scene04, scene05, end};
        std::vector<fsm::states> state_lst = {  fsm::states::scene01, 
                                                fsm::states::end
                                             };

        std::vector<Fxp> sceneMsTimes = {9900 , 1200};

        std::vector<Fxp> sceneMsTimesAccum = {};
        
        states state = states::scene01; 
    
        fsm()
        {
           // SRL::Debug::Print(1, 1, "FSM Constructor");
            Fxp accum = 0;
            for(auto i : this->sceneMsTimes)
            {
                accum = accum + i;
                this->sceneMsTimesAccum.push_back(accum);
            }
        }

        enum class states getCurrentState(Fxp elapsedTime)
        {
            int index = 0;
            while(elapsedTime > sceneMsTimesAccum[index])
            {
                index++;
            }
            return state_lst[index];
        }
};