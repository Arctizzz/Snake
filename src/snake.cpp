#include "snake.hpp"
#include <gtkmm.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#define EMPTY 0
#define APPLE 1
#define SNAKE 2

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
void Snake::domovement() {
int HeadX = head->xpos;
int HeadY = head->ypos;
    switch (direction)
    {
    case UP:    HeadY += 1; break;
    case DOWN:  HeadY -= 1; break;
    case LEFT:  HeadX -= 1; break;
    case RIGHT: HeadX += 1; break;
    }
    has_hit_wall();
    has_hit_itself();
    add_head(HeadX, HeadY);
    delete_tail();
    print_gamearea();
}
void Snake::init_snake() {
    SnakeSegment* segment1 = new SnakeSegment{10, 12, nullptr};
    SnakeSegment* segment2 = new SnakeSegment{10, 11, nullptr};
    SnakeSegment* segment3 = new SnakeSegment{10, 10, nullptr};

    segment1->next = segment2;
    segment2->next = segment3;

    tail = segment3;
    head = segment1;
    Gamearea[10][10] = SNAKE;
    Gamearea[10][11] = SNAKE;
    Gamearea[10][12] = SNAKE;
}

void Snake::generate_apple() {
    bool apple_was_generated = false;
    srand(time(0));
    while(apple_was_generated == false) {
    int randomcol = rand() % cols;
    int randomrow = rand() % rows;

    if(Gamearea[randomrow][randomcol] == EMPTY) {
        Gamearea[randomrow][randomcol] = APPLE;
        apple_was_generated = true;
    }
    }

}
void Snake::add_head(int NewX, int NewY){
    SnakeSegment* newhead = new SnakeSegment{NewX, NewY, head};
    head = newhead;
    Gamearea[NewY][NewX] = SNAKE;

}
void Snake::delete_tail(){
    SnakeSegment* current = head;
    while(current->next != tail){
        current = current->next;
    }
if(has_hit_apple() == false) {
    Gamearea[tail->ypos][tail->xpos] = EMPTY;
    delete tail;
    tail = current;
    tail->next = nullptr;
}
}
bool Snake::has_hit_apple() {
    int HeadX = head->xpos;
    int HeadY = head->ypos;

    if(Gamearea[HeadY][HeadX] == APPLE) {
        generate_apple();
        return true;
    }
    else {
        return false;
    }
}
void Snake::has_hit_wall() {
    int HeadX = head->xpos;
    int HeadY = head->ypos;
    if (HeadX < 0 || HeadX >= cols || HeadY < 0 || HeadY >= rows) {
    game_over();
    }
}

void Snake::has_hit_itself() {
    int HeadX = head->xpos;
    int HeadY = head->ypos;
    if(Gamearea[HeadY][HeadX] == SNAKE){
        game_over();
    }
}
void Snake::game_over(){
    exit(1);
}