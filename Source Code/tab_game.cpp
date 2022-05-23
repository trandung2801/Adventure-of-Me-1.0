#include "tab_game.h"

Tab_game::Tab_game()
{
    number_ = 0;
}

Tab_game::~Tab_game()
{

}

void Tab_game::AddPos(const int& xp)
{
    pos_list_.push_back(xp);
}

void Tab_game::Init(SDL_Renderer* screen)
{
    LoadImg("Data IMG//main_animation//Walk//1.png", screen);
    number_ = 5;
    if(pos_list_.size() > 0)
    {
        pos_list_.clear();
    }
    AddPos(20);
    AddPos(60);
    AddPos(100);
    AddPos(140);
    AddPos(180);
}

void Tab_game::Show(SDL_Renderer* screen)
{
    for(int i = 0; i< pos_list_.size(); i++)
    {
        rect_.x = pos_list_.at(i);
        rect_.y = 7;
        Render(screen);
    }
}

void Tab_game::Decrease()
{
    number_--;
    pos_list_.pop_back();
}

void Tab_game::InitCrease()
{
    number_++;
    int last_pos = pos_list_.back();
    last_pos += 40;
    pos_list_.push_back(last_pos);
}
