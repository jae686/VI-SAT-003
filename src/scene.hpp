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
            if(this->firstFrame)
            {
                //one time events here
                this->firstFrame = false;
                //set start time for the scene
                this->starts_at = elapsed_ms;
            }
            //calculate local time for the scene by subtracting the start time from the global elapsed time
            this->local_time = elapsed_ms - this->starts_at;
        }
       
        Assets * assets = nullptr;
        uint32_t starts_at = 0; // used to calculate the local scene time by substracting it from the global elapsed time
        uint32_t local_time = 0; // calculated by substracting starts_at from the global elapsed time, can be used for timing events within the scene
        bool firstFrame = true; // used to trigger one-time events at the start of the scene

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
            
             if(this->firstFrame)
            {
                //one time events here
                this->firstFrame = false;
                //set start time for the scene
                this->starts_at = elapsed_ms;
            }
            
            this->local_time = elapsed_ms - this->starts_at;

            /*
            if(assets->counters[0] == 0)
            {
                //one time events here
                assets->counters[0] = 1; // set to 1 to indicate that the one-time events have been executed
                SRL::VDP2::NBG0::SetPriority(SRL::VDP2::Priority::Layer2);//set NBG0 priority
                SRL::VDP2::NBG0::ScrollEnable();//enable display of NBG0
            }*/
             //print greets with scrolling effect
            //print greets with scrolling effect
            SRL::Debug::Print(1, 4, "Local Time: %d", this->local_time);
            Vector3D cameraLocation = Vector3D(12.5, -12.5, 12.5);
  
            // Setup light, we can use scale of the vector to manipulate light intensity
            Vector3D lightDirection = Vector3D(0.2, 0.0, 0.2);
            SRL::Scene3D::SetDirectionalLight(lightDirection);


            int scroll_speed = 30; //pixels per second
            int y_offset = (this->local_time * scroll_speed) / 1000; //calculate vertical offset based on elapsed time and scroll speed

            for(int i = 0; i < 50; i++)
            {
                int x = (i * 25) - 1400 + y_offset; //position each line with spacing and apply vertical offset, starting from the bottom of the screen
               // assets->fonts.PrintString(greets[i], Fxp::Convert(x) , 0 , 10, 0.2, -45, 4);
                
                if(x > -240 && x < 160) //only print lines that are within the screen
                {
                     assets->fonts.PrintString(greets[i], Fxp::Convert(x) , 100 , 0.0, 0.7, -45, 4);
                }
            
            }

            
            // Load identity matrix
            SRL::Scene3D::LoadIdentity();
            // Set camera location and direction
            SRL::Scene3D::LookAt(cameraLocation, Vector3D(), Angle::FromDegrees(0.0));
           
            if((this->local_time % assets->counters[1]) == 0) 
            {
                 assets->cube_w.Draw();
            }else
            {
                SRL::Scene3D::Scale(0.5, 0.5, 0.5); 
                assets->cube_w.Draw();
            }
           
            
           

        }
};
