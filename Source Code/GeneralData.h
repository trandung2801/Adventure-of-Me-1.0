#ifndef GENERALDATA_H_INCLUDED
#define GENERALDATA_H_INCLUDED

#include<bits/stdc++.h>
#include <windows.h>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "Text_obj.h"

using namespace std;

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

// Screen
const int FRAME_PER_SECOND = 30;
const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 960;
const int SCREEN_BPP = 32;

//Color base
const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 0xff;



#define BLANK_TILE 0
#define TILE_SIZE 64

#define MAX_MAP_X 450
#define MAX_MAP_Y 15

#define MONEY 6
#define HEART 5

#define None_  1000
#define DEFAULT_RIGHT 100
#define DEFAULT_LEFT 102
#define WALK_RIGHT 103
#define WALK_LEFT 104
#define JUMP 105
#define SKILL_1_RIGHT 106
#define SKILL_2_RIGHT 107
#define SKILL_3_RIGHT 108
#define SKILL_4_RIGHT 109
#define SKILL_1_LEFT 110
#define SKILL_2_LEFT 111
#define SKILL_3_LEFT 112
#define SKILL_4_LEFT 113



typedef struct Input // Các sự kiện của main
{
    int left_;
    int right_;
    int up_;
    int down_;
    int jump_;
    int skill_1_right;
    int skill_2_right;
    int skill_3_right;
    int skill_4_right;
    int skill_1_left;
    int skill_2_left;
    int skill_3_left;
    int skill_4_left;
    int default_right;
    int default_left;
};


typedef struct Map // Các trạng thái của title
{
    int start_x_;
    int start_y_;

    int max_x_;
    int max_y_;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name_;
};

namespace SDLGenaralData
{
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2); // Check va chạm giữa các sự kiện trong game

    int ShowMenu(SDL_Renderer* g_screen, TTF_Font* font,
                      const std::string& menu1,
                      const std::string& menu2,
                      const std::string& img_name); // Render Menu
    int MyRandom(int min, int max); // Hàm ngầu nhiên
}


#endif // GENERALDATA_H_INCLUDED
