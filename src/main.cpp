#include "main_window.hpp"
#include <gtkmm.h>
#include <iostream>
#include <thread>
#include <chrono>
#include "snake.hpp"
int main(int argc, char* argv[]) {
auto app = Gtk::Application::create("org.snake.menu");

    AppWindow window;
    app->hold(); 
    window.show();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    return app->run(argc, argv); 
}
