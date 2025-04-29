#pragma once
#include <gtkmm.h>
#include "menu.hpp"
#include "game.hpp"
#include <utility>

class AppWindow : public Gtk::Window {
public:
    AppWindow();
    std::pair<int, int> get_window_size();

private:
    Glib::RefPtr<Gtk::EventControllerKey> key_controller;
    Gtk::Stack stack;
    Menu menu;
    Game game;
    void layout_functions();
    void on_start_game();
    bool on_key_press(guint keyval, guint keycode, Gdk::ModifierType state);
    bool on_close();
};
