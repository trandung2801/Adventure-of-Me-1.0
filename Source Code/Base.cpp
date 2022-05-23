// Base dung de load anh va render anh len hinh nen
#include "Base.h"
#include "GeneralData.h"

Base::Base() // Khởi tạo thông số Base ban đầu
{
    p_object_ = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}

Base::~Base()
{
    Release();
}

bool Base::LoadImg(std::string path, SDL_Renderer* screen) // Hàm load ảnh bit map lên BaseObject
{
    Release();
    SDL_Texture* new_texture = NULL; // Khởi tạo

    SDL_Surface* load_surface = IMG_Load(path.c_str()); // Load ảnh lên màn hình (Đưa surface thành texture rồi đưa lên màn hình)
    if (load_surface != NULL) // Kiểm tra surface có lỗi không, nếu không lỗi thì
    {
        // Làm biến mất các phần background thừa trong các animation nhân vật (color key là màu nền trong)
        SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
        new_texture = SDL_CreateTextureFromSurface(screen, load_surface); // chuyển surface thành texture
        if(new_texture != NULL) // Nếu chuyển thành công
            {
            // Chuyển thông số surface thành các kích thước màn hình
            rect_.w = load_surface->w;
            rect_.h = load_surface->h;

        SDL_FreeSurface(load_surface); // Xóa surface vì thông số của surface đã có trong texture
    }
    }

    p_object_ = new_texture;

    return p_object_ != NULL; // Khác NULL return về 1, = return về 0
    // Lúc này p_object_ đã có 2 thông tin là texture và kích thước của bức ảnh
}

void Base::Render(SDL_Renderer* des, const SDL_Rect* clip /* = NULL */) //
{
    SDL_Rect renderquad = {rect_.x, rect_.y, rect_.w, rect_.h}; // bao gồm vị trí và kích thước của tấm ảnh
    SDL_RenderCopy(des, p_object_, clip, &renderquad); // Đẩy toàn bộ thông số của p_object_ lên des
}

void Base::Release()
{
    if(p_object_ != NULL)
    {
        SDL_DestroyTexture(p_object_); // Phá hủy toàn bộ thông số của p_object
        p_object_ = NULL;
        rect_.w = 0;
        rect_.h = 0;
    }
}
