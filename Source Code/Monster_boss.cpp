#include "Monster_boss.h"

MonsterBoss::MonsterBoss()
{
    frame_ = 0;
    x_val_ = 0;
    y_val_ = 0;
    x_pos_ = 0;
    y_pos_ = 0;
    width_frame_ = 0;
    height_frame_ = 0;
    map_x_ = 0;
    map_y_ =0;

    blood = 10000;

    on_ground_ = false;
    come_back_time = 0;
}

MonsterBoss::~MonsterBoss()
{

}

bool MonsterBoss::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = Base::LoadImg(path, screen);
    if(ret == true)
    {
        width_frame_ = rect_.w/FRAME_NUM_32;
        height_frame_ = rect_.h;
    }
    return ret;
}

SDL_Rect MonsterBoss::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = rect_.x ;
    rect.y = rect_.y ;
    rect.w = width_frame_;
    rect.h = height_frame_;
    return rect;
}

void MonsterBoss::set_clips()
{
    if (width_frame_> 0 && height_frame_ > 0)
    {
        for(int i = 0; i < FRAME_NUM_32; i++)
        {
            frame_clip_[i].x = i*width_frame_;
            frame_clip_[i].y = 0;
            frame_clip_[i].w = width_frame_;
            frame_clip_[i].h = height_frame_;
        }
    }
}

void MonsterBoss::Show(SDL_Renderer* des)
{
    if(come_back_time == 0)
    {
        rect_.x = x_pos_ - map_x_;
        rect_.y = y_pos_ - map_y_;
        frame_++;
        if(frame_ >= 32)
        {
            frame_ = 0;
        }

        SDL_Rect* currentClip = &frame_clip_[frame_];
        SDL_Rect rendQad = {rect_.x, rect_.y, width_frame_, height_frame_};
        if(currentClip != NULL)
        {
            rendQad.w = currentClip->w;
            rendQad.h = currentClip->h;
        }
        SDL_RenderCopy(des, p_object_, currentClip, &rendQad);
    }
}

void MonsterBoss::DoPlayer(Map& g_map)
{
    if(come_back_time == 0 )
    {
        x_val_ = 0;
        y_val_ += MONSTER_GRAVITY_SPEED;

        if(y_val_ >= MONSTER_MAX_FALL_SPEED)
        {
            y_val_ = MONSTER_MAX_FALL_SPEED;
        }
        if(input_type_.left_ == 1)
        {
            x_val_ -= MONSTER_SPEED;
        }
        if(input_type_.right_ == 1)
        {
            x_val_ += MONSTER_SPEED;
        }

        CheckMap(g_map);
    }
    else if (come_back_time > 0)
    {
        come_back_time --;
        if(come_back_time == 0)
        {
            InitMonster();
        }
    }
}

void MonsterBoss::InitMonster()
{
    x_val_ = 0;
    x_val_ = 0;
    if(x_pos_ > 256)
    {
        x_pos_ -= 256;
        //animation_a_ -= 256;
        //animation_b_ -= 256;
    }
    else
    {
        x_pos_ = 0;
    }
        y_pos_ =0;
        come_back_time = 0;
        input_type_.left_ = 1;
}

void MonsterBoss::CenterEntityOnmap(Map& g_map)
{
    g_map.start_x_ = x_pos_ - (SCREEN_WIDTH/2);
    if(g_map.start_x_ < 0)
    {
        g_map.start_x_ = 0;
    }
    else if (g_map.start_x_ + SCREEN_WIDTH >= g_map.max_x_)
    {
        g_map.start_x_ = g_map.max_x_ - SCREEN_WIDTH;
    }

    g_map.start_y_ = y_pos_ - (SCREEN_HEIGHT/2);
    if(g_map.start_y_ < 0)
    {
        g_map.start_y_ = 0;
    }
    else if (g_map.start_y_ + SCREEN_HEIGHT >= g_map.max_y_)
    {
        g_map.start_y_ = g_map.max_y_ - SCREEN_HEIGHT;
    }
}

void MonsterBoss::CheckMap(Map& g_map)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    //Check theo Ox
    int height_min = height_frame_< TILE_SIZE ? height_frame_ : TILE_SIZE;

    x1 = (x_pos_ + x_val_)/TILE_SIZE; // Check xem main đang ở ô thứ bao nhiêu theo ox
    x2 = (x_pos_ + x_val_ + width_frame_ - 1)/TILE_SIZE; // Check xem main

    y1 = (y_pos_)/TILE_SIZE; // Check xem main đang ở ô thứ bao nhiêu theo oy
    y2 = (y_pos_ + height_min - 1)/TILE_SIZE;

    if(x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y) // Nếu như main nằm trong bản đồ
    {
        if(x_val_ > 0) // main đang di chuyển về bên phải
        {
            int val_1 = g_map.tile[y1][x2];
            int val_2 = g_map.tile[y2][x2];

            if ((val_1 != BLANK_TILE && val_1 != MONEY) || (val_2 != BLANK_TILE && val_2 != MONEY)) // Nếu ô thứ (y1,x2) or (y2,x2) không phải là ô trống (khác 0)
            {
                x_pos_ = x2*TILE_SIZE; // Lập tức main sẽ dừng tại vị trí hiện tại
                x_pos_ -= width_frame_ + 1; // Trả về vị trí cũ cho main
                x_val_ = 0; // Lập tức x_val_ = 0
            }
        }
        else if (x_val_ < 0) // Main đang di chuyển về bên trái
        {
            int val_1 = g_map.tile[y1][x1];
            int val_2 = g_map.tile[y2][x1];

            if ((val_1 != BLANK_TILE && val_1 != MONEY) || (val_2 != BLANK_TILE && val_2 != MONEY)) // Nếu ô thứ (y1,x1) or (y2,x1) không phải là ô trống (khác 0)
            {
                x_pos_ = (x1 + 1)*TILE_SIZE;
                x_val_ = 0; //Lập tức x_val = 0
            }
        }
    }

    //Check theo Oy (Tương tự như Ox)
    int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;

    x1 = (x_pos_)/TILE_SIZE;
    x2 = (x_pos_ + width_min)/TILE_SIZE;

    y1 = (y_pos_ + y_val_)/TILE_SIZE;
    y2 = (y_pos_ + y_val_ + height_frame_ - 1)/TILE_SIZE;

    if(x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y)
    {
        if(y_val_ > 0)
        {
            int val_1 = g_map.tile[y2][x1];
            int val_2 = g_map.tile[y2][x2];

            if((val_1 != BLANK_TILE && val_1 != MONEY) || (val_2 != BLANK_TILE && val_2 != MONEY))
            {
                y_pos_ = y2*TILE_SIZE;
                y_pos_ -= (height_frame_ + 1);
                y_val_ = 0;

                on_ground_ = true;
            }
        }
        else if (y_val_ < 0)
        {
            int val_1 = g_map.tile[y1][x1];
            int val_2 = g_map.tile[y1][x2];

            if((val_1 != BLANK_TILE && val_1 != MONEY) || (val_2 != BLANK_TILE && val_2 != MONEY))
            {
                y_pos_ = (y1 + 1)*TILE_SIZE;
                y_val_ = 0;
            }
        }
    }

    // Nếu không va chạm thì di chuyển như bình thường
    x_pos_ += x_val_;
    y_pos_ += y_val_;

    if(x_pos_ < 0) // Nếu lùi tới giới hạn map
    {
        x_pos_ = 0;
    }
    else if (x_pos_ + width_frame_ > g_map.max_x_)
    {
        x_pos_ = g_map.max_x_ - width_frame_ - 1;
    }

    if(y_pos_ > g_map.max_y_)
    {
        come_back_time = 60;
    }
}

void MonsterBoss::InitAttackEffect(SDL_Renderer* screen)
{
    attack_effect* p_attack_effect = new attack_effect();
    bool ret = p_attack_effect->LoadImg("Data IMG//monster_animation//boss attackeffect.png", screen);
    if(ret)
    {
        p_attack_effect->set_attack_effect_dir_(attack_effect::DIR_LEFT);
        p_attack_effect->set_is_move(true);
        p_attack_effect->SetRect(rect_.x - 50 , rect_.y + 220 );
        p_attack_effect->set_x_val(20);
        attack_effect_list.push_back(p_attack_effect);
    }
}

void MonsterBoss::MakeAttackEffect(SDL_Renderer* des, const int& x_limit, const int& y_limit)
{
    if(frame_ == 18)
    {
        InitAttackEffect(des);
    }
    for(int i = 0; i < attack_effect_list.size(); i++)
    {
        attack_effect* p_attack_effect = attack_effect_list.at(i);
        if(p_attack_effect != NULL)
        {
            if(p_attack_effect->get_is_move())
            {
                int attack_effect_distance = rect_.x + width_frame_ - p_attack_effect->GetRect().x;
                if( attack_effect_distance  < 1500 && attack_effect_distance > 0)
                {
                    p_attack_effect->HandleMove(x_limit, y_limit);
                    p_attack_effect->Render(des);
                }
                else
                {
                    p_attack_effect->set_is_move(false);
                }
            }
            else
            {
                p_attack_effect->Release();
                attack_effect_list.erase(attack_effect_list.begin() + i);
            }
        }
    }
}

void MonsterBoss::DameSkill_1_2()
{
    blood -= 20;
}

void MonsterBoss::DameSkill_3()
{
    blood -= 250;
}

void MonsterBoss::DameSkill_4()
{
    blood -= 1000;
}
