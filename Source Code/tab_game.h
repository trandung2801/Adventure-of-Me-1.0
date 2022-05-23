#ifndef TAB_GAME_H_INCLUDED
#define TAB_GAME_H_INCLUDED

#include "Base.h"
#include "GeneralData.h"

class Tab_game : public Base // Lớp show các text trong game
{
public:
    Tab_game();
    ~Tab_game();

    void SetNum(const int& num) {number_ = num;}
    void AddPos(const int& xPos);
    void Show(SDL_Renderer* screen);
    void Init(SDL_Renderer* screen);

    void InitCrease();
    void Decrease();

private:
    int number_;
    std::vector<int> pos_list_;
};

#endif // TAB_GAME_H_INCLUDED
