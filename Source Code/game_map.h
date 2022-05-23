#ifndef GAME_MAP_H_INCLUDED
#define GAME_MAP_H_INCLUDED

#include "GeneralData.h"
#include "Base.h"

#define MAX_TILES 50

class TileMat : public Base // map được kế thừa từ base
{
public:
    TileMat() {;}
    ~TileMat() {;}
};

class GameMap // Lớp quản lý xây dựng map
{
public:
    GameMap() {;}
    ~GameMap() {;}

    void LoadMap(char* name);
    void LoadTiles(SDL_Renderer* screen);
    void DrawMap(SDL_Renderer* screen);
    Map getMap() const {return game_map_;}
    void SetMap(Map& map_data) {game_map_ = map_data;}

private:
    Map game_map_;
    TileMat tile_mat[MAX_TILES];
};


#endif // GAME_MAP_H_INCLUDED
