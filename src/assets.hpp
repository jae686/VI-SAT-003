#pragma once
#include <srl.hpp>
#include <vector>

#include "modelObject.hpp"
#include "loader.hpp"


enum class assetType : int {TEXTURE , NGB0, NGB1, RBG0, MESH, UNDEFINED};

class Cfilename
{
    char filename[13] = {0};
    assetType type = assetType::UNDEFINED;
};


class BaseAssets
{
    public :
        void virtual loadAssets();
};


class Assets : public BaseAssets
{
    public :

    // holds the demo assets
    ModelObject cube_textured;
    ModelObject cube_flat;
    ModelObject cube_half;
    ModelObject inercia;
    ModelObject sfia;
    ModelObject portugal;
    ModelObject cylinder;
    ModelObject iconosphere_wire;
    ModelObject iconosphere_half;


    std::vector<int32_t> texturePool;
    


    int32_t texture_1 ;
    int32_t texture_2 ;
    int32_t textures[10];
    int32_t scene03_txt[3];
    int32_t counters[7] = {0}; // to use for precistent data beetween frames
    SRL::Math::Types::Angle angles[6] = {0};
    Fxp floats[7] = {0};



    void loadAssets()
    {
        
       
        SRL::Debug::Print(16, 28, "VI-SAT 03 Party Version");
        Loader l = Loader(23);
        
        l.drawLoadingBarAnim(0);      
        l.drawLoadingBarAnim(1);
        cube_textured.LoadFile("CUBE_W.NYA");
        sfia.LoadFile("SFIA001.NYA");
        l.drawLoadingBarAnim(2);
        cube_flat.LoadFile("CUBE_F.NYA");
        l.drawLoadingBarAnim(3);
        inercia.LoadFile("INERCIA.NYA");
        l.drawLoadingBarAnim(4);
        cube_half.LoadFile("CUBE_H.NYA"); 
        l.drawLoadingBarAnim(5);
        this->loadImgtoTilemapNGB0("CROSS02.TGA");
        l.drawLoadingBarAnim(6);
        texture_1 = this->loadTGA("INERCIA0.TGA");
        l.drawLoadingBarAnim(7);
        this->loadImgtoTilemapNGB2("BG1.TGA");
        l.drawLoadingBarAnim(8);
        texture_2 = this->loadTGA("TITLE.TGA");
        l.drawLoadingBarAnim(9);
        textures[0] = this->loadTGA("SRL.TGA");
        l.drawLoadingBarAnim(10);
        textures[1] = this->loadTGA("TXT01.TGA");
        l.drawLoadingBarAnim(11);
        cylinder.LoadFile("CYLD_W.NYA");
        l.drawLoadingBarAnim(12);
        textures[2] = this->loadTGA("AHEAD.TGA");
        l.drawLoadingBarAnim(13);
        this->loadImgtoTilemapNGB1("BG2.TGA");
        l.drawLoadingBarAnim(14);
        l.drawLoadingBarAnim(15);
        l.drawLoadingBarAnim(16);
        l.drawLoadingBarAnim(17);
        iconosphere_half.LoadFile("ICO_M.NYA");
        l.drawLoadingBarAnim(18);
        iconosphere_wire.LoadFile("ICO_W.NYA");
        l.drawLoadingBarAnim(19);
        textures[4] = this->loadTGA("CREDITS1.TGA");
        l.drawLoadingBarAnim(20);
        textures[5] = this->loadTGA("CREDITS2.TGA");
        l.drawLoadingBarAnim(20);
        textures[6] = this->loadTGA("CREDITS3.TGA");
        l.drawLoadingBarAnim(20);
        textures[7] = this->loadTGA("CREDITS4.TGA");
        l.drawLoadingBarAnim(20);
        textures[8] = this->loadTGA("GLENZ.TGA");
        l.drawLoadingBarAnim(21);
        textures[9] = this->loadTGA("VI.TGA");
        l.drawLoadingBarAnim(22);
        l.drawLoadingBarAnim(23);

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