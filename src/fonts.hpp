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

    SRL::Debug::AssertScreen("LoadPallet - no free bank", "fonts.hpp" ,  "LoadPallet()" );
    // No free bank found
    return -1;
    }

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
            textureIndex = SRL::VDP1::TryLoadTexture(tga, LoadPalette);
        }
        
        delete tga; 
        
        if (textureIndex == -1)
        {
            SRL::Debug::AssertScreen("Failed loading texture %s", filename, "loadTGA", filename);
        } 
        
        return textureIndex;
    }

class bitmapfont
{
    // Load color palettes here
    
    private : 
        int32_t char_spr_id[(127-32)] = {0}; //ASCII printable characters (character code 32-127)
        // ascci code space = 32
        // " " , !, " , # , $, %, &, ' , (, ), *, +, , , - , . , / , 0 , 
        std::vector<char*> list = {"SPACE.TGA", "EXCLAMAT.TGA", "DQUOTE.TGA", 
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
       /*
        for (int i = 0 ; i < 58 ; i++)
        {
            SRL::Debug::PrintClearLine(4);
            SRL::Debug::Print(1, 4, "Loading %s", this->list[i]);
            char_spr_id[i] = loadTGA(this->list[i]);
            SRL::Debug::PrintClearLine(4);
            SRL::Debug::PrintClearLine(5);
            SRL::Debug::Print(1, 4, "Loaded %s , %d", this->list[i], char_spr_id[i] );
            SRL::Debug::Print(1, 5, "Free mem %d ", SRL::VDP1::GetAvailableMemory());
        }     
        */
        
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
/*
    void PrintString(const char* s, uint16_t size, Fxp x, Fxp y, Fxp scale = 1.0)
    {
        Fxp x_offset = 32;
        Fxp x_curr = x ;
    
        for(int i = 0 ; i < size ; i++)
        {
            this->printChar(s[i], x_curr, y);
            x_curr = x_curr + x_offset; 
        }

    }
*/
    
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
       transformS = transformS.CreateScale(Vector3D(1.0));



       
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

        //add the offset

        /*
        for(int j = 0 ; j<4 ; j++)
        {
            points[j] = points[j] + cursor;
        }
       */
       
        Matrix33 transforms =  translationM(x,y) * transformR *  translationM(cursor.X,cursor.Y) * transformS;

        //rotate the points

        Vector3D vec3_points[4] = {Vector3D(0.0)};
        vec3_points[0] = Vector3D(points[0], 1.0);
        vec3_points[1] = Vector3D(points[1], 1.0);
        vec3_points[2] = Vector3D(points[2], 1.0);
        vec3_points[3] = Vector3D(points[3], 1.0);

       
       
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
        
        // draw out sprite

        SRL::Scene2D::DrawSprite(char_spr_id[(int)c], points, 50.0 );

       
    
       }


        
       

    }

    

};

