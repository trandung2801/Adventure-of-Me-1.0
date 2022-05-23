
#include "game_map.h"
#include "GeneralData.h"
#include "Base.h"

void GameMap::LoadMap(char* name) // Đọc file
{
    FILE* fp = NULL; // Khái bao con trỏ fp == NULL
    fopen_s(&fp, name, "rb"); // Mở file
    if (fp == NULL) // Nếu đọc không thành công
    {
        return;
    }

    // Khởi tạo vị trí ban đầu ở ô 0 ,0
    game_map_.max_x_ = 0;
    game_map_.max_y_ = 0;

    //Vòng lặp đọc thong tin của map từ file text
    for(int i = 0; i < MAX_MAP_Y; i++)
    {
        for(int j = 0; j < MAX_MAP_X; j++)
        {
            fscanf(fp, "%d", &game_map_.tile[i][j]);//Đọc và lưu vào mảng
            int val = game_map_.tile[i][j]; // Biến val để kiểm tra
            if (val > 0)
            {
                if(j > game_map_.max_x_)
                {
                    game_map_.max_x_ = j;
                }

                if (i > game_map_.max_y_)
                {
                    game_map_.max_y_ = i;
                }
            }
        }
    }


    // 2 vị trí cuối cùng của map
    game_map_.max_x_ = (game_map_.max_x_ + 1) * TILE_SIZE;
    game_map_.max_y_ = (game_map_.max_y_ + 1) * TILE_SIZE;

    // Khởi tạo 2 vị trí ban dầu bằng 0
    game_map_.start_x_ = 0;
    game_map_.start_y_ = 0;

    game_map_.file_name_ = name;
    fclose(fp);

}

void GameMap::LoadTiles(SDL_Renderer* screen) // Hàm để load img cho các chỉ số tương ứng
{
    char file_img[30]; // Độ dài tên file
    FILE* fp = NULL;

    for (int i = 0; i < MAX_TILES; i++) // Load các bức ảnh trong file
    {
        sprintf_s(file_img,"Data IMG//Map 01//map//%d.png", i);

        fopen_s(&fp, file_img, "rb");
        if (fp == NULL) // Nếu tấm ảnh không có đọc tấm tiếp theo
        {
            continue;
        }
        fclose(fp); // Nếu không có thì đóng hàm

        tile_mat[i].LoadImg(file_img, screen); //Load img lên tile
    }
}

void GameMap::DrawMap(SDL_Renderer* screen) // Hàm vẽ map
{
    //
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    int map_x = 0;
    int map_y = 0;

    map_x = game_map_.start_x_/TILE_SIZE; // Vị trí thứ bao nhiêu theo Ox(Lấy phần nguyên)
    x1 = (game_map_.start_x_%TILE_SIZE)*-1;
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

    map_y = game_map_.start_y_/TILE_SIZE;//Vị trí thứ bao nhiêu theo Oy(Lấy phần nguyên)
    y1 = (game_map_.start_y_%TILE_SIZE)*-1;
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

    for (int i = y1; i < y2; i += TILE_SIZE)
    {
        map_x = game_map_.start_x_/TILE_SIZE;
        for (int j = x1; j< x2; j += TILE_SIZE)
        {
            int val = game_map_.tile[map_y][map_x];//Vị trí ô thứ bao nhiêu
            if (val > 0)
            {
                tile_mat[val].SetRect(j, i);
                tile_mat[val].Render(screen);
            }
            map_x++;
        }
        map_y++;
    }
}
