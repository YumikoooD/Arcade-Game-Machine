/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-guillaume.deplaine
** File description:
** ncurse
*/

#include "Graphical.hpp"
#include "Ncurses.hpp"

extern "C" {
    graphical::IDisplayModule *entryPoint()
    {
        return new Ncurses;
    }
}
