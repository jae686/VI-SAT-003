#pragma once

#include <srl.hpp>
#include "modelObject.hpp"
// Using to shorten names for Vector, HighColor, and other types
using namespace SRL::Types;
using namespace SRL::Math::Types;
using namespace SRL::Input;


class effects
{
    public:

    uint32_t cnt = 0;

    void compositeDrawing(ModelObject *inner, Vector3D inner_scale , ModelObject *outer, Vector3D outer_scale)
    {
        SRL::Scene3D::PushMatrix();
        SRL::Scene3D::Scale(inner_scale);
        inner->Draw();
        SRL::Scene3D::PopMatrix();
        SRL::Scene3D::PushMatrix();
        SRL::Scene3D::Scale(outer_scale);
        outer->Draw();
        SRL::Scene3D::PopMatrix();
    }

    void drawGridWave(ModelObject *obj, Vector3D location ,int grid_size_x, int grid_size_y, Fxp grid_spacing, Fxp waveFrequency, Fxp waveSpeed, uint32_t time)
    {
        
         // Calculate center position of the grid
        const Fxp half_grid_x = Fxp::Convert(grid_size_x) / 2;
        const Fxp half_grid_y = Fxp::Convert(grid_size_y) / 2;
         //centro para o efeito
        const Fxp center_x = half_grid_x * grid_spacing;
        const Fxp center_y = half_grid_y * grid_spacing;
        const Vector3D scene_center = Vector3D(center_x, 0, center_y);
        SRL::Scene3D::PushMatrix();
        SRL::Scene3D::LoadIdentity();
        SRL::Scene3D::Translate(location);
        //Vector3D cameraLocation = Vector3D(12.5, -12.5, 12.5);
        Vector3D cameraLocation = Vector3D(12.5, -12.5, 0.0);
         SRL::Scene3D::LookAt(cameraLocation, Vector3D(), Angle::FromDegrees(0.0));
        // ---- Render animated grid ----
            for (int i = 0; i < grid_size_x; i++)
            {
                for (int j = 0; j < grid_size_y; j++)
                {
                    SRL::Scene3D::PushMatrix();
                    // Calculate grid cell position
                    Vector2D gridPosition(Fxp::Convert(i) * grid_spacing, Fxp::Convert(j) * grid_spacing);
                   // gridPosition.X = Fxp::Convert(grid_spacing * i);
                    
                    // Calculate offset from center for wave effect
                    Vector2D positionOffset = gridPosition - Vector2D(center_x, center_y);
                    
                    // Calculate distance from center for radial wave
                    Fxp distanceFromCenter = positionOffset.Length();

                    // Calculate wave height based on distance and time
                    Fxp wavePhase = distanceFromCenter * waveFrequency;
                    Fxp timeComponent = Fxp::Convert(time) * waveSpeed;
                    Fxp WavePlusTime = wavePhase + timeComponent;
                    Fxp waveHeight = SRL::Math::Trigonometry::Sin(WavePlusTime) * 3;

                  //  SRL::Debug::Print(1,7+j+i, "WavePlusTime %f, calc %f", WavePlusTime,waveHeight);

                    // Position the cube in 3D space
                    Vector3D cubePosition(gridPosition.X, waveHeight, gridPosition.Y);
                    SRL::Scene3D::Translate(cubePosition);
                    
                    // Draw different cube based on wave height
                    const auto volume = SRL::Sound::Cdda::Analysis::GetTotalVolume();
                    const auto scale_f = Fxp::BuildRaw(volume.RightChannel << 5) / 7.0;
                    
                    if(scale_f > 0.6)
                    {
                        this->cnt++;
                    }
                   
                    Vector3D scale = Vector3D(1.0);
                    scale = Vector3D(1.0,  (scale_f * 1.0), 1.0 );

                    SRL::Scene3D::Scale(scale);
                    
                    obj->Draw();
                    
                    SRL::Scene3D::PopMatrix();
                }
            }

            SRL::Scene3D::PopMatrix();
    }


};