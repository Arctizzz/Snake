#include "main_window.hpp"
#include "menu.hpp"
#include "game.hpp"
#include <iostream>
#include <gdk/gdkkeysyms.h>
#include <gtkmm/applicationwindow.h>
AppWindow::AppWindow()
: stack(), menu(), game() {
    set_title("Snake Game");
    set_default_size(500, 500);
    set_resizable(true);
    set_focusable(true);
    set_can_focus(true);
    key_controller = Gtk::EventControllerKey::create();
    add_controller(key_controller);

    stack.set_transition_type(Gtk::StackTransitionType::NONE);
    stack.set_transition_duration(500);
    stack.add(menu, "menu");
    stack.add(game, "game");

    set_child(stack);
    signal_realize().connect(sigc::mem_fun(*this, &AppWindow::layout_functions));
    key_controller->signal_key_pressed().connect(sigc::mem_fun(*this, &AppWindow::on_key_press), false);
    menu.on_start_game.connect(sigc::mem_fun(*this, &AppWindow::on_start_game));
    stack.set_visible_child("menu");
    signal_close_request().connect(sigc::mem_fun(*this, &AppWindow::on_close), false);
}

void AppWindow::on_start_game() {
    stack.set_visible_child("game");
    Glib::signal_timeout().connect(
        sigc::mem_fun(*this, &AppWindow::on_game_tick),
        5000
    );
}
std::pair<int, int> AppWindow::get_window_size() {
    int width, height;
    auto display = Gdk::Display::get_default();
    if (display) {
        auto surface = get_surface();
        auto monitor = display->get_monitor_at_surface(surface);
        if (monitor) {
            Gdk::Rectangle geometry;
            monitor->get_geometry(geometry);

            width = geometry.get_width();
            height = geometry.get_height();
            
        }
    }
    return std::make_pair(width, height);
}
// all functions that require realization to be called
void AppWindow::layout_functions() {
    fullscreen();
    auto [width, height] = get_window_size();
    menu.assemble_menu_layout(width, height);
    game.set_window_size(width, height);
    game.queue_draw(); // redraw window as last step to make sure it all works properly
}
bool AppWindow::on_key_press(guint keyval, guint keycode, Gdk::ModifierType state) {
    if (keyval == GDK_KEY_Escape) {
        if(property_fullscreened() == true) {
            unfullscreen();
        }
        else {
            fullscreen();
        }
    return true; 
}
return false; 

}

bool AppWindow::on_close() {
    exit(0);
    return false;
}

bool AppWindow::on_game_tick() {
    game.tick();
    game.queue_draw();
    return true;
}
