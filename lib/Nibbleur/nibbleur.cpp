/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-guillaume.deplaine
** File description:
** Nibbleur
*/

#include "nibbleur.hpp"
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

void Nibbleur::initialize_Nibbleur()
{
    head = new NibbleurSegment {MAP_SIZE / 2, MAP_SIZE / 2, nullptr, nullptr};
    NibbleurSegment *current = head;
    for (int i = 1; i < Nibbleur_size; ++i) {
        current->next = new NibbleurSegment{MAP_SIZE / 2, MAP_SIZE / 2 - i, nullptr, current};
        current->next->prev = current;
        current = current->next;
    }
    tail = current;
}
void Nibbleur::init(std::shared_ptr<core::IAssetLoader> file)
{
    time = 0;
    Nibbleur_size = 5;
    initialize_Nibbleur();
    create_map();
    win_strict = game::DEFAULT;
    //last_action = core::DOWN;
    file->init("./lib/Nibbleur/nibbleur_conf.csv");
    game_file = file;
    
}

const std::size_t &Nibbleur::get_score() {
    return Nibbleur_size;
}

void Nibbleur::generate_fruit()
{
    int fruitX, fruitY;
    do {
        fruitX = getRandomNumber(0, MAP_SIZE - 1);
        fruitY = getRandomNumber(0, MAP_SIZE - 1);
    } while (map.find(fruitX) == map.end() || 
            fruitY >= map[fruitX].size() || 
            map[fruitX][fruitY] != ' ' || map[fruitX][fruitY] == 'W');

    map[fruitX][fruitY] = FRUIT;
}

void Nibbleur::create_map() {
        std::string emptyRow(MAP_SIZE, ' ');
        for (int i = 0; i < MAP_SIZE; ++i) {
            map[i] = emptyRow;
        }

        for (int i = 0; i < MAP_SIZE; ++i) {
            map[i][0] = 'W';
            map[i][MAP_SIZE - 1] = 'W';
            map[0][i] = 'W';
            map[MAP_SIZE - 1][i] = 'W';
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distrib(1, MAP_SIZE - 2);
        for (int i = 0; i < MAP_SIZE; ++i) {
            int x = distrib(gen);
            int y = distrib(gen);
            if (map[x][y] == ' ')
                map[x][y] = 'W';
        }

        head->x = MAP_SIZE / 2;
        head->y = MAP_SIZE / 2;

        map[head->x][head->y] = Nibbleur_HEAD;
        map[head->x][head->y - 1] = Nibbleur_BODY;
        map[head->x][head->y - 2] = Nibbleur_BODY;
        map[head->x][head->y - 3] = Nibbleur_BODY;

        generate_fruit();
    }


game::state Nibbleur::update(std::map<core::action, bool> action)
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
