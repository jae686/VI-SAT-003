#pragma once


#include <srl.hpp>

// Using to shorten names for Vector, HighColor, and other types
using namespace SRL::Types;
using namespace SRL::Math::Types;
using namespace SRL::Input;

class Loader
{
  
    private :
        uint8_t curr_cnt = 0; //
        uint8_t target_cnt = 0;
        uint8_t total_cnt = 0;

        Fxp start_width = 0.0;
        Fxp curr_width = 0.0;
        Fxp target_width = 0.0;
        Fxp speed_factor = 3.0;

        Vector2D bar[4];

        const uint16_t barHeight = 64;
        uint16_t halfWidth;

        Fxp minimumWidth;
        Fxp maximumWidth;

        uint16_t halfHeight;
        const HighColor color_end = HighColor(0);
        const HighColor color_start = HighColor(HighColor::Colors::White);


   
    public:
    
    Loader(const uint8_t total_cnt)
    {
        this->total_cnt = total_cnt;
        
        // Get screen size
        this->halfWidth = SRL::TV::Width >> 1;
        this->minimumWidth = Fxp::Convert(-halfWidth);
        this->maximumWidth = Fxp::Convert(halfWidth);
        halfHeight = SRL::TV::Height >> 1;
        Fxp minimumHeight = Fxp::Convert(-halfHeight);
        Fxp maximumHeight = Fxp::Convert(halfHeight);
    }

    bool finished()
    {
        if(curr_cnt >= total_cnt)
        {
            return true;
        }else
        {
            return false;
        }
    }

    bool drawLoadingBar(uint8_t curr_cnt)
    {
        
        bool ret = false;
        this->target_cnt = curr_cnt;
        this->target_width = ((Fxp::Convert(curr_cnt) / Fxp::Convert(total_cnt)) * SRL::TV::Width) ;

        if(this->curr_width <  this->target_width)
        {
            this->curr_width = (this->curr_width + (this->speed_factor)) ;
            ret = true ;
        }

        HighColor curr_color;
               
        Fxp Ratio = this->curr_width / Fxp::Convert(SRL::TV::Width);

        if(Ratio > 1.0)
        {
            curr_color.Red = color_end.Red;
            curr_color.Green = color_end.Green;
            curr_color.Blue = color_end.Blue;
        }
        else
        {
            curr_color.Red = (Fxp::Convert(color_start.Red) + ((Fxp::Convert(color_end.Red) - Fxp::Convert(color_start.Red))) * Ratio).As<int16_t>();
            curr_color.Green = (Fxp::Convert(color_start.Green) + ((Fxp::Convert(color_end.Green) - Fxp::Convert(color_start.Green))) * Ratio).As<int16_t>();
            curr_color.Blue = (Fxp::Convert(color_start.Blue) + ((Fxp::Convert(color_end.Blue) - Fxp::Convert(color_start.Blue))) * Ratio).As<int16_t>();
        }

        

        SRL::VDP2::SetBackColor(curr_color);

        Fxp bH = Fxp::Convert(barHeight/2);

        bar[0] = Vector2D(this->minimumWidth,  - bH );
        bar[1] = Vector2D(this->curr_width + this->minimumWidth,  - bH );

        bar[2] = Vector2D(this->curr_width + this->minimumWidth,   bH );
        bar[3] = Vector2D(this->minimumWidth, bH );

        SRL::Scene2D::DrawPolygon(bar, true, HighColor::Colors::White,512.0);
        SRL::Core::Synchronize();
        return ret;
    }

    bool drawLoadingBarAnim(uint8_t curr_cnt)
    {
        SRL::Debug::Print(1,2, "item %d", curr_cnt);
        while(drawLoadingBar(curr_cnt))
        {
            //SRL::Debug::Print(1, 3, "drawBar == true");
        }
            //SRL::Debug::Print(1, 2, "drawBar == false");
        
            SRL::Debug::PrintClearLine(5);
            SRL::Debug::PrintClearLine(6);
            SRL::Debug::Print(1, 5, "Free VDP1 mem %d ", SRL::VDP1::GetAvailableMemory());
            SRL::Debug::Print(1, 6, "free HighWorkRam space %d" , SRL::Memory::HighWorkRam::GetFreeSpace());

        return true;
    }
};