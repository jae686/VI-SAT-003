
#include <srl.hpp>
#include <srl_timer.hpp>
#include "modelObject.hpp"
#include "loader.hpp"
#include <array>
#include "scene.hpp"
#include "fsm.hpp"
#include "assets.hpp"

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
    SRL::Core::Initialize(HighColor(0x00, 0x00, 0x00));
    SRL::Scene3D::SetDepthDisplayLevel(8);
 
    fsm fsm;

    Assets assets;
   // assets.loadAssets();

    Scene01 scene01_s = Scene01(&assets);

    // Frame counter
    Fxp elapsedTime = 0;
    SRL::Sound::Cdda::Analysis::Start();
    SRL::Sound::Cdda::SetVolume(4);
    SRL::Sound::Cdda::PlaySingle(2,true);

    fsm::states state = fsm::states::scene01;

    while (1)
    {     
        state = fsm.getCurrentState(elapsedTime);
        SRL::Debug::Print(1, 3, "Elapsed Time %f", elapsedTime);
        switch(state)
        {
            case fsm::states::scene01 : 
                scene01_s.draw(elapsedTime);
                //SRL::Debug::Print(1, 3, "Scene 1");
            break;
           
            default : 
                SRL::Sound::Cdda::StopPause(); 
                SRL::Debug::PrintClearScreen();
             
                SRL::Debug::Print(2, 3, "END");
        }
        SRL::Core::Synchronize(); // Swap buffers and wait for VBlank
        elapsedTime = elapsedTime + SRL::Timer::DeltaMilliseconds();
    }

    return 0;
}
