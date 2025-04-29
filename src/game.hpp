#pragma once
#include <gtkmm.h>

class Game : public Gtk::DrawingArea {
public:
    Game();
    void set_window_size(int width, int height);

private:
void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);
int cols = 20;
int rows = 20;
};