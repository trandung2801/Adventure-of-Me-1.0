#include "explosion_obj.h"

ExplosionObj::ExplosionObj()
{
    frame_width_ = 0;
    frame_height_ = 0;
    frame_ = 0;
}

ExplosionObj::~ExplosionObj()
{

}

bool ExplosionObj::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = Base::LoadImg(path, screen);

    if(ret)
    {
        frame_width_ = rect_.w/NUM_FRAME_EXPLOSION;
        frame_height_ = rect_.h;
    }
    return ret;
}

void ExplosionObj::set_clip()
{
    if (frame_width_ > 0 && frame_height_ > 0)
    {
        for(int i = 0; i < NUM_FRAME_EXPLOSION; i++)
        {
            frame_clip_[i].x = i*frame_width_;
            frame_clip_[i].y = 0;
            frame_clip_[i].w = frame_width_;
            frame_clip_[i].h = frame_height_;
        }
    }
}

void ExplosionObj::Show(SDL_Renderer* screen)
{
    SDL_Rect* current_clip = &frame_clip_[frame_];
    SDL_Rect render_quad = {rect_.x, rect_.y, frame_width_, frame_height_};
    if(current_clip != NULL)
    {
        render_quad.w = current_clip->w;
        render_quad.h = current_clip->h;
    }

    SDL_RenderCopy(screen, p_object_, current_clip, &render_quad);
}
