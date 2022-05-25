#include "main_obj.h"
#include "GeneralData.h"

void main_obj::HandeInputAction(SDL_Event events, SDL_Renderer* screen, Mix_Chunk* g_sound_main_attack[4], Mix_Chunk* g_sound_main[2]) // Hàm xử lí các sự kiện được nhập từ bàn phím
{
    if(events.type == SDL_KEYDOWN) // Nếu chúng ta ấn phím xuống (ấn nút xuống)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_RIGHT: // Nếu là ấn nút sang phải
            {
                status_ = WALK_RIGHT;
                input_type_.right_ = 1;
                input_type_.left_ = 0;
                input_type_.default_right = 0;
                input_type_.default_left = 0;
                Mix_PlayChannel(-1, g_sound_main[0], 0);
            }
            break;
        case SDLK_LEFT: // Nếu là ấn nút sang trái
            {
                status_ = WALK_LEFT;
                input_type_.right_ = 0;
                input_type_.left_ = 1;
                input_type_.default_right = 0;
                input_type_.default_left = 0;
                Mix_PlayChannel(-1, g_sound_main[0], 0);
            }
            break;
        case SDLK_UP:
            {
                if(on_ground_ == true)
                {
                    status_ = JUMP;
                    input_type_.jump_ = 1;
                    input_type_.default_right = 0;
                    input_type_.default_left = 0;
                }
            }
            break;
        case SDLK_q:
            {
                if(input_type_.right_ == 1 || input_type_.default_right == 1)
                {
                    status_ = SKILL_1_RIGHT;
                    input_type_.skill_1_right = 1;
                    input_type_.left_ = 0;
                    input_type_.default_right = 0;
                    input_type_.default_left = 0;
                    Mix_PlayChannel(-1, g_sound_main_attack[0], 0);
                }
                if(input_type_.left_ == 1 || input_type_.default_left == 1)
                {
                    status_ = SKILL_1_LEFT;
                    input_type_.skill_1_left = 1;
                    input_type_.right_ = 0;
                    input_type_.default_right = 0;
                    input_type_.default_left = 0;
                    Mix_PlayChannel(-1, g_sound_main_attack[0], 0);
                }
            }
            break;
        case SDLK_w:
            {
                if(input_type_.right_ == 1 || input_type_.default_right == 1)
                {
                    status_ = SKILL_2_RIGHT;
                    input_type_.skill_2_right = 1;
                    input_type_.left_ = 0;
                    input_type_.default_right = 0;
                    input_type_.default_left = 0;
                    Mix_PlayChannel(-1, g_sound_main_attack[0], 0);
                }
                if(input_type_.left_ == 1 || input_type_.default_left == 1)
                {
                    status_ = SKILL_2_LEFT;
                    input_type_.skill_2_left = 1;
                    input_type_.right_ = 0;
                    input_type_.default_right = 0;
                    input_type_.default_left = 0;
                    Mix_PlayChannel(-1, g_sound_main_attack[0], 0);
                }
            }
            break;
        case SDLK_e:
            {
                if (cooldownE == 0)
                {
                    attack_effect* p_attack_effect = new attack_effect();
                    p_attack_effect->set_attack_effect_type(attack_effect::attack_effect_skill_3);
                    if(input_type_.right_ == 1 || input_type_.default_right == 1)
                    {
                        status_ = SKILL_3_RIGHT;
                        input_type_.skill_3_right = 1;
                        input_type_.left_ = 0;
                        input_type_.default_right = 0;
                        input_type_.default_left = 0;
                        p_attack_effect->set_attack_effect_dir_(attack_effect::DIR_RIGHT);
                        p_attack_effect->LoadImgAttackEffect(screen);
                        p_attack_effect->SetRect(this->rect_.x + width_frame_ + 50, this->rect_.y + height_frame_*(-0.1));
                        Mix_PlayChannel(-1, g_sound_main_attack[1], 0);
                    }
                    if(input_type_.left_ == 1 || input_type_.default_left == 1)
                    {
                        status_ = SKILL_3_LEFT;
                        input_type_.skill_3_left = 1;
                        input_type_.right_ = 0;
                        input_type_.default_right = 0;
                        input_type_.default_left = 0;
                        p_attack_effect->set_attack_effect_dir_(attack_effect::DIR_LEFT);
                        p_attack_effect->LoadImgAttackEffect(screen);
                        p_attack_effect->SetRect(this->rect_.x - width_frame_ - 50, this->rect_.y + height_frame_*(-0.1));
                        Mix_PlayChannel(-1, g_sound_main_attack[1], 0);
                    }
                    p_attack_effect->set_x_val(20);
                    p_attack_effect->set_y_val(20);
                    p_attack_effect->set_is_move(true);

                    p_attack_effect_list_.push_back(p_attack_effect);
                }
                cooldownE = 100;
            }
            break;
        case SDLK_r:
            {
                if(cooldownR == 0)
                {
                    attack_effect* p_attack_effect = new attack_effect();
                    p_attack_effect->set_attack_effect_type(attack_effect::attack_effect_skill_4);
                    if(input_type_.default_right == 1)
                    {
                        status_ = SKILL_4_RIGHT;
                        input_type_.skill_4_right = 1;
                        input_type_.left_ = 0;
                        input_type_.default_right = 0;
                        input_type_.default_left = 0;
                        p_attack_effect->set_attack_effect_dir_(attack_effect::DIR_DOWN);
                        p_attack_effect->LoadImgAttackEffect(screen);
                        p_attack_effect->SetRect(this->rect_.x + width_frame_ + 200, height_frame_  - 160);
                        Mix_PlayChannel(-1, g_sound_main_attack[2], 0);
                    }
                    if(input_type_.default_left == 1)
                    {
                        status_ = SKILL_4_LEFT;
                        input_type_.skill_4_left = 1;
                        input_type_.right_ = 0;
                        input_type_.default_right = 0;
                        input_type_.default_left = 0;
                        p_attack_effect->set_attack_effect_dir_(attack_effect::DIR_DOWN);
                        p_attack_effect->LoadImgAttackEffect(screen);
                        p_attack_effect->SetRect(this->rect_.x - 400,height_frame_ - 160);
                        Mix_PlayChannel(-1, g_sound_main_attack[2], 0);
                    }
                    p_attack_effect->set_x_val(20);
                    p_attack_effect->set_y_val(30);
                    p_attack_effect->set_is_move(true);

                    p_attack_effect_list_.push_back(p_attack_effect);
                }
                cooldownR = 1000;
            }
            break;
        }
    }
    else if (events.type == SDL_KEYUP) // Nếu nút lên
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_RIGHT:
            {
                status_ = DEFAULT_RIGHT;
                input_type_.right_ = 0;
                input_type_.left_ = 0;
                input_type_.default_right = 1;
                input_type_.default_left = 0;
            }
            break;
        case SDLK_LEFT:
            {
                status_ = DEFAULT_LEFT;
                input_type_.right_ = 0;
                input_type_.left_ = 0;
                input_type_.default_right = 0;
                input_type_.default_left = 1;
            }
            break;
        case SDLK_UP:
        {
            input_type_.jump_ = 0;
        }
        break;
        case SDLK_q:
            {
                if(input_type_.default_right == 0 && status_ == SKILL_1_RIGHT)
                {
                    status_ = DEFAULT_RIGHT;
                    input_type_.skill_1_right = 0;
                    input_type_.left_ = 0;
                    input_type_.default_right = 1;
                    input_type_.default_left = 0;
                }
                if(input_type_.default_left == 0 && status_ == SKILL_1_LEFT)
                {
                    status_ = DEFAULT_LEFT;
                    input_type_.skill_1_left = 0;
                    input_type_.right_ = 0;
                    input_type_.default_right = 0;
                    input_type_.default_left = 1;
                }
            }
            break;
        case SDLK_w:
            {
                if(input_type_.default_right == 0 && status_ == SKILL_2_RIGHT)
                {
                    status_ = DEFAULT_RIGHT;
                    input_type_.skill_2_right = 0;
                    input_type_.left_ = 0;
                    input_type_.default_right = 1;
                    input_type_.default_left = 0;
                }
                if(input_type_.default_left == 0 && status_ == SKILL_2_LEFT)
                {
                    status_ = DEFAULT_LEFT;
                    input_type_.skill_2_left = 0;
                    input_type_.right_ = 0;
                    input_type_.default_right = 0;
                    input_type_.default_left = 1;
                }
            }
            break;
        case SDLK_e:
            {
                if(input_type_.default_right == 0 && status_ == SKILL_3_RIGHT)
                {
                    status_ = DEFAULT_RIGHT;
                    input_type_.skill_3_right = 0;
                    input_type_.left_ = 0;
                    input_type_.default_right = 1;
                    input_type_.default_left = 0;
                }
                if(input_type_.default_left == 0 && status_ == SKILL_3_LEFT)
                {
                    status_ = DEFAULT_LEFT;
                    input_type_.skill_3_left = 0;
                    input_type_.right_ = 0;
                    input_type_.default_right = 0;
                    input_type_.default_left = 1;
                }

            }
            break;
        case SDLK_r:
            {
                if(input_type_.default_right == 0 && status_ == SKILL_4_RIGHT)
                {
                    status_ = DEFAULT_RIGHT;
                    input_type_.skill_4_right = 0;
                    input_type_.left_ = 0;
                    input_type_.default_right = 1;
                    input_type_.default_left = 0;
                }
                if(input_type_.default_left == 0 && status_ == SKILL_4_LEFT)
                {
                    status_ = DEFAULT_LEFT;
                    input_type_.skill_4_left = 0;
                    input_type_.right_ = 0;
                    input_type_.default_right = 0;
                    input_type_.default_left = 1;
                }

            }
            break;
        }
    }
}

void main_obj::HandleAttackEffect(SDL_Renderer* des)
{
    for(int i = 0; i < p_attack_effect_list_.size(); i++)
    {
        attack_effect* p_attack_effect = p_attack_effect_list_.at(i);
        if(p_attack_effect != NULL)
        {
            if(p_attack_effect->get_is_move() == true)
            {
                p_attack_effect->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
                p_attack_effect->Render(des);
            }
            else
            {
                p_attack_effect_list_.erase(p_attack_effect_list_.begin() + i);
                if(p_attack_effect != NULL)
                {
                    delete p_attack_effect;
                    p_attack_effect = NULL;
                }
            }
        }
    }
}

void main_obj::DoPlayer(Map& map_data)
{
    if (come_back_time_ == 0)
    {
        x_val_ = 0;
        y_val_ += GRAVITY_SPEED;

        if(y_val_ >= MAX_FALL_SPEED) // Nếu y_val_ lớn hơn max_fall_speed thì cho y_val_ = max_fall_speed
        {
            y_val_ = MAX_FALL_SPEED;
        }

        if(input_type_.left_ == 1) // Nếu ấn trái
        {
            x_val_ -= PLAYER_SPEED;
        }
        if(input_type_.right_ == 1 ) // Nếu ấn phải
        {
            x_val_ += PLAYER_SPEED;
        }
        if(input_type_.jump_ == 1) // Nếu ấn nhảy
        {
            if (on_ground_ == true) // Chỉ khi nhân vật ở trên mặt đất
            {
                y_val_ = -  PLAYER_JUMP_VAL;
            }
            input_type_.jump_ = 0;
            on_ground_ = false;
        }

        CheckMap(map_data);
        CenterEntiTyOnMap(map_data);
    }
    if (come_back_time_ > 0)
    {
        come_back_time_ --;
        if(come_back_time_ == 0)
        {
            on_ground_ = false;
            if (x_pos_ > 256)
            {
                x_pos_ -= 256;
            }
            else
            {
                x_pos_ = 0;
            }
            y_pos_ = 0;
            x_val_ = 0;
            y_val_ = 0;
        }
    }
    if(cooldownE > 0)
    {
        CooldownE();
    }
    if(cooldownR > 0)
    {
        CooldownR();
    }
}
