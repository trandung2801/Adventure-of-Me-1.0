#ifndef FPS_H_INCLUDED
#define FPS_H_INCLUDED

class FPS // Lớp FPS điều chỉnh tốc độ game
{
public:
    FPS();
    ~FPS();

    void start();
    void stop();
    void paused();
    void unpaused();

    int get_ticks();

    bool is_started();
    bool is_paused();

private:
    int start_tick_;
    int paused_tick_;

    bool is_paused_;
    bool is_started_;

};


#endif // FPS_H_INCLUDED
