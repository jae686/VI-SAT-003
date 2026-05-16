
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

  
    Scene01 scene01_s = Scene01(&assets);
    Scene02 scene02_s = Scene02(&assets);
    Scene03 scene03_s = Scene03(&assets);
    SceneCredits sceneCredits_s = SceneCredits(&assets);
    // Frame counter
    uint32_t elapsedTime = 0;
    SRL::Sound::Cdda::Analysis::Start();
    SRL::Sound::Cdda::SetVolume(4);
    SRL::Sound::Cdda::PlaySingle(2,true);
    SRL::Sound::Cdda::Analysis::GetTotalVolume();

    fsm::states state = fsm::states::scene01;

    bool firstFrame = true;
    Fxp angle = 0.0;

    Fxp MusicBPM = 137.0;
    Fxp beatDuration = 60000.0 / MusicBPM; // Duration of one beat in milliseconds

    assets.counters[1] = beatDuration.As<uint32_t>(); // Store beat duration in counters[1] for use in scenes
    assets.counters[2] = assets.counters[1] + 7000; // time for next beat

  //  SRL::VDP2::SetBackColor(HighColor::Colors::Blue);
    SRL::Scene3D::SetDepthDisplayLevel(4);
    SRL::Debug::PrintClearScreen();
    while (1)
    {     
        state = fsm.getCurrentState(elapsedTime);
         
        switch(state)
        {
            
            case fsm::states::scene01 : 
                scene01_s.draw(elapsedTime);
            break;
            case fsm::states::scene02 : 
                scene02_s.draw(elapsedTime);
            break;
            case fsm::states::scene03 : 
                scene03_s.draw(elapsedTime);
            break;
            case fsm::states::end : 
                sceneCredits_s.draw(elapsedTime);
            break;
           
            default : 
                SRL::Sound::Cdda::StopPause(); 
                SRL::Debug::PrintClearScreen();
                SRL::Debug::Print(2, 3, "PARTY VERSION NOT FINAL");
                SRL::Debug::Print(2, 4, "Code Jae686//Vollumetric Illusions");
                SRL::Debug::Print(2, 5, "Sound, Gfx EviL//Accession");
                SRL::Debug::Print(2, 6, "Released at outline 2026");
                SRL::Debug::Print(2, 8, "END");
            break;
        }
        SRL::Core::Synchronize(); // Swap buffers and wait for VBlank
        Fxp delta = SRL::Timer::DeltaMilliseconds();
       // SRL::Debug::Print(1, 3, "Elapsed Time %d , Delta %f", elapsedTime, delta);
        //SRL::Debug::Print(1, 4, "60000//BPM: %d", assets.counters[1]);
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
