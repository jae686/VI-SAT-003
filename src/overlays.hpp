#include <srl.hpp>


class overlay
{
    public:
    overlay()
    {

    };

    void drawOverlayNGB0(SRL::Math::Vector2D start_p, uint16_t x_spacing = 0, uint16_t x_repeat = 0, uint16_t y_spacing = 0, uint16_t y_repeat = 0)
    {
        SRL::VDP2::NBG0::SetPriority(SRL::VDP2::Priority::Layer7);//set NBG0 priority
        SRL::VDP2::NBG0::ScrollEnable();//enable display of NBG0
        SRL::VDP2::NBG0::SetPosition(start_p);
    }

    void drawOverlayNGB1(SRL::Math::Vector2D start_p)
    {
        SRL::VDP2::NBG1::SetPriority(SRL::VDP2::Priority::Layer1);//set NBG0 priority
        SRL::VDP2::NBG1::ScrollEnable();//enable display of NBG0
        SRL::VDP2::NBG1::SetPosition(start_p);
    }

     void drawOverlayNGB2(SRL::Math::Vector2D start_p)
    {
        SRL::VDP2::NBG2::SetPriority(SRL::VDP2::Priority::Layer2);//set NBG0 priority
        SRL::VDP2::NBG2::ScrollEnable();//enable display of NBG0
        SRL::VDP2::NBG2::SetPosition(start_p);
    }

    void drawOverlayNGB3(SRL::Math::Vector2D start_p)
    {
        SRL::VDP2::NBG3::SetPriority(SRL::VDP2::Priority::Layer1);//set NBG0 priority
        SRL::VDP2::NBG3::ScrollEnable();//enable display of NBG0
        SRL::VDP2::NBG3::SetPosition(start_p);
    }

     void disableOverlayNGB1()
     {
         SRL::VDP2::NBG1::ScrollDisable();
     }

     void disableOverlayNGB2()
     {
         SRL::VDP2::NBG2::ScrollDisable();
     }

      void disableOverlayNGB3()
     {
         SRL::VDP2::NBG3::ScrollDisable();
     }

     void disableOverlayNGB0()
     {
         SRL::VDP2::NBG0::ScrollDisable();
     }


};
