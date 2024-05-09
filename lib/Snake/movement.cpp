/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-guillaume.deplaine
** File description:
** snake
*/

#include "snake.hpp"
#include "Game.hpp"

void Snake::set_game()
{
    for (int i = 0; i != MAP_SIZE; i++) {
        for (int j = 0; j != MAP_SIZE; j++) {
            if (map[i][j] == FRUIT)
                game_file->set_elem(11, i, j);
        }
    }
    for (SnakeSegment *current = head; current != nullptr; current = current->next) {
        if (map[current->x][current->y] == ' ')
            game_file->set_elem(0, current->x, current->y);
        if (map[current->x][current->y] == SNAKE_HEAD)
            game_file->set_elem(1, current->x, current->y);
    }
    for (int i = 0; i != MAP_SIZE; i++) {
        for (int j = 0; j != MAP_SIZE; j++) {
            if (map[i][j] == SNAKE_BODY)
                game_file->set_elem(5, i, j);
            if (map[i][j] == 'W')
                game_file->set_elem(12, i, j);
        }
    }
}

void Snake::move_up()
{
    if (last_action == core::DOWN)
        return;
    if (snake_size == MAP_SIZE * MAP_SIZE)
        win_strict = game::WIN;
    if (map[head->x - 1][head->y] != ' ' && map[head->x - 1][head->y] != FRUIT)
        win_strict = game::LOSE;
    if (map[head->x - 1][head->y] == FRUIT) {
        snake_size++;
        tail->next = new SnakeSegment{tail->x, tail->y, nullptr, tail};
        tail = tail->next;
        generate_fruit();
    }
    if (head->x > 0) {
        move_segments(head->x, head->y);
        head->x--;
        map[head->x][head->y] = SNAKE_HEAD;
        last_action = core::UP;
        set_game();
    }
}

void Snake::move_left()
{
    if (last_action == core::RIGHT)
        return;
    if (snake_size == MAP_SIZE * MAP_SIZE)
        win_strict = game::WIN;
    if (map[head->x][head->y - 1] != ' ' && map[head->x][head->y - 1] != FRUIT)
        win_strict = game::LOSE;
    if (map[head->x][head->y - 1] == FRUIT) {
        snake_size++;
        tail->next = new SnakeSegment{tail->x, tail->y, nullptr, tail};
        tail = tail->next;
        generate_fruit();
    }
    if (head->y > 0) {
        move_segments(head->x, head->y);
        head->y--;
        map[head->x][head->y] = SNAKE_HEAD;
        last_action = core::LEFT;
        set_game();
    }
}

void Snake::move_right()
{
    if (last_action == core::LEFT)
        return;
    if (snake_size == MAP_SIZE * MAP_SIZE)
        win_strict = game::WIN;
    if (map[head->x][head->y + 1] != ' ' && map[head->x][head->y + 1] != FRUIT)
        win_strict = game::LOSE;
    if (map[head->x][head->y + 1] == FRUIT) {
        snake_size++;
        tail->next = new SnakeSegment{tail->x, tail->y, nullptr, tail};
        tail = tail->next;
        generate_fruit();
    }
    if (head->y < MAP_SIZE - 1) {
        move_segments(head->x, head->y);
        head->y++;
        map[head->x][head->y] = SNAKE_HEAD;
        last_action = core::RIGHT;
        set_game();
    }
}

void Snake::move_down()
{
    if (last_action == core::UP)
        return;
    if (snake_size == MAP_SIZE * MAP_SIZE)
        win_strict = game::WIN;
    if (map[head->x + 1][head->y] != ' ' && map[head->x + 1][head->y] != FRUIT)
        win_strict = game::LOSE;
    if (map[head->x + 1][head->y] == FRUIT) {
        snake_size++;
        tail->next = new SnakeSegment{tail->x, tail->y, nullptr, tail};
        tail = tail->next;
        generate_fruit();
    }
    if (head->x < MAP_SIZE - 1) {
        move_segments(head->x, head->y);
        head->x++;
        map[head->x][head->y] = SNAKE_HEAD;
        last_action = core::DOWN;
        set_game();
    }
}

void Snake::move_segments(int new_head_x, int new_head_y)
{
    SnakeSegment *current = head;
    while (current != nullptr) {
        int temp_x = current->x;
        int temp_y = current->y;
        map[current->x][current->y] = ' ';
        current->x = new_head_x;
        current->y = new_head_y;
        map[current->x][current->y] = SNAKE_BODY;
        map[tail->x][tail->y] = ' ';
        new_head_x = temp_x;
        new_head_y = temp_y;
        if (current->next == nullptr) {
            tail->x = current->x;
            tail->y = current->y;
        }
        current = current->next;
    }
}
