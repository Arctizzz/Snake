#include "game.hpp"
#include <iostream>
#include <cmath> 
#include <main_window.hpp>
#include "snake.hpp"
int screen_width = 0;
int screen_height = 0;
    Game::Game() {
        snake.init_snake();
        set_draw_func(sigc::mem_fun(*this, &Game::on_draw));
        set_window_size(screen_width, screen_height);

    }
    
    void Game::on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height) {
        auto style_context = get_style_context();
        style_context->render_background(cr, 0, 0, screen_height, screen_height);
        cr->set_source_rgb(0.2, 0.4, 0.2);
        cr->rectangle(0, 0, screen_width, screen_height);
        cr->fill();
        double cell_width = static_cast<double>(screen_height) / cols;
        double cell_height = static_cast<double>(screen_height) / rows;

        for(int row = 0; row < rows; row++){
            for(int col = 0; col < cols; col++){
                bool is_light = (row + col) % 2 == 0;
                const int (&snake_tiles)[Snake::rows][Snake::cols] = snake.get_current_gamearea();
                if(snake_tiles[row][col] == 3 or snake_tiles[row][col] == 2)
                    cr->set_source_rgb(0, 0, 0);
                else if(snake_tiles[row][col] == 1)
                    cr->set_source_rgb(255.0, 0, 0);
                else if(is_light)
                    cr->set_source_rgb(170.0/255, 215.0/255, 81.0/255);
                else
                    cr->set_source_rgb(162.0/255, 209.0/255, 73.0/255);

                double x = col * cell_width;
                double y = row * cell_height;
                cr->rectangle(x, y, cell_width, cell_height);
                cr->fill();
            }
    }
cr->set_source_rgb(0.4, 0.4, 0.4); 

cr->set_line_width(0.7);

for (int col = 0; col <= cols; ++col) {
    double x = col * cell_width;
    cr->move_to(x, 0);
    cr->line_to(x, screen_height);
}

for (int row = 0; row <= rows; ++row) {
    double y = row * cell_height;
    cr->move_to(0, y);
    cr->line_to(screen_width, y);
}

cr->stroke(); 

}
void Game::set_window_size(int width, int height){
        screen_width = width;
        screen_height = height;
    }

void Game::tick() {
    snake.domovement();
}
void Game::set_direction(DIRECTION dir) {
    std::cout << "Direction set to: " << dir << std::endl;
    switch (dir) {
        case UP:    snake.set_direction_up(); break;
        case DOWN:  snake.set_direction_down(); break;
        case LEFT:  snake.set_direction_left(); break;
        case RIGHT: snake.set_direction_right(); break;
    }
}
