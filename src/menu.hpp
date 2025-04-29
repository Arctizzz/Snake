#pragma once
#include <gtkmm.h>
#include <sigc++/signal.h>

class Menu : public Gtk::Box {
public:
    Menu();
    sigc::signal<void()> on_start_game;
    void assemble_menu_layout(int height, int width);

private:
    Gtk::Box main_vbox;
    Gtk::Box start_hbox;
    Gtk::Box lower_hbox;
    Gtk::Button start;
    Gtk::Button settings;
    Gtk::Button exit;
    Gtk::Overlay overlay;
    Gtk::Picture background;

    void start_game();
    void open_settings();
    void exit_game();
    
};
