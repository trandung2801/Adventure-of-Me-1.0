#ifndef MONSTER_OBJ_H_INCLUDED
#define MONSTER_OBJ_H_INCLUDED

#include "GeneralData.h"
#include "Base.h"
#include "attack_effect.h"

#define NUM_FRAME_MONSTER 8
#define MONSTER_GRAVITY_SPEED 0.8
#define MONSTER_MAX_FALL_SPEED 10
#define MONSTER_SPEED 3

class MonsterObj : public Base // Lớp monster được kế thừa từ Base
{
public:
    MonsterObj();
    ~MonsterObj();

    enum TypeMove
    {
        DEFAULT_MONTER = 1000,
        MOVE_IN_MONTER = 1001,
        FIGHT_MONTER = 1002,
    };

    void set_x_val(const float& xVal) {x_val_ = xVal;}
    void set_y_val(const float& yVal) {y_val_ = yVal;}

    void set_x_pos(const float& xp) {x_pos_ = xp;}
    void set_y_pos(const float& yp) {y_pos_ = yp;}
    float get_x_pos() const {return x_pos_;}
    float get_y_pos() const {return y_pos_;}
    void SetMapXY(const int& mp_x, const int& mp_y) {map_x_ = mp_x, map_y_ = mp_y;}

    void set_clips();
    bool LoadImg(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    int get_width_frame() const {return width_frame_;}
    int get_height_frame() const {return height_frame_;}
    void DoPlayer(Map& gMap);
    void CheckMap(Map& map_data);
    void InitMonster();

    void set_type_move(const int& typeMove) {type_move_ = typeMove;}
    int GetTypeMove() const {return type_move_;}
    void SetAnimationPos(const int& pos_a, const int& pos_b) {animation_a_ = pos_a, animation_b_ = pos_b;}
    void set_input_left(const int& ipLeft) {input_type_.left_ = ipLeft;};
    void ImpMoveType(SDL_Renderer* screen);
    SDL_Rect GetRectFrame();

    std::vector<attack_effect*>get_attack_effect_list_() const {return m_attack_effect_list_;}
    void set_attack_effect_list(const std::vector<attack_effect*>& attack_effect_list)
    {
        m_attack_effect_list_ = attack_effect_list;
    }
    void InitAttackEffect(attack_effect* p_attack_effect, SDL_Renderer * screen);
    void MakeAttackEffect(SDL_Renderer* screen, const int& x_limit, const int& y_limit);
    void RemoveAttackEffect(const int& idx);

    void DameSkill_1_2();
    void DameSkill_3();
    void DameSkill_4();
    int GetBlood() const {return blood;}
private:
    float x_val_;
    float y_val_;
    float x_pos_;
    float y_pos_;

    int map_x_;
    int map_y_;

    bool on_ground_;
    int come_back_time;

    SDL_Rect frame_clip_[NUM_FRAME_MONSTER];
    int width_frame_;
    int height_frame_;
    int frame_;

    int type_move_;
    int animation_a_;
    int animation_b_;

    Input input_type_;
    int blood;

    std::vector<attack_effect*> m_attack_effect_list_;

};

#endif // MONSTER_OBJ_H_INCLUDED
