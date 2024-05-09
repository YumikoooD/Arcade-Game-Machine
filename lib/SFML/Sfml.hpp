/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Sfml
*/

#ifndef SFML_HPP_
#define SFML_HPP_

#include "../../include/Graphical.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
#include <string>
#include <vector>

namespace graphical
{

    class Sfml : public IDisplayModule
    {
    public:
        Sfml();
        virtual ~Sfml();
        void init(std::shared_ptr<core::IAssetLoader> assets) override;
        std::map<core::action, bool> update(void) override;
        void set_name(const std::string &name) override;
        std::map<core::action, bool> print_text(const std::string &text) override;
        char get_key(void) override;

    private:
        sf::RenderWindow window;
        sf::Font font;
        std::shared_ptr<core::IAssetLoader> _assets;
        std::map<std::string, sf::Texture> texture_map;
        std::vector<std::vector<sf::Sprite>> sprites;
        std::map<sf::Keyboard::Key, core::action> keyMap;
        void initializeKeyMap();
        void update_sprites();
    };

}

#endif /* SFML_HPP_ */