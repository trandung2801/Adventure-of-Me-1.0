#include "FPS.h"
#include "GeneralData.h"

FPS::FPS()
{
    start_tick_ = 0;
    paused_tick_ = 0;
    is_paused_ = false;
    is_started_ = false;
}

FPS::~FPS()
{

}

void FPS::start()
{
    is_started_ = true;
    is_paused_ = false;
    start_tick_ = SDL_GetTicks();
}

void FPS::stop()
{
    is_paused_ = false;
    is_started_ = false;
}

void FPS::paused()
{
    if(is_started_ == true && is_paused_ == false)
    {
        is_paused_ = true;
        paused_tick_ = SDL_GetTicks() - start_tick_;
    }
}

void FPS::unpaused()
{
    if(is_paused_ == true)
    {
        is_paused_ = false;
        start_tick_ = SDL_GetTicks() - paused_tick_;
        paused_tick_ = 0;
    }
}

int FPS::get_ticks()
{
   if(is_started_ == true)
   {
       if(is_paused_ == true)
       {
           return paused_tick_;
       }
       else
       {
           return SDL_GetTicks() - start_tick_;
       }
   }
   return 0;
}

bool FPS:: is_started()
{
    return is_started_;
}

bool FPS::is_paused()
{
    return is_paused_;
}

