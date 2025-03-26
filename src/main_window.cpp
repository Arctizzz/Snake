#include "main_window.hpp"
#include "menu.hpp"
AppWindow::AppWindow() {

    stack.set_transition_type(Gtk::StackTransitionType::SLIDE_LEFT_RIGHT);
    stack.set_transition_duration(500);

    stack.add(menu, "menu");
    stack.add(game, "game");

    set_child(stack);

    menu.on_start_game.connect(sigc::mem_fun(*this, &AppWindow::on_start_game));
    signal_realize().connect(sigc::mem_fun(*this, &AppWindow::on_start_game));
    show();
}

void AppWindow::on_start_game(){
    stack.set_visible_child("game");
}