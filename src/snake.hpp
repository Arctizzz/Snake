#pragma once

/*#include <gtkmm.h>
#include <stdio.h>
#include <math.h>
*/
class Snake  {
    public: 
    Snake();
    bool has_hit_itself();
    void increase_snake_length();
    void game_over();
    void spawn_random_apple();
    bool has_hit_apple();
    bool has_hit_wall();
    void print_gamearea();

    private:
    int SnakeLength = 0;
    static const int cols = 20;
    static const int rows = 20;
    int Gamearea[rows][cols];

};