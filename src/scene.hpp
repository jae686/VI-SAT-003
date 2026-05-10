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

class SceneCredits : public BaseScene
{
    public :
        // ---- Scene configuration ----
       
        // Credits scene, with scrolling text and background animation

        //Text:

        const char* greets[50] = {
            "abaddon",
            "accession",
            "agenda",
            "alcatraz",
            "altair",
            "attention whore",
            "batman group",
            "bitshifters",
            "brain control",
            "brainlez coders!",
            "bus error collective",
            "citavia",
            "damage",
            "darklite",
            "dekadence",
            "desire",
            "disaster area",
            "epoqe",
            "excess team",
            "extend",
            "fairlight"
            "focus design",
            "gaia space agency",
            "haujobb",
            "horology",
            "ICUP", 
            "joker",
            "jumalauta",
            "logicoma",
            "loonies",
            "mad wizards",
            "marquee design",
            "matt current",
            "mercury",
            "mfx",
            "napalm core",
            "poo-brain",
            "rebels",
            "rift",
            "royal belgian beer squadron",
            "sensar studios",
            "slipstream",
            "smfx",
            "software failure",
            "spectrals",
            "spreadpoint",
            "teadrinker",
            "team210",
            "the black lotus",
            "the orz",
            "tpolm"
        };
        

        SceneCredits(Assets * s) : BaseScene(s)
        {
           
        }

        void draw(uint32_t elapsed_ms)
        {          
           //print greets with scrolling effect
            int scroll_speed = 30; //pixels per second
            int y_offset = (elapsed_ms * scroll_speed) / 1000; //calculate vertical offset based on elapsed time and scroll speed

            for(int i = 0; i < 50; i++)
            {
                int x = (i * 35) - 160; //position each line with spacing and apply vertical offset, starting from the bottom of the screen
               // assets->fonts.PrintString(greets[i], Fxp::Convert(x) , 0 , 10, 0.2, -45, 4);
                
                if(x > -160 && x < 160) //only print lines that are within the screen
                {
                     assets->fonts.PrintString(greets[i], Fxp::Convert(x) , 0 , 10, 0.2, -45, 4);
                }
            
            }
    

        }
};
