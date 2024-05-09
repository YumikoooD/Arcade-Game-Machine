/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Sfml
*/

#include "Sfml.hpp"

namespace graphical
{

    Sfml::Sfml()
    {
        initializeKeyMap();
    }

    Sfml::~Sfml()
    {
        if (window.isOpen())
        {
            window.close();
        }
    }

    void Sfml::init(std::shared_ptr<core::IAssetLoader> assets)
    {
        this->_assets = assets;
        if (!font.loadFromFile("lib/SFML/arial.ttf"))
        {
            throw std::runtime_error("Failed to load font");
        }
        this->window.create(sf::VideoMode(800, 600), "Arcade");
        update_sprites();
    }

    void Sfml::update_sprites()
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
                    sf::Texture texture;
                    if (!texture.loadFromFile(path))
                    {
                        throw std::runtime_error("Failed to load texture");
                    }
                    auto inserted = texture_map.insert({path, texture});
                    it = inserted.first;
                }
                sprites[y][x].setTexture(it->second);
                sprites[y][x].setPosition(x * 32, y * 32);
            }
        }
    }

    std::map<core::action, bool> Sfml::update(void)
    {
        sf::Event event;
        std::map<core::action, bool> actions;

        update_sprites();

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                actions[core::QUIT] = true;
            if (event.type == sf::Event::KeyPressed)
            {
                if (keyMap.find(event.key.code) != keyMap.end())
                {
                    actions[keyMap[event.key.code]] = true;
                }
            }
        }

        window.clear();
        for (const auto &row : sprites)
        {
            for (const auto &sprite : row)
            {
                window.draw(sprite);
            }
        }
        window.display();

        return actions;
    }

    void Sfml::set_name(const std::string &name)
    {
        window.setTitle(name);
    }

    std::map<core::action, bool> Sfml::print_text(const std::string &text)
    {
        window.clear();
        sf::Text sfText(text, font);
        sfText.setPosition(100, 100);
        window.draw(sfText);
        window.display();
        sf::Event event;
        std::map<core::action, bool> actions;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                actions[core::QUIT] = true;
            if (event.type == sf::Event::KeyPressed)
            {
                if (keyMap.find(event.key.code) != keyMap.end())
                {
                    actions[keyMap[event.key.code]] = true;
                }
            }
        }
        return actions;
    }

    char Sfml::get_key(void)
    {
        sf::Event event;
        while (true)
        {
            while (!window.pollEvent(event))
                ;
            if (event.type == sf::Event::Closed)
            {
                return 27;
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code >= sf::Keyboard::A && event.key.code <= sf::Keyboard::Z)
                {
                    return static_cast<char>('A' + event.key.code - sf::Keyboard::A);
                }
                if (event.key.code >= sf::Keyboard::A && event.key.code <= sf::Keyboard::Z)
                {
                    return static_cast<char>('a' + event.key.code - sf::Keyboard::A);
                }
                if (event.key.code >= sf::Keyboard::Num0 && event.key.code <= sf::Keyboard::Num9)
                {
                    return static_cast<char>('0' + event.key.code - sf::Keyboard::Num0);
                }
                if (event.key.code == sf::Keyboard::Space)
                {
                    return ' ';
                }
                if (event.key.code == sf::Keyboard::Escape)
                {
                    return 27;
                }
                if (event.key.code == sf::Keyboard::Return)
                {
                    return '\n';
                }
            }
        }
    }

    void Sfml::initializeKeyMap()
    {
        keyMap[sf::Keyboard::Escape] = core::action::QUIT;
        keyMap[sf::Keyboard::Up] = core::action::UP;
        keyMap[sf::Keyboard::Down] = core::action::DOWN;
        keyMap[sf::Keyboard::Left] = core::action::LEFT;
        keyMap[sf::Keyboard::Right] = core::action::RIGHT;
        keyMap[sf::Keyboard::Space] = core::action::ACTION;
        keyMap[sf::Keyboard::Return] = core::action::MENU;
    }

}