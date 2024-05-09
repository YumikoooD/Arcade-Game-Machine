/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** entry
*/

#include "Sdl.hpp"

extern "C" graphical::IDisplayModule* entryPoint() {
    return new graphical::Sdl();
}
