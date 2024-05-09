/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-guillaume.deplaine
** File description:
** Nibbleur
*/

#include "nibbleur.hpp"
#include "Game.hpp"

void Nibbleur::set_game()
{
    for (int i = 0; i != MAP_SIZE; i++) {
        for (int j = 0; j != MAP_SIZE; j++) {
            if (map[i][j] == FRUIT)
                game_file->set_elem(11, i, j);
        }
    }
    for (NibbleurSegment *current = head; current != nullptr; current = current->next) {
        if (map[current->x][current->y] == 'W')
            game_file->set_elem(11, current->x, current->y);
        if (map[current->x][current->y] == ' ')
            game_file->set_elem(0, current->x, current->y);
        if (map[current->x][current->y] == Nibbleur_HEAD)
            game_file->set_elem(1, current->x, current->y);
    }
    for (int i = 0; i != MAP_SIZE; i++) {
        for (int j = 0; j != MAP_SIZE; j++) {
            if (map[i][j] == Nibbleur_BODY)
                game_file->set_elem(5, i, j);
            if (map[i][j] == 'W')
            game_file->set_elem(12, i, j);
        }
    }
}

void Nibbleur::move_up()
{
    if (last_action == core::DOWN)
        return;
    if (Nibbleur_size == MAP_SIZE * MAP_SIZE)
        win_strict = game::WIN;
    if (map[head->x - 1][head->y] != ' ' && map[head->x - 1][head->y] != FRUIT
        && map[head->x - 1][head->y] != 'W')
        win_strict = game::LOSE;
    if (map[head->x - 1][head->y] == 'W') {
        if (map[head->x][head->y - 1] != 'W' && map[head->x][head->y +1 ] != 'W') {
            return;
        }
        if (map[head->x][head->y - 1] != 'W') {
            move_left();
        } else if (map[head->x][head->y + 1] != 'W') {
            move_right();
        }
        return;
    }
    if (map[head->x - 1][head->y] == FRUIT) {
        Nibbleur_size++;
        tail->next = new NibbleurSegment{tail->x, tail->y, nullptr, tail};
        tail = tail->next;
        generate_fruit();
    }
    if (head->x > 0) {
        move_segments(head->x, head->y);
        head->x--;
        map[head->x][head->y] = Nibbleur_HEAD;
        last_action = core::UP;
        set_game();
    }
}

void Nibbleur::move_left()
{
    if (last_action == core::RIGHT)
        return;
    if (Nibbleur_size == MAP_SIZE * MAP_SIZE)
        win_strict = game::WIN;
    if (map[head->x][head->y - 1] != ' ' && map[head->x][head->y - 1] != FRUIT
        && map[head->x][head->y - 1] != 'W')
        win_strict = game::LOSE;
    if (map[head->x][head->y - 1] == 'W') {
        if (map[head->x - 1][head->y] != 'W' && map[head->x + 1][head->y] != 'W') {
            return;
        }
        if (map[head->x - 1][head->y] != 'W') {
            move_up();
        } else if (map[head->x + 1][head->y] != 'W') {
            move_down();
        }
        return;
    }
    if (map[head->x][head->y - 1] == FRUIT) {
        Nibbleur_size++;
        tail->next = new NibbleurSegment{tail->x, tail->y, nullptr, tail};
        tail = tail->next;
        generate_fruit();
    }
    if (head->y > 0) {
        move_segments(head->x, head->y);
        head->y--;
        map[head->x][head->y] = Nibbleur_HEAD;
        last_action = core::LEFT;
        set_game();
    }
}

void Nibbleur::move_right()
{
    if (last_action == core::LEFT)
        return;
    if (Nibbleur_size == MAP_SIZE * MAP_SIZE)
        win_strict = game::WIN;
    if (map[head->x][head->y + 1] != ' ' && map[head->x][head->y + 1] != FRUIT
        && map[head->x][head->y + 1] != 'W')
        win_strict = game::LOSE;
    if (map[head->x][head->y + 1] == 'W') {
        if (map[head->x - 1][head->y] != 'W' && map[head->x + 1][head->y] != 'W') {
            return;
        }
        if (map[head->x - 1][head->y] != 'W') {
            move_up();
        } else if (map[head->x + 1][head->y] != 'W') {
            move_down();
        }
        return;
    }
    if (map[head->x][head->y + 1] == FRUIT) {
        Nibbleur_size++;
        tail->next = new NibbleurSegment{tail->x, tail->y, nullptr, tail};
        tail = tail->next;
        generate_fruit();
    }
    if (head->y < MAP_SIZE - 1) {
        move_segments(head->x, head->y);
        head->y++;
        map[head->x][head->y] = Nibbleur_HEAD;
        last_action = core::RIGHT;
        set_game();
    }
}

void Nibbleur::move_down()
{
    if (last_action == core::UP)
        return;
    if (Nibbleur_size == MAP_SIZE * MAP_SIZE)
        win_strict = game::WIN;
    if (map[head->x + 1][head->y] != ' ' && map[head->x + 1][head->y] != FRUIT
        && map[head->x + 1][head->y] != 'W')
        win_strict = game::LOSE;
    if (map[head->x + 1][head->y] == 'W') {
        if (map[head->x][head->y - 1] != 'W' && map[head->x][head->y +1] != 'W') {
            return;
        }
        if (map[head->x][head->y - 1] != 'W') {
            move_left();
        } else if (map[head->x][head->y + 1] != 'W') {
            move_right();
        }
        return;
    }
    if (map[head->x + 1][head->y] == FRUIT) {
        Nibbleur_size++;
        tail->next = new NibbleurSegment{tail->x, tail->y, nullptr, tail};
        tail = tail->next;
        generate_fruit();
    }
    if (head->x < MAP_SIZE - 1) {
        move_segments(head->x, head->y);
        head->x++;
        map[head->x][head->y] = Nibbleur_HEAD;
        last_action = core::DOWN;
        set_game();
    }
}

void Nibbleur::move_segments(int new_head_x, int new_head_y)
{
    NibbleurSegment *current = head;
    while (current != nullptr) {
        int temp_x = current->x;
        int temp_y = current->y;
        map[current->x][current->y] = ' ';
        current->x = new_head_x;
        current->y = new_head_y;
        map[current->x][current->y] = Nibbleur_BODY;
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
