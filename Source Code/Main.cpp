
#include "GeneralData.h"
#include "Base.h"
#include "game_map.h"
#include "main_obj.h"
#include "FPS.h"
#include "monster_obj.h"
#include "attack_effect.h"
#include "explosion_obj.h"
#include "Text_obj.h"
#include "tab_game.h"
#include "Geometric.h"
#include "Monster_boss.h"

#define NumberMonster 50

Base g_background;
TTF_Font* font_time = NULL;
TTF_Font* font_menu = NULL;

bool InitData() // Khởi tạo thông số môi trường cho SDL
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO); // Thiết lập môi trường ban đầu cho SDL
    if (ret < 0)
        return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"); // Thiết lập tỉ lệ và chất lượng

    g_window = SDL_CreateWindow("Adventure of Me", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN); // Tạo của sổ windown cho game
    if(g_window == NULL)
    {
        success = false;
    }
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED); // Gán g_screen để tạo màn hình windown
        if(g_screen == NULL)
            success = false;
        else
        {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR ,RENDER_DRAW_COLOR); // Tiến hành vẽ ra màn hình windown
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) && imgFlags))
                success = false;
        }

        if(TTF_Init() == -1)
        {
            success = false;
        }

        font_time = TTF_OpenFont("Font//dlxfont_.ttf", 15);
        if(font_time == NULL)
        {
            success = false;
        }

        font_menu = TTF_OpenFont("Font//dlxfont_.ttf", 50);
        if(font_menu == NULL)
        {
            success = false;
        }

        if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
        {
            success = false;
        }

//Read sound
        g_sound_menu[0] = Mix_LoadWAV("Sound//Menu Game//Menu.wav");
        g_sound_menu[1] = Mix_LoadWAV("Sound//Menu Game//You-win.wav");
        g_sound_menu[2] = Mix_LoadWAV("Sound//Menu Game//Game-Over.wav");
        g_sound_menu[3] = Mix_LoadWAV("Sound//Menu Game//Backgound.wav");

        g_sound_main_attack[0] = Mix_LoadWAV("Sound//Attack Effect//Skill 12.wav");
        g_sound_main_attack[1] = Mix_LoadWAV("Sound//Attack Effect//Skill 3.wav");
        g_sound_main_attack[2] = Mix_LoadWAV("Sound//Attack Effect//Skill 4.wav");

        g_sound_main[0] = Mix_LoadWAV("Sound//Main//Walk.wav");

    }

    return success;
}

bool LoadBackground()
{
    bool ret = g_background.LoadImg("Data IMG//Map 01//Background//BackGround.png", g_screen);
    if ( ret == false)
        return false;

    return true;
}

void close() // Hàm giải phóng các đối tượng
{
    g_background.Release();

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    SDL_Quit();
}

std::vector<MonsterObj*> MakeMonsterList() // Khởi tạo các monster
{
    std::vector<MonsterObj*> list_monster;

    MonsterObj* dynamic_monster = new MonsterObj[NumberMonster];
    for(int i = 0; i < NumberMonster; i++)
    {
        MonsterObj* p_monster = (dynamic_monster + i);
        if(p_monster != NULL)
        {
            p_monster->LoadImg("Data IMG//monster_animation//monster 1 right.png", g_screen);
            p_monster->set_clips();
            p_monster->set_type_move(MonsterObj::MOVE_IN_MONTER);
            p_monster->set_x_pos(500 + i*500);
            p_monster->set_y_pos(200);

            int pos1 = p_monster->get_x_pos() - 60;
            int pos2 = p_monster->get_x_pos() + 60;

            p_monster->SetAnimationPos(pos1,pos2);
            p_monster->set_input_left(1);

            list_monster.push_back(p_monster);
        }
    }
    return list_monster;
}

int main(int argc, char* argv[])
{
    FPS fps_timer; // Khởi tạo thông số FPS cho game
    bool is_quit = false; // Khởi  tạm biến kết thúc

    if(InitData() == false) // Nếu khởi tạo môi trường thất bại
        return -1;

    //Make menu game
    Mix_PlayChannel(-1, g_sound_menu[0], 100);
    int ret_menu = SDLGenaralData::ShowMenu(g_screen, font_menu, "Play Game", "Exit", "Data IMG//Map 01//Background//BackGround1.png");
    if (ret_menu == 1)
    {
        is_quit = true;
    }
    else
    {
        Mix_FreeChunk(g_sound_menu[0]);
        Mix_PlayChannel(-1, g_sound_menu[3], 100);
    }

    if(LoadBackground() == false)
        return -1;
again:

    // Khai báo game map
    GameMap game_map;
    game_map.LoadMap("Data IMG//Map 01//Map//map01.txt");
    game_map.LoadTiles(g_screen);

    // Khai báo main
    main_obj p_player;
    p_player.LoadImg("Data IMG//main_animation//Walk//default right.png", g_screen);
    p_player.set_clips();

    // Khai báo tab game
    Tab_game tab_game;
    tab_game.Init(g_screen);

    std::vector<MonsterObj*> monster_list = MakeMonsterList();

    //Monster Boss
    MonsterBoss MonsterBoss_1;
    MonsterBoss_1.LoadImg("Data IMG//monster_animation//boss.png", g_screen);
    MonsterBoss_1.set_clips();
    MonsterBoss_1.set_xpos(28600);
    MonsterBoss_1.set_ypos(10);


    ExplosionObj exp_monster;
    bool tRect = exp_monster.LoadImg("Data IMG//monster_animation//monster.png", g_screen);
    if(!tRect) return -1;
    exp_monster.set_clip();

    //Time Text
    TextObj time_game;
    time_game.SetColor(TextObj::WHITE_TEXT);

    //Score
    TextObj score_game;
    score_game.SetColor(TextObj::WHITE_TEXT);
    int score_value = 0;

    //Money
    TextObj money_game;
    money_game.SetColor(TextObj::WHITE_TEXT);

    //Blood main
    TextObj blood_main_game;
    blood_main_game.SetColor(TextObj::RED_TEXT);

    //CooldownE
    TextObj cooldownE_game;
    cooldownE_game.SetColor(TextObj::WHITE_TEXT);

    //CooldownR
    TextObj cooldownR_game;
    cooldownR_game.SetColor(TextObj::WHITE_TEXT);

    int num_die = 0; // Khởi tạo số lần die
    while(!is_quit) // Nếu biến kết thúc false => vòng lặp vô tận
    {
        fps_timer.start();
        while(SDL_PollEvent(&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT)
            {
                is_quit = true;
            }

            p_player.HandeInputAction(g_event, g_screen, g_sound_main_attack, g_sound_main); // Các sự kiện đang được nhập từ bàn phím
        }

        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR); // Render ra ngoài màn hình
        SDL_RenderClear(g_screen); // Xóa màn hình đi

        g_background.Render(g_screen, NULL);
        Map map_data = game_map.getMap();

        // Main
        p_player.HandleAttackEffect(g_screen);// Tạo attack effect cho main
        p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
        p_player.DoPlayer(map_data);
        p_player.Show(g_screen); // Show main ra screen
        SDL_Rect rect_player = p_player.GetRectFrame();

        // Vẽ các trạng thái của map
        game_map.SetMap(map_data);
        game_map.DrawMap(g_screen);

        //Draw Geometric
        GeometricFormat rectangle_size(0, 0, SCREEN_WIDTH, 40);
        ColorData color_data(0, 0, 0);
        Geometric::RenderRectangle(rectangle_size, color_data, g_screen);

        GeometricFormat outline_size(1, 1, SCREEN_WIDTH - 1, 38);
        ColorData color_data_2(255, 255, 255);

        Geometric::RenderOutline(outline_size, color_data_2, g_screen);

        // Show tab game
        tab_game.Show(g_screen);
        // Monster
        for(int i = 0; i < monster_list.size(); i++)
        {
            MonsterObj* p_monster = monster_list.at(i);
            if(p_monster != NULL)
            {
                p_monster->SetMapXY(map_data.start_x_, map_data.start_y_);
                p_monster->ImpMoveType(g_screen);
                p_monster->DoPlayer(map_data);
                p_monster->Show(g_screen);

                // va cham giua main và quái
                SDL_Rect rect_monster = p_monster->GetRectFrame();
                bool bCol_2 = SDLGenaralData::CheckCollision(rect_player, rect_monster);
                if(bCol_2 )
                {
                    p_monster->set_type_move(MonsterObj::FIGHT_MONTER);
                    p_monster->ImpMoveType(g_screen);
                    p_monster->DoPlayer(map_data);
                    p_monster->Show(g_screen);
                    p_player.DameMonster1();
                    if(p_player.GetStatus() == SKILL_1_LEFT || p_player.GetStatus() == SKILL_1_RIGHT ||
                       p_player.GetStatus() == SKILL_2_LEFT || p_player.GetStatus() == SKILL_2_RIGHT)
                    {
                        p_monster->DameSkill_1_2();
                    }
                    if(p_monster->GetBlood() <= 0)
                        {
                            score_value += 10;
                            p_monster->Release();
                            monster_list.erase(monster_list.begin() + i);
                        }
                    int blood_main_now = p_player.GetBlood();
                    if(blood_main_now <= 0)
                    {
                        num_die ++;
                        if(num_die <= 5)
                        {
                            p_player.SetRect(0, 0);
                            p_player.set_comeback_time(60);
                            SDL_Delay(1000);
                            tab_game.Decrease();
                            tab_game.Render(g_screen);
                            p_player.reset_blood();
                            continue;
                        }
                        if(num_die > 5)
                        {
                            Sleep(500);
                            Mix_FreeChunk(g_sound_menu[3]);
                            Mix_PlayChannel(-1, g_sound_menu[2], 100);
                            int ret_menu = SDLGenaralData::ShowMenu(g_screen, font_menu,
                                                                   "Player Again", "Exit",
                                                                   "Data IMG//Map 01//Background//BackGround2.png");

                            if (ret_menu == 1)
                            {
                                is_quit = true;
                                continue;
                            }
                            else
                            {
                                is_quit = false;
                                Mix_FreeChunk(g_sound_menu[2]);
                                goto again;

                            }
                        }
                    }
                }
            }
        }

        // Attack Effect
        std::vector<attack_effect*>attack_effect_arr = p_player.get_attack_effect_list();
        for(int j = 0; j < attack_effect_arr.size(); j++)
        {
            attack_effect* p_attack_effect = attack_effect_arr.at(j);
            if(p_attack_effect != NULL)
            {
                for (int a = 0; a < monster_list.size(); a++)
                {
                    MonsterObj* obj_monster = monster_list.at(a);
                    if(obj_monster != NULL)
                    {
                        SDL_Rect rect_monster = obj_monster->GetRectFrame();
                        SDL_Rect rect_attack_effect = p_attack_effect->GetRectFrame();
                        // Va chạm monster vs attack effect của nhân vật
                        bool bCol = SDLGenaralData::CheckCollision(rect_attack_effect, rect_monster);

                        if(bCol)
                        {
                            obj_monster->set_type_move(MonsterObj::FIGHT_MONTER);
                            obj_monster->ImpMoveType(g_screen);
                            obj_monster->DoPlayer(map_data);
                            obj_monster->Show(g_screen);
                            if(p_player.GetStatus() == SKILL_3_LEFT || p_player.GetStatus() == SKILL_3_RIGHT)
                            {
                                obj_monster->DameSkill_3();
                            }
                            if(p_player.GetStatus() == SKILL_4_LEFT || p_player.GetStatus() == SKILL_4_RIGHT)
                            {
                                obj_monster->DameSkill_4();
                            }
                            p_player.RemoveAttackEffect(j);
                            if(obj_monster->GetBlood() <= 0)
                            {
                                obj_monster->Release();
                                monster_list.erase(monster_list.begin() + a);
                                score_value += 10;
                            }
                        }
                    }
                }
            }
        }

        //Show game time
        std::string str_time ="Time: ";
        Uint32 time_val = SDL_GetTicks()/1000;
        int val_time = 0 + time_val;

        std::string str_val = std::to_string(val_time);
        str_time += str_val;

        time_game.SetText(str_time);
        time_game.LoadFromRenderText(font_time, g_screen);
        time_game.RenderText(g_screen, SCREEN_WIDTH - 150, 15);

        //Show score
        std::string val_str_score = std::to_string(score_value);
        std::string strScore("Score: ");
        strScore += val_str_score;

        score_game.SetText(strScore);
        score_game.LoadFromRenderText(font_time, g_screen);
        score_game.RenderText(g_screen, SCREEN_WIDTH - 550, 15);

        // Show money
        int money_count = p_player.GetMoneyCount();
        std::string money_str = std::to_string(money_count);
        std::string Strmoney("Money:");
        Strmoney += money_str;

        money_game.SetText(Strmoney);
        money_game.LoadFromRenderText(font_time, g_screen);
        money_game.RenderText(g_screen, SCREEN_WIDTH - 320, 15);

        //Show Blood main
        int blood_main = p_player.GetBlood();
        std::string blood_main_str = std::to_string(blood_main);
        std::string Strbool("Blood:");
        Strbool += blood_main_str;

        blood_main_game.SetText(Strbool);
        blood_main_game.LoadFromRenderText(font_time, g_screen);
        blood_main_game.RenderText(g_screen, 320, 15);

        //Show CooldownE
        int cooldownE = p_player.GetCooldownE();
        std::string cooldownE_game_str = std::to_string(cooldownE);
        std::string StrcooldownE("E:");
        StrcooldownE += cooldownE_game_str;

        cooldownE_game.SetText(StrcooldownE);
        cooldownE_game.LoadFromRenderText(font_time, g_screen);
        cooldownE_game.RenderText(g_screen, 500, 15);

        // Show CooldownR
        int cooldownR = p_player.GetCooldownR();
        std::string cooldownR_game_str = std::to_string(cooldownR);
        std::string StrcooldownR("R:");
        StrcooldownR += cooldownR_game_str;

        cooldownR_game.SetText(StrcooldownR);
        cooldownR_game.LoadFromRenderText(font_time, g_screen);
        cooldownR_game.RenderText(g_screen, 600, 15);



        if(score_value >= 490)
        {
                //Show Boss
            MonsterBoss_1.SetMapXY(map_data.start_x_, map_data.start_y_);
            MonsterBoss_1.DoPlayer(map_data);
            MonsterBoss_1.MakeAttackEffect(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
            MonsterBoss_1.Show(g_screen);

            SDL_Rect rect_monster_boss = MonsterBoss_1.GetRectFrame();

            bool bCol_1 = false;
            std::vector<attack_effect*> tAttack_Effect_list = MonsterBoss_1.get_attack_effect_list();
            for(int jj = 0; jj < tAttack_Effect_list.size(); jj ++)
            {
                attack_effect* pt_attack_effect = tAttack_Effect_list.at(jj);
                SDL_Rect rect_attack_effect = pt_attack_effect->GetRectFrame();
                if(pt_attack_effect)
                {
                    bCol_1 = SDLGenaralData::CheckCollision(rect_attack_effect, rect_player);
                    if(bCol_1)
                    {
                        p_player.DameMonsterBoss2();
                        int blood_main_now = p_player.GetBlood();
                        if(blood_main_now <= 0)
                        {
                            num_die ++;
                            if(num_die <= 5)
                            {
                                p_player.SetRect(0, 0);
                                p_player.set_comeback_time(60);
                                SDL_Delay(1000);
                                tab_game.Decrease();
                                tab_game.Render(g_screen);
                                p_player.reset_blood();
                                continue;
                            }
                            if(num_die > 5)
                            {
                                Sleep(500);
                                Mix_FreeChunk(g_sound_menu[3]);
                                Mix_PlayChannel(-1, g_sound_menu[2], 100);
                                int ret_menu = SDLGenaralData::ShowMenu(g_screen, font_menu,
                                                                       "Player Again", "Exit",
                                                                       "Data IMG//Map 01//Background//BackGround2.png");
                                if (ret_menu == 1)
                                {
                                    is_quit = true;
                                    continue;
                                }
                                else
                                {
                                    is_quit = false;
                                    Mix_FreeChunk(g_sound_menu[2]);
                                    goto again;
                                }
                            }
                        }
                    break;
                    }
                }
            }

            bool bCol_2 = SDLGenaralData::CheckCollision(rect_player, rect_monster_boss);
            if(bCol_2 )
            {
                p_player.DameMonsterBoss1();
                if(p_player.GetStatus() == SKILL_1_LEFT || p_player.GetStatus() == SKILL_1_RIGHT ||
                p_player.GetStatus() == SKILL_2_LEFT || p_player.GetStatus() == SKILL_2_RIGHT)
                {
                    MonsterBoss_1.DameSkill_1_2();
                }
                if(MonsterBoss_1.GetBlood() <= 0)
                {
                    score_value += 200;
                    Sleep(500);
                    Mix_FreeChunk(g_sound_menu[3]);
                    Mix_PlayChannel(-1, g_sound_menu[1], 100);
                    int ret_menu = SDLGenaralData::ShowMenu(g_screen, font_menu,
                                                            "Player Again", "Exit",
                                                            "Data IMG//Map 01//Background//BackGround3.png");
                    if (ret_menu == 1)
                    {
                        is_quit = true;
                        continue;
                    }
                    else
                    {
                        is_quit = false;
                        Mix_FreeChunk(g_sound_menu[1]);
                        goto again;
                    }
                }
                int blood_main_now = p_player.GetBlood();
                if(blood_main_now <= 0)
                {
                    num_die ++;
                    if(num_die <= 5)
                    {
                        p_player.SetRect(0, 0);
                        p_player.set_comeback_time(60);
                        SDL_Delay(1000);
                        tab_game.Decrease();
                        tab_game.Render(g_screen);
                        p_player.reset_blood();
                        continue;
                    }
                    if(num_die > 5)
                    {
                        Sleep(500);
                        Mix_FreeChunk(g_sound_menu[3]);
                        Mix_PlayChannel(-1, g_sound_menu[2], 100);
                        int ret_menu = SDLGenaralData::ShowMenu(g_screen, font_menu,
                                                                "Player Again", "Exit",
                                                                "Data IMG//Map 01//Background//BackGround2.png");
                        if (ret_menu == 1)
                        {
                            is_quit = true;
                            continue;
                        }
                        else
                        {
                            is_quit = false;
                            Mix_FreeChunk(g_sound_menu[2]);
                            goto again;
                        }
                    }
                }
            }

            for(int j = 0; j < attack_effect_arr.size(); j++)
            {
                attack_effect* p_attack_effect = attack_effect_arr.at(j);
                if(p_attack_effect != NULL)
                {
                    SDL_Rect rect_attack_effect = p_attack_effect->GetRectFrame();
                    // Va chạm monster vs attack effect của nhân vật
                    bool bCol = SDLGenaralData::CheckCollision(rect_attack_effect, rect_monster_boss);

                    if(bCol)
                    {

                        if(p_player.GetStatus() == SKILL_3_LEFT || p_player.GetStatus() == SKILL_3_RIGHT)
                        {
                            MonsterBoss_1.DameSkill_3();
                        }
                        if(p_player.GetStatus() == SKILL_4_LEFT || p_player.GetStatus() == SKILL_4_RIGHT)
                        {
                            MonsterBoss_1.DameSkill_4();
                        }
                        p_player.RemoveAttackEffect(j);
                        if(MonsterBoss_1.GetBlood() <= 0)
                        {
                            score_value += 200;
                            Sleep(500);
                            Mix_FreeChunk(g_sound_menu[3]);
                            Mix_PlayChannel(-1, g_sound_menu[1], 100);
                            int ret_menu = SDLGenaralData::ShowMenu(g_screen, font_menu,
                                                                    "Player Again", "Exit",
                                                                    "Data IMG//Map 01//Background//BackGround3.png");
                            if (ret_menu == 1)
                            {
                                is_quit = true;
                                continue;
                            }
                            else
                            {
                                is_quit = false;
                                Mix_FreeChunk(g_sound_menu[1]);
                                goto again;
                            }
                        }
                    }
                }
            }
        }

        // Update lại màn hình
        SDL_RenderPresent(g_screen);

        int real_imp_time = fps_timer.get_ticks();
        int time_one_frame = 1000/FRAME_PER_SECOND; //ms

        if (real_imp_time < time_one_frame)
        {
            int delay_time = time_one_frame - real_imp_time;
            if(delay_time >= 0)
                SDL_Delay(delay_time);
        }
    }

    for (int i = 0; i < monster_list.size(); i++ )
    {
        MonsterObj* p_monster = monster_list.at(i);
        if(p_monster)
        {
            p_monster->Release();
            p_monster = NULL;
        }

    monster_list.clear();
    }

    close();
    return 0;
}
