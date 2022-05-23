#ifndef BASE_H_INCLUDED
#define BASE_H_INCLUDED

#include "GeneralData.h"

class Base // Lớp Base, lớp nền tảng cho các lớp trên base
{
public:
    Base();
    ~Base();

    void SetRect(const int& x, const int& y) {rect_.x = x, rect_.y = y;}
    SDL_Rect GetRect() const {return rect_;}
    SDL_Texture* GetObject() const {return p_object_;}

    virtual bool LoadImg(std::string path, SDL_Renderer* screen);
    void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);

    void Release();
protected:
    SDL_Texture* p_object_;
    SDL_Rect rect_;
};

#endif // BASE_H_INCLUDED
