#pragma once
#include <gtkmm.h>
enum GAME_SPEED {
    SLOW = 750,
    STANDARD = 500,
    FAST = 250,
    SONIC = 100
};
enum BOARD_SIZE {
    TINY = 5,
    SMALL = 10,
    MEDIUM = 20,
    BIG = 30,
    GIANT = 50
};
class Settings : public Gtk::Box {
    public:
    Settings();
    sigc::signal<void()> on_return_to_menu;
    sigc::signal<void()> on_open_settings;
    int get_board_size(int board_size, int new_size);
    int get_game_speed(int game_speed, int new_speed);
    int set_board_size();
    int set_game_speed();
    int cycle_board_size();
    int cycle_game_speed();
    void return_to_menu();
    void open_settings();
    int board_size_value;
    int game_speed_value;
    void assemble_menu_layout(int height, int width);
    private: 
    Gtk::Box main_vbox;
    Gtk::Box start_hbox;
    Gtk::Box lower_hbox;
    Gtk::Button board_size;
    Gtk::Button game_speed;
    Gtk::Button back;
};