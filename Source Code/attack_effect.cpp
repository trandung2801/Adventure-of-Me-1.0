#include "attack_effect.h"

attack_effect::attack_effect()
{
    x_val_ = 0;
    y_val_ = 0;
    is_move_ = false;
    attack_effect_type = NULL;
}

attack_effect::~attack_effect()
{

}

bool attack_effect::LoadImgAttackEffect(SDL_Renderer* des)
{
    bool ret = false;
    if(attack_effect_type == attack_effect_skill_3 && attack_effect_dir_ == DIR_RIGHT)
    {
        ret = LoadImg("Data IMG//main_animation//attack effect//1 right.png", des);
    }
    else if(attack_effect_type == attack_effect_skill_3 && attack_effect_dir_ == DIR_LEFT)
    {
        ret = LoadImg("Data IMG//main_animation//attack effect//1 left.png", des);
    }
    else if(attack_effect_type == attack_effect_skill_4  )
    {
        ret = LoadImg("Data IMG//main_animation//attack effect//4.png", des);
    }
    return ret;

}

SDL_Rect attack_effect::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y - 50;
    rect.w = rect_.w;
    rect.h = rect_.h;
    return rect;
}

void attack_effect::HandleMove(const int& x_border, const int& y_border)
{
    if (attack_effect_dir_ == DIR_RIGHT)
    {
        rect_.x += x_val_;
        if (rect_.x > x_border)
        {
            is_move_ = false;
        }
    }
    else if (attack_effect_dir_ == DIR_LEFT)
    {
        rect_.x -= x_val_;
        if (rect_.x < 0)
        {
            is_move_ = false;
        }
    }
    else if (attack_effect_dir_ == DIR_UP)
    {
        rect_.y -= y_val_;
        if(rect_.y < 0)
        {
            is_move_ = false;
        }
    }
    else if (attack_effect_dir_ == DIR_UP_LEFT)
    {
        rect_.x -= x_val_;
        if(rect_.x < 0)
        {
            is_move_ = false;
        }
        rect_.y -= y_val_;
        if(rect_.y < 0)
        {
            is_move_ = false;
        }
    }
    else if (attack_effect_dir_ == DIR_UP_RIGHT)
    {
        rect_.x += x_val_;
        if(rect_.x > x_border)
        {
            is_move_ = false;
        }
        rect_.y -= y_val_;
        if(rect_.y < 0)
        {
            is_move_ = false;
        }
    }
    else if (attack_effect_dir_ == DIR_DOWN)
    {
        rect_.y += y_val_;
        if(rect_.y > y_border)
        {
            is_move_ = false;
        }
    }
}
