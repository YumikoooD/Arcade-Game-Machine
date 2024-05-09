/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-guillaume.deplaine
** File description:
** ncurse
*/

#include "nibbleur.hpp"
#include "Game.hpp"

extern "C" {
    game::IGameModule *entryPoint()
    {
        return new Nibbleur;
    }
}
