#pragma once
#include <srl.hpp>
#include "modelObject.hpp"
#include "loader.hpp"
#include "assets.hpp"
#include "overlays.hpp"



class BaseScene
{
    public :
        virtual void draw(uint32_t elapsed_ms); //
        uint16_t duration_frames = 0; //how many frames does the scene last (to be changed for time when frame time is available in SRL)
        Assets * assets = nullptr;
        
        BaseScene(Assets * s)
        {
            this->assets = s;
        }       
};


class Scene01 : public BaseScene
{
    public :
        // ---- Scene configuration ----
       

        Scene01(Assets * s) : BaseScene(s)
        {
           
        }

        void draw(uint32_t elapsed_ms)
        {          
   
            // Rotated rectangle points       
            Vector3D point = Vector3D(0.0 , 0.0, 500.0);   
        }
};


