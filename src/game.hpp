#pragma once
#include <gtkmm.h>
#include "snake.hpp"

class Game : public Gtk::DrawingArea {
public:
Snake snake;
    Game();
    void set_window_size(int width, int height);
    void tick();

private:
void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);
int cols = 20;
int rows = 20;
};