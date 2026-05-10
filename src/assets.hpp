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
      
    int32_t counters[7] = {0}; // to use for precistent data beetween frames
    SRL::Math::Types::Angle angles[6] = {0};
    Fxp floats[7] = {0};

    bitmapfont fonts;

    void loadAssets()
    {
        SRL::Debug::Print(16, 28, "VI-SAT 03 Party Version");

        Loader l = Loader(1);

        //fonts = bitmapfont();
        SRL::Debug::PrintClearScreen();
    };

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

    int32_t loadTGA(char* filename)
    {
        SRL::Bitmap::TGA *tga = new SRL::Bitmap::TGA(filename); // Loads TGA file into main RAM
        int32_t textureIndex = SRL::VDP1::TryLoadTexture(tga);    // Loads TGA into VDP1
        delete tga;  
        return textureIndex;
    }


};