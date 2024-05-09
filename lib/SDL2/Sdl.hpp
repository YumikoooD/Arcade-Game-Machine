/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-guillaume.deplaine
** File description:
** Sdl
*/

/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Sdl
*/

#ifndef SDL_HPP_
#define SDL_HPP_

#include "../../include/Graphical.hpp"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <map>
#include <memory>

namespace graphical
{

    class Sdl : public IDisplayModule
    {
    public:
        Sdl();
        virtual ~Sdl();
        void init(std::shared_ptr<core::IAssetLoader> assets) override;
        std::map<core::action, bool> update(void) override;
        void set_name(const std::string &name) override;
        std::map<core::action, bool> print_text(const std::string &text) override;
        char get_key(void) override;

    private:
        SDL_Window *window = nullptr;
        SDL_Renderer *renderer = nullptr;
        TTF_Font *font = nullptr;
        std::shared_ptr<core::IAssetLoader> _assets;
        std::map<SDL_Keycode, core::action> keyMap;
        std::map<std::string, SDL_Texture *> texture_map;
        std::vector<std::vector<SDL_Texture *>> sprites;
        void initializeKeyMap();
        void update_sprites();
    };

}

#endif /* !SDL_HPP_ */