#pragma once
struct SnakeSegment {
    int xpos;
    int ypos;
    SnakeSegment* next;
};
enum DIRECTION {
    UP,
    LEFT,
    DOWN,
    RIGHT
};

class Snake  {
    public: 
    static const int cols = 20;
    static const int rows = 20;
    Snake();
    int Gamearea[rows][cols];
    void has_hit_itself(int HeadX, int HeadY); //done
    void game_over();
    void has_hit_wall(); //done
    void print_gamearea(); //done
    void domovement(); //done
    void init_snake(); //done
    void generate_apple(); //done
    void delete_tail(bool skip_deletion); //done
    void add_head(int newx, int newy); //done
    void set_body(int headx, int heady);
    void set_direction_right();
    void set_direction_left();
    void set_direction_up();
    void set_direction_down();
    const int (&get_current_gamearea() const)[rows][cols];
    DIRECTION direction;
    DIRECTION get_direction();

    private:
    SnakeSegment* head = nullptr;
    SnakeSegment* tail = nullptr;
};