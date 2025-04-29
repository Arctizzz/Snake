#include "game.hpp"
#include <iostream>
#include <cmath> 
#include <main_window.hpp>
int screen_width = 0;
int screen_height = 0;
    Game::Game() {
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

                if(is_light)
                    cr->set_source_rgb(0/255.0, 204.0/255.0, 86.0/255.0);
                else
                    cr->set_source_rgb(0, 128.0/255.0, 0);

                double x = col * cell_width;
                double y = row * cell_height;
                cr->rectangle(x, y, cell_width, cell_height);
                cr->fill();
            }
    }
}
    void Game::set_window_size(int width, int height){
        screen_width = width;
        screen_height = height;
    }
    

