#ifndef MONSTER_BOSS__1_H_INCLUDED
#define MONSTER_BOSS__1_H_INCLUDED

#include "Base.h"
#include "GeneralData.h"
#include "attack_effect.h"

#define MONSTER_GRAVITY_SPEED 0.8
#define MONSTER_MAX_FALL_SPEED 10
#define MONSTER_SPEED 3

#define FRAME_NUM_32 32

class MonsterBoss : public Base // Lớp Boss của game được kế thừa từ lớp base khá tương đồng với lớp monster
{
public:
    MonsterBoss();
    ~MonsterBoss();
    void set_x_val(int xp) {x_val_ = xp;}
    void set_y_val(int yp) {y_val_ = yp;}

    void set_xpos(const int& xps) {x_pos_ = xps;}
    void set_ypos(const int& yps) {y_val_ = yps;}
    int get_x_pos() {return x_pos_;}
    int get_y_pos() {return y_pos_;}

    void Show(SDL_Renderer* des);
    bool LoadImg(std::string path, SDL_Renderer* screen);
    void set_clips();

    int get_width_frame() const {return width_frame_;}
    int get_height_frame() const {return height_frame_;}

    void SetMapXY(const int map_x, const int map_y) {map_x_ = map_x, map_y_ = map_y;}

    void CheckMap(Map& g_map);
    void CenterEntityOnmap(Map& g_map);
    void DoPlayer(Map& g_map);
    void InitMonster();
    SDL_Rect GetRectFrame();

    std::vector<attack_effect*> get_attack_effect_list() const {return attack_effect_list;}
    void set_attack_effect_list(const std::vector<attack_effect*>& am_list) {attack_effect_list = am_list;}

    void InitAttackEffect(SDL_Renderer* screen);
    void MakeAttackEffect(SDL_Renderer* des, const int& x_limit, const int& y_limit);

    void DameSkill_1_2();
    void DameSkill_3();
    void DameSkill_4();
    int GetBlood() const {return blood;}

private:
    int map_x_;
    int map_y_;
    int on_ground_;
    Input input_type_;
    int frame_;
    int come_back_time;
    SDL_Rect frame_clip_[FRAME_NUM_32];

    int blood;

    int x_pos_;
    int y_pos_;
    float x_val_;
    float y_val_;
    int width_frame_;
    int height_frame_;
    std::vector<attack_effect*> attack_effect_list;

};

#endif // MONSTER_BOSS__1_H_INCLUDED
