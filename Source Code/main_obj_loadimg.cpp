
#include "main_obj.h"

bool main_obj::LoadImg(std::string path, SDL_Renderer* screen) // Hàm đọc path của main
{
    bool ret = Base::LoadImg(path, screen); // Tận dụng hàm load img của lớp base

    if(ret == true) // Nếu đọc được
    {
        width_frame_ = rect_.w/NUM_FRAME_MAIN; // Chia frame ra
        height_frame_ = rect_.h;
    }
    return ret;
}

void main_obj::set_clips() // Hàm tạo hiệu ứng clips cho main
{
    if (status_ == SKILL_4_RIGHT || status_ == SKILL_4_LEFT)
    {
        for(int i = 0; i < 16; i++)
        {
            frame_clip_[i].x = i*width_frame_;
            frame_clip_[i].y = 0;
            frame_clip_[i].w = width_frame_;
            frame_clip_[i].h = height_frame_;
        }

    }
    if (width_frame_> 0 && height_frame_ > 0)
    {
        for(int i = 0; i < NUM_FRAME_MAIN; i++)
        {
            frame_clip_[i].x = i*width_frame_;
            frame_clip_[i].y = 0;
            frame_clip_[i].w = width_frame_;
            frame_clip_[i].h = height_frame_;
        }
    }
}

SDL_Rect main_obj::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y - 50;
    rect.w = width_frame_;
    rect.h = height_frame_;
    return rect;
}

void main_obj::Show(SDL_Renderer* des) // Hàm show bức ảnh
{
    UpdateImageMain(des);

    if (input_type_.left_ == 1 || input_type_.right_ == 1 ||
        input_type_.skill_1_right == 1 || input_type_.skill_1_left == 1 ||
        input_type_.skill_2_right == 1 || input_type_.skill_2_left == 1 ||
        input_type_.skill_3_right == 1 || input_type_.skill_3_left == 1 ||
        input_type_.skill_4_right == 1 || input_type_.skill_4_left == 1 ||
        input_type_.default_right == 1 || input_type_.default_left == 1) // Nếu đang ấn giữ sangs trái hoặc phải liên tục thì liên tục + frame ảnh
    {
        frame_++;
    }
    else
    {
        frame_ = 0;
    }

    if (frame_ >= 8) // Nếu frame ảnh mà lớp hơn 8 thì load về 0 để reset
    {
        frame_ = 0;
    }

    if (come_back_time_ == 0)
    {
        // Cho biến vị trí hiện tại của main
        rect_.x = x_pos_ - map_x_;
        rect_.y = y_pos_ - map_y_;

        SDL_Rect* current_clip = &frame_clip_[frame_]; // Cho biết hiện tại đang ở frame, clip nào

        SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_}; // CHo biết chính xác nhân vật đang ở tọa độ nào chiều dài, rộng là bao nhiêu

        SDL_RenderCopy(des, p_object_, current_clip, &renderQuad); // Vẽ, đẩy các trạng thái của main lên trên màn hình
    }
}

void main_obj::UpdateImageMain(SDL_Renderer* des)
{
    if(on_ground_ == true)
    {
        switch(status_)
        {
        case DEFAULT_RIGHT:
            {
               LoadImg("Data IMG//main_animation//Walk//default right.png", des);
            }
            break;
        case DEFAULT_LEFT:
            {
                LoadImg("Data IMG//main_animation//Walk//default left.png", des);
            }
            break;
        case WALK_RIGHT:
            {
               LoadImg("Data IMG//main_animation//Walk//walk right.png", des);
            }
            break;
        case WALK_LEFT:
            {
                LoadImg("Data IMG//main_animation//Walk//walk left.png", des);
            }
            break;
        case SKILL_1_RIGHT:
            {
                LoadImg("Data IMG//main_animation//Skill 1//skill 1 right.png", des);
            }
            break;
        case SKILL_1_LEFT:
            {
                LoadImg("Data IMG//main_animation//Skill 1//skill 1 left.png", des);
            }
            break;
        case SKILL_2_RIGHT:
            {
                LoadImg("Data IMG//main_animation//Skill 2//skill 2 right.png", des);
            }
            break;
        case SKILL_2_LEFT:
            {
                LoadImg("Data IMG//main_animation//Skill 2//skill 2 left.png", des);
            }
            break;
        case SKILL_3_RIGHT:
            {
                LoadImg("Data IMG//main_animation//Skill 3//skill 1 right.png", des);
            }
            break;
        case SKILL_3_LEFT:
            {
                LoadImg("Data IMG//main_animation//Skill 3//skill 1 left.png", des);
            }
            break;
        case SKILL_4_RIGHT:
            {
                LoadImg("Data IMG//main_animation//Skill 4//skill 4 right.png", des);
            }
            break;
        case SKILL_4_LEFT:
            {
                LoadImg("Data IMG//main_animation//Skill 4//skill 4 left.png", des);
            }
            break;
        }
    }
}


