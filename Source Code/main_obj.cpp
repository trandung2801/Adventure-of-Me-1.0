
#include "main_obj.h"
#include "attack_effect.h"
#include "monster_obj.h"
#include "GeneralData.h"

main_obj::main_obj() // Khởi tạo hàm dành cho main với các trạng thái ban đầu
{
    frame_ = 0;
    x_pos_ = 0;
    y_pos_ = 0;
    x_val_ = 0;
    y_val_ = 0;
    width_frame_ = 0;
    height_frame_ = 0;

    status_ = None_;
    input_type_.left_ = 0;
    input_type_.right_ = 0;
    input_type_.down_ = 0;
    input_type_.up_ = 0;
    input_type_.jump_ = 0;

    input_type_.skill_1_right = 0;
    input_type_.skill_2_right = 0;
    input_type_.skill_3_right = 0;
    input_type_.skill_4_right = 0;
    input_type_.skill_1_left = 0;
    input_type_.skill_2_left = 0;
    input_type_.skill_3_left = 0;
    input_type_.skill_4_left = 0;

    input_type_.default_right = 1;
    input_type_.default_left = 1;

    on_ground_ = false;
    map_x_ = 0;
    map_y_ = 0;

    come_back_time_ = 0;
    cooldownR = 0;
    cooldownE = 0;
    money_count = 0;

    blood = 1000;
}

main_obj::~main_obj() // Hàm hủy
{

}



void main_obj::CenterEntiTyOnMap(Map& map_data)
{
    map_data.start_x_ = x_pos_ - (SCREEN_WIDTH/2);
    if(map_data.start_x_ < 0)
    {
        map_data.start_x_ = 0;
    }
    else if (map_data.start_x_ + SCREEN_WIDTH >= map_data.max_x_)
    {
        map_data.start_x_ = map_data.max_x_ - SCREEN_WIDTH;
    }

    map_data.start_y_ = y_pos_ - (SCREEN_HEIGHT/2);
    if(map_data.start_y_ < 0)
    {
        map_data.start_y_ = 0;
    }
    else if (map_data.start_y_ + SCREEN_HEIGHT >= map_data.max_y_)
    {
        map_data.start_y_ = map_data.max_y_ - SCREEN_HEIGHT;
    }
}

void main_obj::CheckMap(Map& map_data)
{
    Mix_Chunk* g_sound_item[2];

    g_sound_item[0] = Mix_LoadWAV("Sound//Item//Hp.wav");
    g_sound_item[1] = Mix_LoadWAV("Sound//Item//Money.wav");

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
            int val_1 = map_data.tile[y1][x2];
            int val_2 = map_data.tile[y2][x2];

            if(val_1 == MONEY || val_2 == MONEY)
            {
                map_data.tile[y1][x2] = 0;
                map_data.tile[y2][x2] = 0;
                IncreaseMoney();
                Mix_PlayChannel(-1, g_sound_item[1], 0);
            }
            else if(val_1 == HEART || val_2 == HEART)
            {
                map_data.tile[y1][x2] = 0;
                map_data.tile[y2][x2] = 0;
                Healing();
                Mix_PlayChannel(-1, g_sound_item[0], 0);
            }
            else
            {
                if (val_1 != BLANK_TILE || val_2 != BLANK_TILE) // Nếu ô thứ (y1,x2) or (y2,x2) không phải là ô trống (khác 0)
                {
                    x_pos_ = x2*TILE_SIZE; // Lập tức main sẽ dừng tại vị trí hiện tại
                    x_pos_ -= width_frame_ + 1; // Trả về vị trí cũ cho main
                    x_val_ = 0; // Lập tức x_val_ = 0
                }
            }
        }
        else if (x_val_ < 0) // Main đang di chuyển về bên trái
        {
            int val_1 = map_data.tile[y1][x1];
            int val_2 = map_data.tile[y2][x1];

            if(val_1 == MONEY || val_2 == MONEY)
            {
                map_data.tile[y1][x1] = 0;
                map_data.tile[y2][x1] = 0;
                IncreaseMoney();
                Mix_PlayChannel(-1, g_sound_item[1], 0);
            }
            else if(val_1 == HEART || val_2 == HEART)
            {
                map_data.tile[y1][x1] = 0;
                map_data.tile[y2][x1] = 0;
                Healing();
                Mix_PlayChannel(-1, g_sound_item[0], 0);
            }
            else
            {
               if (val_1 != BLANK_TILE || val_2 != BLANK_TILE) // Nếu ô thứ (y1,x1) or (y2,x1) không phải là ô trống (khác 0)
                {
                    x_pos_ = (x1 + 1)*TILE_SIZE;
                    x_val_ = 0; //Lập tức x_val = 0
                }
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
            int val_1 = map_data.tile[y2][x1];
            int val_2 = map_data.tile[y2][x2];
            if(val_1 == MONEY || val_2 == MONEY)
            {
                map_data.tile[y2][x1] = 0;
                map_data.tile[y2][x2] = 0;
                IncreaseMoney();
                Mix_PlayChannel(-1, g_sound_item[1], 0);
            }
            else if(val_1 == HEART || val_2 == HEART)
            {
                map_data.tile[y2][x1] = 0;
                map_data.tile[y2][x2] = 0;
                Healing();
                Mix_PlayChannel(-1, g_sound_item[0], 0);
            }
            else
            {
               if(val_1 != BLANK_TILE || val_2 != BLANK_TILE)
                {
                    y_pos_ = y2*TILE_SIZE;
                    y_pos_ -= (height_frame_ + 1);
                    y_val_ = 0;

                    on_ground_ = true;
                    if(status_ == None_)
                    {
                        status_ = DEFAULT_RIGHT;
                    }
                }
            }
        }
        else if (y_val_ < 0)
        {
            int val_1 = map_data.tile[y1][x1];
            int val_2 = map_data.tile[y1][x2];
            if(val_1 == MONEY || val_2 == MONEY)
            {
                map_data.tile[y1][x1] = 0;
                map_data.tile[y1][x2] = 0;
                IncreaseMoney();
                Mix_PlayChannel(-1, g_sound_item[1], 0);
            }
            else if(val_1 == HEART || val_2 == HEART)
            {
                map_data.tile[y1][x1] = 0;
                map_data.tile[y1][x2] = 0;
                Healing();
                Mix_PlayChannel(-1, g_sound_item[0], 0);
            }
            else
            {
               if(val_1 != BLANK_TILE || val_2 != BLANK_TILE)
                {
                    y_pos_ = (y1 + 1)*TILE_SIZE;
                    y_val_ = 0;
                }
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
    else if (x_pos_ + width_frame_ > map_data.max_x_)
    {
        x_pos_ = map_data.max_x_ - width_frame_ - 1;
    }

    if(y_pos_ > map_data.max_y_)
    {
        come_back_time_ = 60;
    }
}

void main_obj::RemoveAttackEffect(const int& idx)
{
    int size = p_attack_effect_list_.size();
    if(size > 0 && idx <size)
    {
        attack_effect* p_attack_effect = p_attack_effect_list_.at(idx);
        p_attack_effect_list_.erase(p_attack_effect_list_.begin() + idx);

        if(p_attack_effect)
        {
            delete p_attack_effect;
            p_attack_effect = NULL;

        }
    }
}

void main_obj::IncreaseMoney()
{
    money_count ++;
}

void main_obj::Healing()
{
    blood += 500;
}

void main_obj::reset_blood()
{
    blood += 1000;
}

void main_obj::DameMonster1()
{
    blood -= 1;
}

void main_obj::DameMonsterBoss1()
{
    blood -= 10;
}

void main_obj::DameMonsterBoss2()
{
    blood -= 100;
}

void main_obj::CooldownE()
{
    cooldownE -= 1;
}

void main_obj::CooldownR()
{
    cooldownR -= 1;
}
