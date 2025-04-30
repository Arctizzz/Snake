#pragma once
struct SnakeSegment {
    int xpos;
    int ypos;
    SnakeSegment* next;
};
enum DIRECTION {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Snake  {
    public: 
    Snake();
    void has_hit_itself(); //done
    void game_over();
    bool has_hit_apple(); //done
    void has_hit_wall(); //done
    void print_gamearea(); //done
    void domovement(); //done
    void init_snake(); //done
    void generate_apple(); //done
    void delete_tail(); //done
    void add_head(int newx, int newy); //done
    DIRECTION direction = RIGHT;
    private:
    SnakeSegment* head = nullptr;
    SnakeSegment* tail = nullptr;
    int SnakeLength = 0;
    static const int cols = 20;
    static const int rows = 20;
    int Gamearea[rows][cols];
};