/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-guillaume.deplaine
** File description:
** snape
*/

#ifndef SNAPE_HPP_
#define SNAPE_HPP_
#define MAP_SIZE 20
#define SNAKE_HEAD 'o'
#define SNAKE_BODY '-'
#define FRUIT 'F'


#include "Game.hpp"

struct SnakeSegment {
    int x;
    int y;
    SnakeSegment *next;
    SnakeSegment *prev;
};

class Snake : public game::IGameModule {
    public:
        Snake() {};
        ~Snake() = default;
        void init(std::shared_ptr<core::IAssetLoader>) override;
        game::state update(std::map<core::action, bool> action) override;
        const std::size_t &get_score() override;
    private:
        std::map<int, std::string> map;
        std::size_t snake_size;
        SnakeSegment *head;
        SnakeSegment *tail;
        core::action last_action;
        game::state win_strict;
        std::shared_ptr<core::IAssetLoader> game_file;
        void create_map();
        void move(int new_x, int new_y);
        void move_up();
        void move_left();
        void move_right();
        void move_down();
        void generate_fruit();
        void initialize_snake();
        void set_game();
        void move_segments(int new_head_x, int new_head_y);
        int time;
};


#endif /* !SNAPE_HPP_ */
