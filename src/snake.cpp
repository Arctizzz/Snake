#include "snake.hpp"
#include <gtkmm.h>
#include <stdlib.h>
#include <stdio.h>

Snake::Snake() {
for(int col = 0;col < cols; col++) {
    for(int row = 0;row < rows; row++){
        Gamearea[row][col] = 0;
    }
}
}
void Snake::print_gamearea() {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            printf("%d ", Gamearea[row][col]);
        }
        printf("\n");
    }
}