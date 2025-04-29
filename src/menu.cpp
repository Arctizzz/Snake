#include "menu.hpp"
#include <iostream>
#include <gdkmm/display.h>
#include <gdkmm/monitor.h>
#include <gdkmm/paintable.h>
#include "main_window.hpp"

#define MARGIN 20

Menu::Menu()
: Gtk::Box(Gtk::Orientation::VERTICAL),
  main_vbox(Gtk::Orientation::VERTICAL),
  start_hbox(Gtk::Orientation::HORIZONTAL),
  lower_hbox(Gtk::Orientation::HORIZONTAL)
{
    main_vbox.set_spacing(20);
    lower_hbox.set_margin(50);
    lower_hbox.set_spacing(20);

    // Start Button
    start.set_label("Start Game");
    start.set_margin(MARGIN);
    start.signal_clicked().connect(sigc::mem_fun(*this, &Menu::start_game));

    // Settings Button
    settings.set_label("Settings");
    settings.set_margin(MARGIN);
    settings.signal_clicked().connect(sigc::mem_fun(*this, &Menu::open_settings));
    settings.set_margin_start(250);

    // Exit Button
    exit.set_label("Exit Game");
    exit.set_margin(MARGIN);
    exit.signal_clicked().connect(sigc::mem_fun(*this, &Menu::exit_game));
    exit.set_margin_end(250);

    // Background
    auto file = Gio::File::create_for_path("assets/images/snake_bg1920x1080.png");
    auto texture = Gdk::Texture::create_from_file(file);
    background.set_paintable(texture);
    background.set_can_shrink(false);
    background.set_content_fit(Gtk::ContentFit::COVER);

    // Layout
    start_hbox.append(start);
    lower_hbox.append(settings);
    lower_hbox.append(exit);
    main_vbox.append(start_hbox);
    main_vbox.append(lower_hbox);

    overlay.set_child(background);
    overlay.add_overlay(main_vbox);

    // Apply styling
    auto css = Gtk::CssProvider::create();
    css->load_from_data(R"(
        button.start-button {
            background: rgb(33, 117, 0);
            color: white;
            font-weight: bold;
            border-radius: 10px;
        }
        button.settings-button {
            background: rgb(80, 78, 78);
            color: white;
            font-weight: bold;
            border-radius: 5px;
        }
        button.exit-button {
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
    start.get_style_context()->add_class("start-button");
    settings.get_style_context()->add_class("settings-button");
    exit.get_style_context()->add_class("exit-button");

    // Add overlay to this Menu Box
    append(overlay);

}

void Menu::start_game() {
    std::cout << "Game started!" << std::endl;
    on_start_game.emit();
}

void Menu::open_settings() {
    std::cout << "Settings opened!" << std::endl;
    on_start_game.emit();  // Temporary for now
}

void Menu::exit_game() {
    std::exit(1);
}
void Menu::assemble_menu_layout(int height, int width) {
    int top_margin = std::round(height * 0.15);

    start_hbox.set_halign(Gtk::Align::CENTER);
    lower_hbox.set_halign(Gtk::Align::CENTER);
    lower_hbox.set_homogeneous(true);
    main_vbox.set_margin_top(top_margin);

    int button_width = std::round(width * 0.3);
    int button_height = std::round(height * 0.1);

    start.set_size_request(button_width, button_height);
    settings.set_size_request(button_width / 2, button_height / 2);
    exit.set_size_request(button_width / 2, button_height / 2);
}
