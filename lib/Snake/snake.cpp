/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-guillaume.deplaine
** File description:
** snake
*/

#include "snake.hpp"
#include "Game.hpp"
#include "AssetLoader.hpp"
#include <random>
#include <iostream>

int getRandomNumber(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(min, max);

    return distrib(gen);
}

void Snake::initialize_snake()
{
    head = new SnakeSegment{MAP_SIZE / 2, MAP_SIZE / 2, nullptr, nullptr};
    SnakeSegment *current = head;
    for (int i = 1; i < snake_size; ++i) {
        current->next = new SnakeSegment{MAP_SIZE / 2, MAP_SIZE / 2 - i, nullptr, current};
        current->next->prev = current;
        current = current->next;
    }
    tail = current;
}
void Snake::init(std::shared_ptr<core::IAssetLoader> file)
{
    time = 0;
    snake_size = 5;
    initialize_snake();
    create_map();
    win_strict = game::DEFAULT;
    //last_action = core::DOWN;
    file->init("./lib/Snake/snake_conf.csv");
    game_file = file;
    
}

const std::size_t &Snake::get_score() {
    return snake_size;
}

void Snake::generate_fruit()
{
    int fruitX, fruitY;
    do {
        fruitX = getRandomNumber(0, MAP_SIZE - 1);
        fruitY = getRandomNumber(0, MAP_SIZE - 1);
    } while (map.find(fruitX) == map.end() || 
            fruitY >= map[fruitX].size() || 
            map[fruitX][fruitY] != ' ');

    map[fruitX][fruitY] = FRUIT;
}

void Snake::create_map()
{
    std::string emptyRow(MAP_SIZE, ' ');
    for (int i = 0; i < MAP_SIZE; ++i) {
        map[i] = emptyRow;
    }
    for (int i = 0; i < MAP_SIZE; ++i) {
        map[0][i] = 'W';
        map[i][0] = 'W';
        map[i][MAP_SIZE - 1] = 'W';
        map[MAP_SIZE - 1][i] = 'W';
    }

    head->x = MAP_SIZE / 2;
    head->y = MAP_SIZE / 2;

    map[head->x][head->y] = SNAKE_HEAD;
    map[head->x][head->y - 1] = SNAKE_BODY;
    map[head->x][head->y - 2] = SNAKE_BODY;
    map[head->x][head->y - 3] = SNAKE_BODY;
    generate_fruit();
}


game::state Snake::update(std::map<core::action, bool> action)
{
    if (win_strict == game::LOSE) {
        return game::LOSE;
    } else if (win_strict == game::WIN) {
        return game::WIN;
    }
    if (action[core::UP]) {
        move_up();
        return game::DEFAULT;
    }
    if (action[core::DOWN]) {
        move_down();
        return game::DEFAULT;
    }
    if (action[core::LEFT]) {
        move_left();
        return game::DEFAULT;
    }
    if (action[core::RIGHT]) {
        move_right();
        return game::DEFAULT;
    }
     if (time != 6) {
        time++;
        return game::DEFAULT;
    } else {
        time = 0;
        if (last_action == core::UP) {
            move_up();
            return game::DEFAULT;
        }
        if (last_action == core::DOWN) {
            move_down();
            return game::DEFAULT;
        }
        if (last_action == core::LEFT) {
            move_left();
            return game::DEFAULT;
        }
        if (last_action == core::RIGHT) {
            move_right();
            return game::DEFAULT;
        }
    }
    return game::DEFAULT;
}
