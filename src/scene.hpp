#pragma once
#include <srl.hpp>
#include "modelObject.hpp"
#include "loader.hpp"
#include "assets.hpp"
#include "overlays.hpp"
#include "effects.hpp"


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

        BaseScene(Assets * s)
        {
            if(s == nullptr)
            {
                 SRL::Debug::AssertScreen("BaseScene error %d", "scene.hpp" ,  "Basescene()" , s);
            }
            
            this->assets = s;

        }       
};


class Scene01 : public BaseScene
{
    public :
        // ---- Scene configuration ----
       int indexDots = 0;
       int maxDots = assets->textureDots.size();

       ModelObject teste;
       effects effect;
        Scene01(Assets * s) : BaseScene(s)
        {
           //teste.LoadFile("CUBE_Z.NYA");
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
            SRL::Debug::PrintClearLine(1);
            SRL::Debug::PrintClearLine(4);
            SRL::Debug::Print(1,1, "Scene : 01");
            SRL::Debug::Print(1, 4, "Local Time: %d", this->local_time);
            */
            // camera setup
            Vector3D cameraLocation =  Vector3D(25.5, -25.5, 25.5);
            
            // Setup light, we can use scale of the vector to manipulate light intensity
            Vector3D lightDirection = Vector3D(0.2, 0.0, 0.2).Normalize();
           // SRL::Scene3D::SetDirectionalLight(lightDirection);
            const auto volume = SRL::Sound::Cdda::Analysis::GetTotalVolume();
            const auto scale_f = Fxp::BuildRaw(volume.RightChannel << 5) / 7.0;
            
            SRL::Scene3D::PushMatrix();
            SRL::Scene3D::Translate(Vector3D(4.0, 0.0, 0.0));
            SRL::Scene3D::Scale(Vector3D(2.0));
            
            SRL::Scene3D::PopMatrix();

            if(this->local_time < 7000)
            {
                if(this->local_time < 5000)
                {
                    SRL::Scene2D::DrawSprite(assets->texturePool[1], Vector3D(-160.0,-120,500),Vector3D(1.0), SRL::Scene2D::UpperLeft);
                }else
                {
                    assets->fonts.PrintString("Presents", -120, 0,1,0.75,0.0,0);
                }
                
            }else
            {
                assets->fonts.PrintString("VI-SAT 003", -60, 70 ,1,0.50,0.0,0);
                SRL::Scene2D::DrawSprite(assets->textureDots[indexDots%maxDots], Vector3D(-160.0,-120,500),Vector3D(2.0), SRL::Scene2D::UpperLeft);
                
                // Load identity matrix
                SRL::Scene3D::LoadIdentity();
                // Set camera location and direction
                SRL::Scene3D::LookAt(cameraLocation, Vector3D(), Angle::FromDegrees(0.0));
                SRL::Scene3D::PushMatrix();
                SRL::Scene3D::Scale(5* scale_f);
                //assets->cube_f.Draw();
                assets->cuberf.Draw();
                SRL::Scene3D::PopMatrix();

            }
            
            
            
            
            if(/*elapsed_ms - 114 >= assets->counters[2]*/ scale_f > 0.6 )
            {
                indexDots++;
                assets->counters[2] =  assets->counters[2] +  assets->counters[1];
            }
            
         /*
            SRL::Debug::PrintClearLine(5);
            SRL::Debug::PrintClearLine(6);
            SRL::Debug::Print(1, 5, "Free VDP1 mem %d ", SRL::VDP1::GetAvailableMemory());
            SRL::Debug::Print(1, 6, "free HighWorkRam space %d" , SRL::Memory::HighWorkRam::GetFreeSpace());
        */
            
        }
};

class Scene02 : public BaseScene
{
    public :
        // ---- Scene configuration ----
       
        effects effect;
        uint32_t internal_cnt = 0;
        Vector3D gridPosition = Vector3D(15.0, 0.0, 15.0);
        Fxp gridScrollSpeed = 0.00003;
        const char* textUPPER[9] = {"MUCH DEMO", "LITTLE TIME", "GIMME MORE COLOR", "FOR MY DEMO", "BEER", "Thanks for", "having us", "at", "outline 2026" };
        
       int indexTex = 0;
       int maxTex = assets->texturePool.size();

        Scene02(Assets * s) : BaseScene(s)
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

           
         //   SRL::Debug::PrintClearLine(1);
         //   SRL::Debug::PrintClearLine(4);
          //    SRL::Debug::Print(1,1, "Scene : 02");
          //    SRL::Debug::Print(1, 4, "Local Time: %d", this->local_time);

            const auto volume = SRL::Sound::Cdda::Analysis::GetTotalVolume();
            const auto scale_f = Fxp::BuildRaw(volume.RightChannel << 5) / 7.0;

            // camera setup
            Vector3D cameraLocation = Vector3D(12.5, -12.5, 12.5);
            // Setup light, we can use scale of the vector to manipulate light intensity
            Vector3D lightDirection = Vector3D(0.2, 0.0, 0.2);
            SRL::Scene3D::SetDirectionalLight(lightDirection);

            // Load identity matrix
            SRL::Scene3D::LoadIdentity();
            // Set camera location and direction
            SRL::Scene3D::LookAt(cameraLocation, Vector3D(), Angle::FromDegrees(0.0));
            
         //   effect.compositeDrawing(&assets->cuberf, Vector3D(2.0), &assets->cuberw, Vector3D(5.0) );
            if(this->local_time < 24000)
            {
                effect.drawGridWave(&assets->cuberf,gridPosition, 7 , 25 , Fxp(5.0) ,0.03 ,0.05, internal_cnt);
                gridPosition.X = gridPosition.X - (gridScrollSpeed * this->local_time);
            }else
            {
                SRL::Scene3D::Scale(3 * scale_f);
                assets->cuberw.Draw();

                int scroll_speed = 25; //pixels per second
                int y_offset = ((this->local_time - 24000) * scroll_speed) / 1000; //calculate vertical offset based on elapsed time and scroll speed

                //for(int i = 0; i < 9; i++)
                for(int i = 8; i >= 0 ; i--)
                {
                    int y = (i * 25) - (16*9) + y_offset; //position each line with spacing and apply vertical offset, starting from the bottom of the screen
                                    
                    if(y > -240 && y < 160) //only print lines that are within the screen
                    {
                        assets->fonts.PrintString(textUPPER[i], -120, Fxp::Convert(y) , 0.0, Fxp(0.7) + (scale_f * 0.001), 0, 0);
                    }
                
                }
            }
            
            SRL::Scene2D::DrawSprite(assets->texturePool[indexTex%maxTex], Vector3D(-160.0,-120,600),Vector3D(1.0), SRL::Scene2D::UpperLeft);
            internal_cnt++;
            
             if(/*elapsed_ms - 114 >= assets->counters[2]*/ scale_f > 0.7 )
            {
                indexTex++; 
            }
            
            //assets->fonts.PrintString(textUPPER[0], -120,     -60, 1, 0.5, 0, 0);
           // assets->fonts.PrintString(textUPPER[1], -120, -60 -16, 1, 0.5, 0, 0);

        }
};

class Scene03 : public BaseScene
{
    public :
        // ---- Scene configuration ----
       

        Scene03(Assets * s) : BaseScene(s)
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

            //print greets with scrolling effect
        //    SRL::Debug::PrintClearLine(1);
        //    SRL::Debug::PrintClearLine(4);
        //    SRL::Debug::Print(1, 1, "Scene : 03");
        //    SRL::Debug::Print(1, 4, "Local Time: %d", this->local_time);

            SRL::Scene2D::DrawSprite(assets->texturePool[2], Vector3D(-160.0,-120,500),Vector3D(1.0), SRL::Scene2D::UpperLeft);
        }
};

class SceneCredits : public BaseScene
{
    public :
        // ---- Scene configuration ----
       
        // Credits scene, with scrolling text and background animation

        //Text:

        const char* greets[52] = {
            "abaddon",
            "Glenz",
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
            "konsumer",
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
            "royal belgian",
            "beer squadron",
            "sensar studios",
            "slipstream",
            "smfx",
            "software failure",
            "spectrals",
            "spreadpoint",
            "teadrinker",
            "team210",
            "the black lotus",
            "the orb",
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
                SRL::VDP2::NBG2::SetPriority(SRL::VDP2::Priority::Layer7);//set NBG2 priority
                SRL::VDP2::NBG2::ScrollEnable();//enable display of NBG2
                Vector2D offset = Vector2D(0.0, 0.0);
                SRL::VDP2::NBG2::SetPosition(offset);
            }*/
            
            //print greets with scrolling effect
         //   SRL::Debug::PrintClearLine(1);
         //   SRL::Debug::PrintClearLine(4);
         //   SRL::Debug::Print(1,1, "Scene : Credits");
         //   SRL::Debug::Print(1, 4, "Local Time: %d", this->local_time);
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
                     assets->fonts.PrintString(greets[i], Fxp::Convert(x) , 100 , 0.0, 0.7, -45, 0);
                }
            
            }

            SRL::Scene2D::DrawSprite(assets->texturePool[0], Vector3D(0.0,0.0,500),Vector3D(1.0), SRL::Scene2D::Center);
            
            // Load identity matrix
            SRL::Scene3D::LoadIdentity();
            // Set camera location and direction
            SRL::Scene3D::LookAt(cameraLocation, Vector3D(), Angle::FromDegrees(0.0));
           
           
           // assets->cube_f.Draw();
            
           
            
           

        }
};
