/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-guillaume.deplaine
** File description:
** snape
*/

#ifndef SNAPE_HPP_
#define SNAPE_HPP_
#define MAP_SIZE 20
#define Nibbleur_HEAD 'o'
#define Nibbleur_BODY '-'
#define FRUIT 'F'


#include "Game.hpp"

struct NibbleurSegment {
    int x;
    int y;
    NibbleurSegment *next;
    NibbleurSegment *prev;
};

class Nibbleur : public game::IGameModule {
    public:
        Nibbleur() {};
        ~Nibbleur() = default;
        void init(std::shared_ptr<core::IAssetLoader>) override;
        game::state update(std::map<core::action, bool> action) override;
        const std::size_t &get_score() override;
    private:
        std::map<int, std::string> map;
        std::size_t Nibbleur_size;
        NibbleurSegment *head;
        NibbleurSegment *tail;
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
        void initialize_Nibbleur();
        void set_game();
        void move_segments(int new_head_x, int new_head_y);
        int time;
};


#endif /* !SNAPE_HPP_ */
