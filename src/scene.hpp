#pragma once
#include <srl.hpp>
#include "modelObject.hpp"
#include "loader.hpp"
#include "assets.hpp"
#include "overlays.hpp"



class BaseScene
{
    public :
        virtual void draw(uint32_t elapsed_ms)
        {
            if(fistFrame)
            {
                //one time events here
                fistFrame = false;
                //set start time for the scene
                starts_at = elapsed_ms;
            }
        }
       
        Assets * assets = nullptr;
        uint32_t starts_at = 0; // used to calculate the local scene time by substracting it from the global elapsed time
        bool fistFrame = true; // used to trigger one-time events at the start of the scene

        BaseScene(Assets * s, uint32_t starts_at = 0)
        {
            this->assets = s;
            this->starts_at = starts_at;
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
                int x = (i * 25) - 1400 + y_offset; //position each line with spacing and apply vertical offset, starting from the bottom of the screen
               // assets->fonts.PrintString(greets[i], Fxp::Convert(x) , 0 , 10, 0.2, -45, 4);
                
                if(x > -240 && x < 160) //only print lines that are within the screen
                {
                     assets->fonts.PrintString(greets[i], Fxp::Convert(x) , 100 , 0.0, 0.7, -45, 4);
                }
            
            }
    

        }
};
