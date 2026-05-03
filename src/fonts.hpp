#pragma once
#include <srl.hpp>
#include <vector>


// Using to shorten names for Vector and HighColor
using namespace SRL::Types;
using namespace SRL::Math::Types;

enum class assetType : int {TEXTURE , NGB0, NGB1, RBG0, MESH, UNDEFINED};

class Cfilename
{
    public : 
    char filename[13] = {0};
    assetType type = assetType::UNDEFINED;
   
    
    Cfilename(char* a)
    {
        for(int i = 0 ; i < 13 ; i++)
        {
            this->filename[i] = a[i];
        }
    }

    /*Cfilename(const Cfilename &b)
    {
        for(int i = 0 ; i < 13 ; i++)
        {
            this->filename[i] = b.filename[i];
        }
        this->type = b.type;
    }
    */
};

int16_t LoadPalette(SRL::Bitmap::BitmapInfo* bitmap)
    {
    // Get free CRAM bank
    int32_t id = SRL::CRAM::GetFreeBank(bitmap->ColorMode);

    if (id >= 0)
    {
        SRL::CRAM::Palette palette(bitmap->ColorMode, id);

        if (palette.Load((HighColor*)bitmap->Palette->Colors, bitmap->Palette->Count) >= 0)
        {
            // Mark bank as in use
            SRL::CRAM::SetBankUsedState(id, bitmap->ColorMode, true);
            return id;
        }

        return id;
    }

    // No free bank found
    return -1;
    }

class bitmapfont
{
    // Load color palettes here
    
    private : 
        int32_t char_spr_id[58] = {0};
        // ascci code space = 32
        // " " , !, " , # , $, %, &, ' , (, ), *, +, , , - , . , / , 0 , 
        std::vector<char*> list = {"Y.TGA", "EXCLAMAT.TGA", "DQUOTE.TGA", 
                                         "HASHTAG.TGA","HASHTAG.TGA", "PERCENTA.TGA", 
                                         "ECOMER.TGA", "SQUOTE.TGA", "LPARENTE.TGA" ,
                                         "RPARENTE.TGA", "MIDDOT.TGA", "PLUS.TGA",
                                         "DOT.TGA" , "MINUS.TGA" , "DOT.TGA", "SLASH.TGA" , "0.TGA", 
                                         "1.TGA" , "2.TGA" , "3.TGA", "4.TGA",
                                         "5.TGA" , "6.TGA" , "7.TGA" , "8.TGA",
                                         "9.TGA" , "DDOT.TGA" , "DDOT.TGA" , 
                                         "DDOT.TGA", "EQUAL.TGA", "DDOT.TGA", 
                                         "QUESTION.TGA" , "AT.TGA", "A.TGA",
                                         "B.TGA" , "C.TGA", "D.TGA" , "E.TGA" ,
                                         "F.TGA" , "G.TGA" , "H.TGA", "I.TGA" ,
                                         "J.TGA" , "K.TGA", "L.TGA", "M.TGA" ,
                                         "N.TGA" , "O.TGA" , "P.TGA" , "Q.TGA" ,
                                         "R.TGA" , "S.TGA" , "T.TGA" , "U.TGA" ,
                                         "V.TGA" , "W.TGA","X.TGA" , "Y.TGA" ,
                                         "Z.TGA"  };
    
    public :



    bitmapfont()
    {
        //load all textures from the list
        int32_t res = SRL::Cd::ChangeDir("FONT");	

        if (res < 0 )
        {
             SRL::Debug::AssertScreen("SRL::Cd::ChangeDir error %d", "fonts.hpp" ,  "bitmapfont()" , res);
        }

        for (int i = 0 ; i < 55 ; i++)
        {
            SRL::Debug::PrintClearLine(4);
            SRL::Debug::Print(1, 4, "Loading %s", this->list[i]);
            char_spr_id[i] = loadTGA(this->list[i]);
            SRL::Debug::PrintClearLine(4);
            SRL::Debug::Print(1, 4, "Loaded %s , %d", this->list[i], char_spr_id[i] );

        }         
        SRL::Cd::ChangeDir((char*) 0);
    }


    void printChar(const char a, Fxp x, Fxp y, Fxp scale = 1.0)
    {
        //get the index 
        char c = a - 32;
        SRL::Debug::PrintClearLine(4);
        SRL::Debug::Print(1, 4, "char %d , index %d, id %d", a, c , char_spr_id[(int)c]);
        SRL::Scene2D::DrawSprite(char_spr_id[(int)c], Vector3D(x, y, 500.0));
    }

    int32_t loadTGA(const char* filename) //texture loading function
    {
        SRL::Bitmap::TGA *tga = new SRL::Bitmap::TGA(filename); // Loads TGA file into main RAM
        SRL::Bitmap::BitmapInfo info = tga->GetInfo();          // Get info about the tga we are loading
        int32_t textureIndex = -1;
        
        if(info.ColorMode == SRL::CRAM::TextureColorMode::RGB555) // RGBA texture
        {
            textureIndex = SRL::VDP1::TryLoadTexture(tga);  // Loads TGA into VDP1
        }
        else
        {
            //assume is pallet texture
            textureIndex = SRL::VDP1::TryLoadTexture(tga, LoadPalette);
        }
        
        delete tga; 
        
        if (textureIndex == -1)
        {
            SRL::Debug::AssertScreen("Failed loading texture %s", filename, "loadTGA", filename);
        } 
        
        return textureIndex;
}


};

