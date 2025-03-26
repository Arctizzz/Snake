#pragma once
#include "game.hpp"
#include "menu.hpp"
#include <gtkmm.h>

class AppWindow : public Gtk::Window {
public:
    AppWindow();

private:
    Gtk::Stack stack;
    Menu menu;
    Game game;

    void on_start_game();
};