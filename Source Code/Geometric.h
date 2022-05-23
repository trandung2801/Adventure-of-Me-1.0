#ifndef GEOMETRIC_H_INCLUDED
#define GEOMETRIC_H_INCLUDED

#include "Base.h"
#include "GeneralData.h"

typedef struct GeometricFormat // Chứa các thông số của các hình học trong game
{
public:
    GeometricFormat(int left, int top, int width, int height) {left_ = left, top_ = top, width_ = width, height_ = height;}

    int left_;
    int top_;
    int width_;
    int height_;

};

typedef struct ColorData // Chứa các color của hình học trong game
{
    ColorData(Uint8 r, Uint8 g, Uint8  b) {red_ = r, green_ = g, blue_ = b;}
public:
    Uint8 red_;
    Uint8 green_;
    Uint8 blue_;
};

class Geometric // Lớp các hình học có trong game
{
public:
    static void RenderRectangle(const GeometricFormat& geo_size, const ColorData& color_data, SDL_Renderer* screen);
    static void RenderOutline(const GeometricFormat& geo_size, const ColorData& color_data, SDL_Renderer* screen);
} ;


#endif // GEOMETRIC_H_INCLUDED
