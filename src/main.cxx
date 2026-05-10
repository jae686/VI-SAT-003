
#include <srl.hpp>
#include <srl_timer.hpp>
#include "modelObject.hpp"
#include "loader.hpp"
#include <array>
#include "scene.hpp"
#include "fsm.hpp"
#include "assets.hpp"
#include "fonts.hpp"


// Using to shorten names for Vector, HighColor, and other types
using namespace SRL::Types;
using namespace SRL::Math::Types;
using namespace SRL::Input;

/**
 * SaturnRingLib Demo 01
 * 
 * This demo showcases:
 * - 3D camera rotation around a target
 * - Wave animation effect on a grid
 * - 3D model rendering with lighting
 */

int main()
{
    // ---- Initialize library ----
    SRL::Core::Initialize(HighColor::Colors::Blue);
    SRL::Scene3D::SetDepthDisplayLevel(8);
 
    fsm fsm;

    Assets assets;
    assets.loadAssets();

    //bitmapfont fonts; 

    Scene01 scene01_s = Scene01(&assets);
    SceneCredits sceneCredits_s = SceneCredits(&assets);
    // Frame counter
    uint32_t elapsedTime = 0;
    SRL::Sound::Cdda::Analysis::Start();
    SRL::Sound::Cdda::SetVolume(4);
    SRL::Sound::Cdda::PlaySingle(2,true);

    fsm::states state = fsm::states::scene01;

    bool firstFrame = true;
    Fxp angle = 0.0;

    while (1)
    {     
        state = fsm.getCurrentState(elapsedTime);
        SRL::Debug::Print(1, 3, "Elapsed Time %d , Angle %f", elapsedTime, angle);
        /*
        assets.fonts.PrintString("X TOSTA", -160.0 ,0.0 , 10, 0.25, -45, 4);
        assets.fonts.PrintString("X TOSTA", -100.0 ,0.0 , 10, 0.25, -45, 4);
        assets.fonts.PrintString("X TOSTA", -40.0 ,0.0 , 10, 0.25, -45, 4);
       */
       
        //assets.fonts.PrintString("X TOSTA", -320.0 ,0.0 , 10, 0.5, angle, 4);
       
       
        switch(state)
        {
            
            case fsm::states::scene01 : 
                //scene01_s.draw(elapsedTime);
                sceneCredits_s.draw(elapsedTime);
            break;
           
            default : 
                SRL::Sound::Cdda::StopPause(); 
                SRL::Debug::PrintClearScreen();
                SRL::Debug::Print(2, 3, "END");
        }
        SRL::Core::Synchronize(); // Swap buffers and wait for VBlank
        Fxp delta = SRL::Timer::DeltaMilliseconds();
        
        if(firstFrame)
        {
            firstFrame = !firstFrame;
        }
        else
        {
            uint32_t delta_u = delta.As<uint32_t>();
            elapsedTime = elapsedTime + delta_u;
            angle = angle + delta * 0.1;        
        }
        
    }

    return 0;
}
