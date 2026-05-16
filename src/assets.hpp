#pragma once
#include <srl.hpp>
#include <vector>

#include "modelObject.hpp"
#include "loader.hpp"
#include "fonts.hpp"



class BaseAssets
{
    public :
        void virtual loadAssets();
};


class Assets : public BaseAssets
{
    public :

    // holds the demo assets
    std::vector<int32_t> texturePool;
    std::vector<int32_t> textureDots;
    
    

    int32_t counters[7] = {0}; // to use for persistent data between frames index 0 - 0 : credits scene background is disabled, 1 otherwise
    SRL::Math::Types::Angle angles[6] = {0};
    Fxp floats[7] = {0};

    ModelObject cube_f;
    ModelObject pot;

    ModelObject cuberf;
    ModelObject cuberw;

    bitmapfont fonts;

    void loadAssets()
    {
        SRL::Debug::Print(16, 28, "VI-SAT 03 Party Version");

        Loader l = Loader(7);
        //load a background image to NBG0
        // loadImgtoTilemapNGB0("SPLASH1.TGA");
        // loadTilemapNGB0("SPLASH1.BIN");
        l.drawLoadingBarAnim(1);
        int32_t res = SRL::Cd::ChangeDir("NYA");
         if (res < 0 )
        {
            SRL::Debug::AssertScreen("SRL::Cd::ChangeDir error %d", "assets.hpp" ,  "loadAssets()" , res);
        }

        pot.LoadFile("POT.NYA");
        cube_f.LoadFile("CUBEF.NYA");
        cuberf.LoadFile("CUBERF.NYA");
        cuberw.LoadFile("CUBERW.NYA");
        SRL::Cd::ChangeDir((char*) 0);

        l.drawLoadingBarAnim(2);
        l.drawLoadingBarAnim(3);
        texturePool.push_back(this->loadTGA("BANSKY.TGA")); // 0
        l.drawLoadingBarAnim(4);
        texturePool.push_back(this->loadTGA("INTRO01.TGA")); // 1
        l.drawLoadingBarAnim(5);
        textureDots.push_back(this->loadTGA("DOTS1.TGA")); // 2
        l.drawLoadingBarAnim(6);
        textureDots.push_back(this->loadTGA("DOTS2.TGA")); // 3
        l.drawLoadingBarAnim(7);
        texturePool.push_back(this->loadTGA("FORBD.TGA")); // 2
       // texturePool.push_back(this->loadTGA("ARROW4.TGA")); // 3
        SRL::Debug::PrintClearScreen();
    };

    void loadTilemapNGB0(char* filename)
    {
        auto tile = new SRL::Tilemap::Interfaces::CubeTile(filename);     // load the tilemap into main ram
        SRL::VDP2::NBG0::LoadTilemap(*tile);                                    // load tilemap into NGB0
        delete tile;                                                            // free the tilemap copy in main ramm
    }

     void loadTilemapNGB1(char* filename)
    {
        auto tile = new SRL::Tilemap::Interfaces::CubeTile(filename);     // load the tilemap into main ram
        SRL::VDP2::NBG1::LoadTilemap(*tile);                                    // load tilemap into NGB1
        delete tile;                                                            // free the tilemap copy in main ramm
    }
    void loadImgtoTilemapNGB0(char* filename)
    {
        SRL::Bitmap::TGA* logo = new SRL::Bitmap::TGA(filename);//Load Bitmap image to work RAM
        SRL::Tilemap::Interfaces::Bmp2Tile* TestTilebmp = new SRL::Tilemap::Interfaces::Bmp2Tile(*logo);//convert bitmap to tilemap
        
        for(int i = 0 ; i < 19 ; i = i+3)
        {
            for(int j = 0 ; j < 14 ; j = j+3)
            {
                TestTilebmp->CopyMap(0,SRL::Tilemap::Coord(0,0), SRL::Tilemap::Coord(1,1), 0,SRL::Tilemap::Coord(i,j) );
            }
        }
        
        SRL::VDP2::NBG0::LoadTilemap(*TestTilebmp);//Transfer tilemap from work RAM to VDP2 VRAM and register with NBG2
        delete TestTilebmp;//free tilemap from work ram 
        delete logo;//free original bitmap from work ram
    }

    void loadImgtoTilemapNGB1(char* filename)
    {
        SRL::Bitmap::TGA* logo = new SRL::Bitmap::TGA(filename);//Load Bitmap image to work RAM
        SRL::Tilemap::Interfaces::Bmp2Tile* Tilebmp = new SRL::Tilemap::Interfaces::Bmp2Tile(*logo);//convert bitmap to tilemap
        
        SRL::VDP2::NBG1::LoadTilemap(*Tilebmp);//Transfer tilemap from work RAM to VDP2 VRAM and register with NBG2
        delete Tilebmp;//free tilemap from work ram 
        delete logo;//free original bitmap from work ram
    }

    void loadImgtoTilemapNGB2(char* filename)
    {
        SRL::Bitmap::TGA* logo = new SRL::Bitmap::TGA(filename);//Load Bitmap image to work RAM
        SRL::Tilemap::Interfaces::Bmp2Tile* Tilebmp = new SRL::Tilemap::Interfaces::Bmp2Tile(*logo);//convert bitmap to tilemap
        
        SRL::VDP2::NBG2::LoadTilemap(*Tilebmp);//Transfer tilemap from work RAM to VDP2 VRAM and register with NBG2
        delete Tilebmp;//free tilemap from work ram 
        delete logo;//free original bitmap from work ram
    }

     void loadImgtoTilemapNGB3(char* filename)
    {
        SRL::Bitmap::TGA* logo = new SRL::Bitmap::TGA(filename);//Load Bitmap image to work RAM
        SRL::Tilemap::Interfaces::Bmp2Tile* Tilebmp = new SRL::Tilemap::Interfaces::Bmp2Tile(*logo);//convert bitmap to tilemap
        
        SRL::VDP2::NBG3::LoadTilemap(*Tilebmp);//Transfer tilemap from work RAM to VDP2 VRAM and register with NBG2
        delete Tilebmp;//free tilemap from work ram 
        delete logo;//free original bitmap from work ram
    }

    void loadImgtoTilemapRBG0(char* filename)
    {
        SRL::Tilemap::Interfaces::CubeTile* TestTilebin = new SRL::Tilemap::Interfaces::CubeTile("FOGRGB.BIN");//Load tilemap from cd to main RAM
        SRL::VDP2::RBG0::LoadTilemap(*TestTilebin);
        delete TestTilebin;
        SRL::VDP2::RBG0::SetRotationMode(SRL::VDP2::RotationMode::TwoAxis);
    }

    int32_t loadTGA(const char* filename) //texture loading function
    {
        SRL::Bitmap::TGA *tga = new SRL::Bitmap::TGA(filename); // Loads TGA file into main RAM
        SRL::Bitmap::BitmapInfo info = tga->GetInfo();          // Get info about the tga we are loading
        int32_t textureIndex = -1;
        int32_t character_palette = 0;
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


};