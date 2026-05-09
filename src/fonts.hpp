#pragma once
#include <srl.hpp>
#include <vector>


// Using to shorten names for Vector and HighColor
using namespace SRL::Types;
using namespace SRL::Math::Types;


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

        SRL::Debug::AssertScreen("LoadPallet - no free bank", "fonts.hpp" ,  "LoadPallet" );
        // No free bank found
        return -1;
    }

    

class bitmapfont
{
    // Load color palettes here
    
    private : 
        int32_t char_spr_id[(127-32)] = {0}; //ASCII printable characters (character code 32-127)
        int32_t character_palette = 0; //palettes for the characters, if they are palette textures
        int32_t character_palette2 = 0; //palettes for the characters, if they are palette textures
        SRL::CRAM::Palette palettes[8]; //palettes for the characters, if they are palette textures
        SRL::CRAM::Palette mypalette;
        HighColor colors[255] = {HighColor(0,15,15)};
    
    public :

    int32_t loadTGA(const char* filename) //texture loading function
    {
        SRL::Bitmap::TGA *tga = new SRL::Bitmap::TGA(filename); // Loads TGA file into main RAM
        SRL::Bitmap::BitmapInfo info = tga->GetInfo();          // Get info about the tga we are loading
        int32_t textureIndex = -1;
        SRL::Debug::PrintClearLine(6);
        if(info.ColorMode == SRL::CRAM::TextureColorMode::RGB555) // RGBA texture
        {
            SRL::Debug::Print(1, 6, "RGB555");
            textureIndex = SRL::VDP1::TryLoadTexture(tga);  // Loads TGA into VDP1
        }
        else
        {
            switch (info.ColorMode)
            {
            case SRL::CRAM::TextureColorMode::Paletted128 :
                 SRL::Debug::Print(1, 6, "Paletted128");
                break;
            case SRL::CRAM::TextureColorMode::Paletted256 :
                 SRL::Debug::Print(1, 6, "Paletted256");
                break;
            case SRL::CRAM::TextureColorMode::Paletted64 :
                 SRL::Debug::Print(1, 6, "Paletted64");
                break;
            case SRL::CRAM::TextureColorMode::Paletted16 :
                 SRL::Debug::Print(1, 6, "Paletted16");
                break;
            
            default:
                SRL::Debug::Print(1, 6, "??");
                break;
            }
            if (character_palette == 0)
            {
                character_palette = LoadPalette(&info); // Load palette to CRAM and get its id
            }           
            
            textureIndex = SRL::VDP1::TryLoadTexture(tga, character_palette);
            
            
        }
        
        delete tga; 
        
        if (textureIndex == -1)
        {
            SRL::Debug::AssertScreen("Failed loading texture %s", filename, "loadTGA", filename);
        } 
        
        return textureIndex;
    }

    bitmapfont()
    {
        //create palette for the font characters, if they are paletted textures

        character_palette2 = SRL::CRAM::GetFreeBank(SRL::CRAM::TextureColorMode::Paletted16);
        if(character_palette2 < 0)
        {
            SRL::Debug::AssertScreen("Failed to get free CRAM bank for font palette", "fonts.hpp" ,  "bitmapfont()" );
        }
        mypalette = SRL::CRAM::Palette(SRL::CRAM::TextureColorMode::Paletted256, character_palette2);           

        // Todo : define some palette templates and use them instead of hardcoding colors here

        colors[0] = HighColor(0,10,0); //transparent
        colors[1] = HighColor(64,255,64); //white
        colors[2] = HighColor(255,0,0); //Red
        colors[3] = HighColor(255,0,0); //Red
        colors[4] = HighColor(0,0,0); //black
        colors[5] = HighColor(0,255,0); //Green
        colors[6] = HighColor(0,255,0); //Green
        colors[7] = HighColor(0,0,0); //    black
        colors[8] = HighColor(0,0,255); //   blue
        colors[9] = HighColor(0,0,255); //blue
        colors[10] = HighColor(255,0,255); // magenta
        colors[11] = HighColor(0,255,0); //green
        colors[12] = HighColor(0,0,255); //blue
        colors[13] = HighColor(255,255,0); //yellow
        colors[14] = HighColor(255,0,255); //magenta
        colors[15] = HighColor(0,255,255); //cyan
        colors[16] = HighColor(0,10,0); //transparent
        colors[17] = HighColor(255,0,0); 
        colors[18] = HighColor(30,0,31); //white
        colors[19] = HighColor(0,31,0); //green
        colors[20] = HighColor(0,0,14); //blue
        colors[21] = HighColor(31,31,0); //yellow
        colors[22] = HighColor(31,0,31); //magenta
        colors[23] = HighColor(0,31,31); //cyan
        colors[24] = HighColor(0,10,0); //transparent
        colors[25] = HighColor(31,0,0); //red
        colors[26] = HighColor(31,31,31); //white
        colors[27] = HighColor(0,31,0); //green
        colors[28] = HighColor(0,0,31); //blue
        colors[29] = HighColor(31,31,0); //yellow
        colors[30] = HighColor(31,0,31); //magenta
        colors[31] = HighColor(0,31,31); //cyan
        colors[32] = HighColor(0,10,0); //transparent
        colors[33] = HighColor(31,0,0); //red
        colors[34] = HighColor(31,31,31); //white
        colors[35] = HighColor(0,31,0); //green
        colors[36] = HighColor(0,0,31); //blue
        colors[37] = HighColor(31,31,0); //yellow
        colors[38] = HighColor(31,0,31); //magenta
        colors[39] = HighColor(0,128,128); //cyan

        for (int i = 40; i < 255; i++)
        {
            colors[i] = HighColor(255,255,255); //transparent
        }
        //... define more 256 colors as needed
        

        
        if (mypalette.Load(colors, -1) < 0)
        {
            SRL::Debug::AssertScreen("Failed to load font palette to CRAM", "fonts.hpp" ,  "bitmapfont()" );
        }

        SRL::CRAM::SetBankUsedState(character_palette2, SRL::CRAM::TextureColorMode::Paletted16, true);

             
        //load all textures from the list
        int32_t res = SRL::Cd::ChangeDir("FONT");	

        if (res < 0 )
        {
             SRL::Debug::AssertScreen("SRL::Cd::ChangeDir error %d", "fonts.hpp" ,  "bitmapfont()" , res);
        }

       for(int i = 0 ; i < 95 ; i++) // 127 - 32 = 95
        {
            SRL::Debug::PrintClearLine(4);
           // SRL::Debug::Print(1, 4, "Loading %s", this->list[i]);
            char filename[13] = {0};
            snprintf(filename, 13, "%d.TGA", i + 32);
            bool exists = SRL::Cd::File(filename).Exists();
            SRL::Debug::Print(1, 5, "File %s exists ? %d", filename, exists);
            if(exists)
            {
                SRL::Debug::Print(1, 4, "Loading %s", filename);
                char_spr_id[i] = loadTGA(filename);
                SRL::Debug::Print(1, 4, "Loaded %s , %d", filename, char_spr_id[i] );
            }else
            {
                char_spr_id[i] = char_spr_id[0]; // space character as fallback
                SRL::Debug::Print(1, 4, "File %s not found, using space as fallback", filename);
            }
           // SRL::Debug::PrintClearLine(4);
          //  SRL::Debug::PrintClearLine(5);
            SRL::Debug::Print(1, 5, "Free mem %d ", SRL::VDP1::GetAvailableMemory());

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
    
    Matrix33 translationM(Fxp x, Fxp y)
    {
        Matrix33 transform = Matrix33::Identity();
        transform.Row0.Z = x;
        transform.Row1.Z = y;
        return transform;
    }


    void PrintString(const char* s, Fxp x, Fxp y, Fxp spacing, Fxp scale, Fxp angle)
    {       
       Vector2D cursor = Vector2D(0,0);
       Vector2D points[4] = {Vector2D(0.0)};
       
       Matrix33 transformR = Matrix33::Identity();
       transformR = transformR.CreateRotationZ(Angle::FromDegrees(angle));

       Matrix33 transformT = translationM(x,y);

       Matrix33 transformS = Matrix33::Identity();
       transformS = transformS.CreateScale(Vector3D(scale));
      
       for(int i = 0 ; s[i] != 0 ; i++)
       {

        //determine character size
        //get the index 
        char c = s[i] - 32;

        //get the texture dimensions
        uint16_t h = SRL::VDP1::Textures[char_spr_id[(int)c]].Height;
        uint16_t w = SRL::VDP1::Textures[char_spr_id[(int)c]].Width;
        
        //set a quad at the center, with the size of the quad
        
        Fxp h2 = Fxp::Convert(h/2);
        Fxp w2 = Fxp::Convert(w/2);


        points[0] = Vector2D(-w2, -h2);
        points[1] = Vector2D(w2,  -h2);
        points[2] = Vector2D( w2,  h2);
        points[3] = Vector2D(-w2,  h2);
   
        Matrix33 transforms =  translationM(x,y) * transformR *  translationM(cursor.X,cursor.Y) * transformS;     

        Vector3D vec3_points[4] = {Vector3D(0.0)};
        vec3_points[0] = Vector3D(points[0], 1.0);
        vec3_points[1] = Vector3D(points[1], 1.0);
        vec3_points[2] = Vector3D(points[2], 1.0);
        vec3_points[3] = Vector3D(points[3], 1.0);

       
        //transform the points

        for(int j = 0 ; j < 4 ; j++)
        {
            //multiply vector by our rotation matrix
            vec3_points[j] = transforms *  vec3_points[j];
            // get back to vector2D type that  SRL::Scene2D::DrawSprite accepts
            points[j].X = vec3_points[j].X;
            points[j].Y = vec3_points[j].Y;
        }
        
        
         //update the cursor position for the next iteration
        cursor.X = cursor.X + spacing + Fxp::Convert(w);
        
        
        //SRL::Scene2D::DrawSprite(char_spr_id[(int)c], points, 500.0 );
         
        
        uint16_t paletteIndex = mypalette.GetId() ; 

        SRL::Debug::Print(1, 6, "palette index %d", paletteIndex);

        SPR_ATTR attr = SPR_ATTRIBUTE( char_spr_id[(int)c],paletteIndex << 8, No_Gouraud, 0 | ECdis | CL16Bnk , FUNC_Texture  );

        SRL::Scene2D::Draw( &attr,points, 500.0);
        
       }

    }

    

};

