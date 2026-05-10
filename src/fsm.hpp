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

        std::vector<uint32_t> sceneMsTimes = {64000 , 32000};

        std::vector<uint32_t> sceneMsTimesAccum = {};
        
        states state = states::scene01; 
    
        fsm()
        {
           // SRL::Debug::Print(1, 1, "FSM Constructor");
            uint32_t accum = 0;
            for(auto i : this->sceneMsTimes)
            {
                accum = accum + i;
                this->sceneMsTimesAccum.push_back(accum);
            }
        }

        enum class states getCurrentState(uint32_t elapsedTime)
        {
            int index = 0;
            while(elapsedTime > sceneMsTimesAccum[index])
            {
                index++;
            }
            return state_lst[index];
        }
};