/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-guillaume.deplaine
** File description:
** Sdl
*/

/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-guillaume.deplaine
** File description:
** Sdl
*/

#include "Sdl.hpp"
#include <SDL2/SDL_image.h>
#include <iostream>
#include <sstream>

namespace graphical
{

    Sdl::Sdl()
    {
        initializeKeyMap();
        printf("Sdl constructor\n");
    }

    Sdl::~Sdl()
    {
        if (font)
        {
            TTF_CloseFont(font);
        }
        if (renderer)
        {
            SDL_DestroyRenderer(renderer);
        }
        if (window)
        {
            SDL_DestroyWindow(window);
        }
        TTF_Quit();
        SDL_Quit();
    }

    void Sdl::init(std::shared_ptr<core::IAssetLoader> assets)
    {
        printf("Sdl init\n");
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            throw std::runtime_error("Failed to initialize SDL");
        }
        if (TTF_Init() == -1)
        {
            throw std::runtime_error("Failed to initialize TTF");
        }
        window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
        if (!window)
        {
            throw std::runtime_error("Failed to create window");
        }
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer)
        {
            throw std::runtime_error("Failed to create renderer");
        }
        font = TTF_OpenFont("lib/SDL2/arial.ttf", 24);
        if (!font)
        {
            throw std::runtime_error("Failed to load font");
        }
        this->_assets = assets;
        update_sprites();
    }

    void Sdl::update_sprites()
    {
        const auto &game_map = _assets->get_map();
        sprites.resize(game_map.size());
        for (std::size_t y = 0; y < game_map.size(); y++)
        {
            sprites[y].resize(game_map[y].size());
            for (std::size_t x = 0; x < game_map[y].size(); x++)
            {
                std::string path = _assets->get_textual(game_map[y][x], core::IAssetLoader::SPRITE_2D);
                auto it = texture_map.find(path);
                if (it == texture_map.end())
                {
                    SDL_Surface *surface = IMG_Load(path.c_str());
                    if (!surface)
                    {
                        throw std::runtime_error("Failed to load texture");
                    }
                    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
                    if (!texture)
                    {
                        SDL_FreeSurface(surface);
                        throw std::runtime_error("Failed to create texture");
                    }
                    auto inserted = texture_map.insert({path, texture});
                    it = inserted.first;
                }
                sprites[y][x] = it->second;
            }
        }
    }

    std::map<core::action, bool> Sdl::update(void)
    {
        SDL_Event event;
        std::map<core::action, bool> actions;

        update_sprites();

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                actions[core::QUIT] = true;
            }
            if (event.type == SDL_KEYDOWN)
            {
                if (keyMap.find(event.key.keysym.sym) != keyMap.end())
                {
                    actions[keyMap[event.key.keysym.sym]] = true;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (const auto &row : sprites)
        {
            for (const auto &sprite : row)
            {
                SDL_RenderCopy(renderer, sprite, nullptr, nullptr);
            }
        }
        SDL_RenderPresent(renderer);

        return actions;
    }

    void Sdl::set_name(const std::string &name)
    {
        SDL_SetWindowTitle(window, name.c_str());
    }

    std::map<core::action, bool> Sdl::print_text(const std::string &text)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_Color color = {255, 255, 255, 255};

        int text_x = 100;
        int text_y = 100;

        std::istringstream textStream(text);
        std::string line;
        while (getline(textStream, line))
        {
            SDL_Surface *surface = TTF_RenderText_Solid(font, line.c_str(), color);
            if (!surface)
            {
                continue;
            }
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
            if (!texture)
            {
                SDL_FreeSurface(surface);
                continue;
            }

            int text_width = surface->w;
            int text_height = surface->h;
            SDL_FreeSurface(surface);

            SDL_Rect renderQuad = {text_x, text_y, text_width, text_height};
            SDL_RenderCopy(renderer, texture, nullptr, &renderQuad);

            SDL_DestroyTexture(texture);

            text_y += text_height + 5;
        }

        SDL_RenderPresent(renderer);

        SDL_Event event;
        std::map<core::action, bool> actions;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                actions[core::QUIT] = true;
            }
            if (event.type == SDL_KEYDOWN)
            {
                if (keyMap.find(event.key.keysym.sym) != keyMap.end())
                {
                    actions[keyMap[event.key.keysym.sym]] = true;
                }
            }
        }

        return actions;
    }

    char Sdl::get_key(void)
    {
        SDL_Event event;
        while (SDL_WaitEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                return 27;
            }
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z)
                {
                    return static_cast<char>(event.key.keysym.sym);
                }
                if (event.key.keysym.sym >= SDLK_0 && event.key.keysym.sym <= SDLK_9)
                {
                    return static_cast<char>(event.key.keysym.sym);
                }
                if (event.key.keysym.sym == SDLK_SPACE)
                {
                    return ' ';
                }
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    return 27;
                }
                if (event.key.keysym.sym == SDLK_RETURN)
                {
                    return '\n';
                }
            }
        }
        return '\0';
    }

    void Sdl::initializeKeyMap()
    {
        printf("Sdl initializeKeyMap\n");
        keyMap[SDLK_ESCAPE] = core::action::QUIT;
        printf("Sdl initializeKeyMap 1\n");
        keyMap[SDLK_UP] = core::action::UP;
        printf("Sdl initializeKeyMap 2\n");
        keyMap[SDLK_DOWN] = core::action::DOWN;
        printf("Sdl initializeKeyMap 3\n");
        keyMap[SDLK_LEFT] = core::action::LEFT;
        printf("Sdl initializeKeyMap 4\n");
        keyMap[SDLK_RIGHT] = core::action::RIGHT;
        printf("Sdl initializeKeyMap 5\n");
        keyMap[SDLK_SPACE] = core::action::ACTION;
        printf("Sdl initializeKeyMap 6\n");
        keyMap[SDLK_RETURN] = core::action::MENU;
        printf("Sdl initializeKeyMap 7\n");
    }

}