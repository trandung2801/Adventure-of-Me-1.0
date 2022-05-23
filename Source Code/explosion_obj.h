#ifndef EXPLOSION_OBJ_H_INCLUDED
#define EXPLOSION_OBJ_H_INCLUDED

#include "GeneralData.h"
#include "Base.h"

#define NUM_FRAME_EXPLOSION 8

class ExplosionObj : public Base // Lớp hoạt ảnh khi va chạm (chưa dùng tới)
{
public:
    ExplosionObj();
    ~ExplosionObj();

    void set_clip();
    void set_frame(const int& fr) { frame_ = fr;}
    virtual bool LoadImg(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* screen);
    int get_frame_width() const {return frame_width_;}
    int get_frame_height() const {return frame_height_;}

private:
    int frame_width_;
    int frame_height_;

    unsigned int frame_;
    SDL_Rect frame_clip_[NUM_FRAME_EXPLOSION];
};


#endif // EXPLOSION_OBJ_H_INCLUDED
