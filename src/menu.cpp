#include "menu.hpp"
#include <iostream>
#include <gdkmm/display.h>
#include <gdkmm/monitor.h>
#include <gdkmm/paintable.h>
#include "main_window.hpp"

#define MARGIN 20
Menu::Menu()
:   main_vbox(Gtk::Orientation::VERTICAL),
    start_hbox(Gtk::Orientation::HORIZONTAL),
    lower_hbox(Gtk::Orientation::HORIZONTAL)
{

    set_title("Snake Game Menu");
    set_default_size(400, 300);
    main_vbox.set_spacing(20);
    lower_hbox.set_margin(50);
    lower_hbox.set_spacing(20);
//  Start Button
    start.set_label("Start Game");
    start.set_margin(MARGIN);
    start.signal_clicked().connect(sigc::mem_fun(*this, &Menu::start_game));
//  Settings button
    settings.set_label("Settings");
    settings.set_margin(MARGIN);
    settings.signal_clicked().connect(sigc::mem_fun(*this, &Menu::open_settings));
    settings.set_margin_start(250);
//  Exit Button
    exit.set_label("Exit Game");
    exit.set_margin(MARGIN);
    exit.signal_clicked().connect(sigc::mem_fun(*this, &Menu::exit_game));
    exit.set_margin_end(250);
//  Add Background to Box and Buttons
    auto file = Gio::File::create_for_path("assets/images/snake_bg1920x1080.png");
    auto texture = Gdk::Texture::create_from_file(file);
    background.set_paintable(texture); 
    background.set_can_shrink(false);
    background.set_content_fit(Gtk::ContentFit::COVER);

// Adding Buttons to Main Box
    start_hbox.append(start);
    lower_hbox.append(settings);
    lower_hbox.append(exit);
    main_vbox.append(start_hbox);
    main_vbox.append(lower_hbox);
//  Overlay
    overlay.set_child(background);
    overlay.add_overlay(main_vbox);
// Button Colors
    auto css = Gtk::CssProvider::create();
    css->load_from_data(R"(
        button.start-button {
            background:rgb(33, 117, 0);
            color: white;
            font-weight: bold;
            border-radius: 10px;
        }
        button.settings-button {
            background:rgb(80, 78, 78);
            color: white;
            font-weight: bold;
            border-radius: 5px;
        }
        button.exit-button {
            background:rgb(192, 25, 13);
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

    set_child(overlay);
    signal_realize().connect(sigc::mem_fun(*this, &Menu::assemble_layout));

}
// Start Game Logic
void Menu::start_game() {
    std::cout << "Game started!" << std::endl;
    on_start_game.emit();
}
// Open Settings Logic
void Menu::open_settings(){
    std::cout << "Settings opened!" << std::endl;
    on_start_game.emit();
}
// Exit Game Logic
void Menu::exit_game(){
    std::exit(1);
}
/*
Debug Logic if necessary
void Menu::Debug(){
    int screen_width;
    int screen_height;

    auto display = Gdk::Display::get_default();
        if (display) {
            auto monitor = display->get_monitor_at_surface(get_surface());
            if (monitor) {
                Gdk::Rectangle geometry;
                monitor->get_geometry(geometry);
                
                screen_width = geometry.get_width();
                screen_height = geometry.get_height();
                std::cout << "Screen size:" << screen_width << "x" << screen_height << std::endl;
            }
        }

}*/
// Assemble Layout Logic 
void Menu::assemble_layout(){
// Grabs Monitor size to dynamically adjust Button positions 

    auto display = Gdk::Display::get_default();
    if (display) {
        auto surface = get_surface();
        auto monitor = display->get_monitor_at_surface(surface);

        if (monitor) {
            Gdk::Rectangle geometry;
            monitor->get_geometry(geometry);
            int screen_width = geometry.get_width();
            int screen_height = geometry.get_height();
            start_hbox.set_halign(Gtk::Align::CENTER);
            lower_hbox.set_halign(Gtk::Align::CENTER);
            lower_hbox.set_homogeneous(true);
            int top_margin = std::round(screen_height*0.15);
            main_vbox.set_margin_top(top_margin);

            int button_width = round(screen_width * 0.3);
            int button_height = round(screen_height * 0.1);
            start.set_size_request(button_width, button_height);
            settings.set_size_request(button_width/2, button_height/2);
            exit.set_size_request(button_width/2, button_height/2);
            
        }
    }
}