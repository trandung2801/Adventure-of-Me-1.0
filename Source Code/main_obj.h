#ifndef MAIN_OBJ_H_INCLUDED
#define MAIN_OBJ_H_INCLUDED

#include <vector>
#include "GeneralData.h"
#include "Base.h"
#include "game_map.h"
#include "attack_effect.h"

#define NUM_FRAME_MAIN 8
#define GRAVITY_SPEED  0.8
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 8
#define PLAYER_JUMP_VAL 20

class main_obj : public Base// Lớp main được kế thừa từ base
{
public:
    main_obj();
    ~main_obj();

    bool LoadImg(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void HandeInputAction(SDL_Event, SDL_Renderer* screen, Mix_Chunk* g_sound_main_attack[4], Mix_Chunk* g_sound_main[2]);
    void set_clips();
    int GetStatus() const {return status_;}
    float GetX_pos() {return x_pos_;}

    void DoPlayer(Map& map_data);
    void CheckMap(Map& map_data);
    void SetMapXY(const int map_x, const int map_y) {map_x_ = map_x, map_y_ = map_y;}
    void CenterEntiTyOnMap (Map& map_data);
    void UpdateImageMain(SDL_Renderer* des);

    SDL_Rect GetRectFrame();

    void set_attack_effect_list(const std::vector<attack_effect*>& attack_effect_list)
    {
        p_attack_effect_list_ = attack_effect_list;
    }
    std::vector<attack_effect*> get_attack_effect_list() const {return p_attack_effect_list_;}
    void HandleAttackEffect(SDL_Renderer* des);
    void RemoveAttackEffect(const int& idx);
    void set_comeback_time(const int& cb_time){ come_back_time_ = cb_time;}
    void CooldownE();
    int GetCooldownE() const {return cooldownE;}

    void CooldownR();
    int GetCooldownR() const {return cooldownR;};

    void IncreaseMoney();
    int GetMoneyCount() const {return money_count;}

    void Healing();
    void DameMonsterBoss1();
    void DameMonsterBoss2();
    void DameMonster1();
    int GetBlood() const {return blood;}
    void reset_blood();

private:

    int money_count;
    int score;

    std::vector<attack_effect*> p_attack_effect_list_;

    float x_val_; // Biến tăng giảm theo trục Ox
    float y_val_; // Biến tăng giảm theo trục Oy

    // Vi trí hiện tại của main
    float x_pos_;
    float y_pos_;

    // Lưu kích thước thật của nhân vật ứng với 1 frame ảnh
    int width_frame_;
    int height_frame_;

    SDL_Rect frame_clip_[NUM_FRAME_MAIN];// Lưu các frame
    Input input_type_; // Biến lưu trạng thái
    int frame_; // Biến lưu chỉ số của frame
    int status_; // Lưu trạng thái của việc di chuyển
    bool on_ground_; // Biến check rơi tự do

    int map_x_;
    int map_y_;

    int come_back_time_;
    int cooldownE;
    int cooldownR;

    int blood;
};


#endif // MAIN_OBJ_H_INCLUDED
