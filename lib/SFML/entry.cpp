/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** entry
*/

#include "Sfml.hpp"

extern "C" graphical::IDisplayModule *entryPoint() {
    return new graphical::Sfml();
}
