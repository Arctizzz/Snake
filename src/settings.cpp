#include "settings.hpp"
#include <iostream>
#include <gdkmm/display.h>
#include <gdkmm/monitor.h>
#include <gdkmm/paintable.h>
#include "main_window.hpp"

#define MARGIN 20

Settings::Settings()
: Gtk::Box(Gtk::Orientation::VERTICAL),
  main_vbox(Gtk::Orientation::VERTICAL),
  start_hbox(Gtk::Orientation::HORIZONTAL),
  lower_hbox(Gtk::Orientation::HORIZONTAL)
{
    main_vbox.set_spacing(20);
    lower_hbox.set_margin(50);
    lower_hbox.set_spacing(20);

    // Start Button
    board_size.set_label("Board Size: " + std::to_string(board_size_value));
    board_size.set_margin(MARGIN);
    board_size.signal_clicked().connect(sigc::mem_fun(*this, &Settings::cycle_board_size));

    // Settings Button
    game_speed.set_label("Game Speed: " + std::to_string(game_speed_value));
    game_speed.set_margin(MARGIN);
    game_speed.signal_clicked().connect(sigc::mem_fun(*this, &Settings::cycle_game_speed));
    game_speed.set_margin_start(250);

    // Exit Button
    back.set_label("Return");
    back.set_margin(MARGIN);
    back.signal_clicked().connect(sigc::mem_fun(*this, &Settings::return_to_menu));
    back.set_margin_end(250);
    // Layout
    start_hbox.append(back);
    lower_hbox.append(game_speed);
    lower_hbox.append(board_size);
    main_vbox.append(start_hbox);
    main_vbox.append(lower_hbox);
    // Apply styling
    auto css = Gtk::CssProvider::create();
    css->load_from_data(R"(
        button.board_size-button {
            background: rgb(194, 202, 78);
            color: white;
            font-weight: bold;
            border-radius: 10px;
        }
        button.game_speed-button {
            background: rgb(22, 161, 138);
            color: white;
            font-weight: bold;
            border-radius: 5px;
        }
        button.back-button {
            background: rgb(192, 25, 13);
            color: white;
            font-weight: bold;
            border-radius: 5px;
        }
        button:hover {
            opacity: 0.9;
        }
    )");

    auto display = Gdk::Display::get_default();
    Gtk::StyleContext::add_provider_for_display(display, css, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    start.get_style_context()->add_class("board_size-button");
    settings.get_style_context()->add_class("game_speed-button");
    exit.get_style_context()->add_class("back-button");

    // Add overlay to this Menu Box
    append(overlay);

}

void Settings::return_to_menu() {
    std::cout << "Game started!" << std::endl;
    on_return_to_menu.emit();
}

void Settings::open_settings() {
    std::cout << "Settings opened!" << std::endl;
    on_open_settings.emit();  
}
void Settings::assemble_menu_layout(int height, int width) {
    int top_margin = std::round(height * 0.15);

    start_hbox.set_halign(Gtk::Align::CENTER);
    lower_hbox.set_halign(Gtk::Align::CENTER);
    lower_hbox.set_homogeneous(true);
    main_vbox.set_margin_top(top_margin);

    int button_width = std::round(width * 0.3);
    int button_height = std::round(height * 0.1);

    board_size.set_size_request(button_width, button_height);
    game_speed.set_size_request(button_width / 2, button_height / 2);
    back.set_size_request(button_width / 2, button_height / 2);
}

int get_board_size() {
    return board_size_value;
}
int get_game_speed() {
    return game_speed_value;
}
int set_board_size(int board_size, int new_size) {
    board_size = new_size;
    return board_size;
}
int set_game_speed(int game_speed, int new_speed) {
    game_speed = new_speed;
    return game_speed;
}
