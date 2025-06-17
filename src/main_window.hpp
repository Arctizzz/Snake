#pragma once
#include <gtkmm.h>
#include "menu.hpp"
#include "game.hpp"
#include "snake.hpp"
#include "settings.hpp"
#include <utility>
class AppWindow : public Gtk::Window {
public:
    AppWindow();
    std::pair<int, int> get_window_size();
    bool movement_done;
private:
    Glib::RefPtr<Gtk::EventControllerKey> key_controller;
    Gtk::Stack stack;
    Menu menu;
    Game game;
    Snake snake;
    Settings settings;
    void layout_functions();
    void on_start_game();
    void on_open_settings();
    bool on_key_press(guint keyval, guint keycode, Gdk::ModifierType state);
    bool on_close();
    bool on_game_tick();
};
