#ifndef ATTACK_EFFECT_H_INCLUDED
#define ATTACK_EFFECT_H_INCLUDED

#include "Base.h"
#include "GeneralData.h"


class attack_effect : public Base // Lớp attack effect được kế thừa từ lớp Base
{
public:
    attack_effect();
    ~attack_effect();

    enum AttackEffectDir // status attack effect
    {
        DIR_RIGHT = 20,
        DIR_LEFT = 21,
        DIR_NONE = 22,
        DIR_UP = 23,
        DIR_DOWN = 24,
        DIR_UP_RIGHT = 25,
        DIR_UP_LEFT = 26,
        DIR_DOWN_LEFT = 27,
        DIR_DOWN_RIGHT = 28,
    };

    enum AttackEffectType
    {
        attack_effect_skill_3 = 30,
        attack_effect_skill_4 = 31,
        monster_attack_effect_1 = 32,
        monster_attack_effect_2 = 33,
    };

    void set_x_val(const int& xVal) {x_val_ = xVal;}
    void set_y_val(const int& yVal) {y_val_ = yVal;}
    int get_x_val() const {return x_val_;}
    int get_y_val() const {return y_val_;}

    void set_is_move(const bool& isMove) {is_move_ = isMove;}
    bool get_is_move() const {return is_move_;}

    void set_attack_effect_dir_(const unsigned int& attackDir) {attack_effect_dir_ = attackDir;}
    unsigned int get_attack_effect_dir_() const {return attack_effect_dir_;}

    void set_attack_effect_type(const unsigned int& attackType) {attack_effect_type = attackType;}
    unsigned int get_attack_effect_type() const {return attack_effect_type;}

    void HandleMove(const int& x_border, const int& y_border);
    bool LoadImgAttackEffect(SDL_Renderer* des);
    SDL_Rect GetRectFrame();

private:
    int x_val_;
    int y_val_;
    bool is_move_;
    unsigned int attack_effect_dir_;
    unsigned int attack_effect_type;

};


#endif // ATTACK_EFFECT_H_INCLUDED
