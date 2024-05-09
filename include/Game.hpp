/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** game
*/

#ifndef GAME_HPP_
    #define GAME_HPP_

    #include <string>
    #include <memory>
    #include <map>
    #include "Core.hpp"

namespace game {
    enum state {
        DEFAULT,
        LOSE,
        WIN
    };

    class IGameModule {
        public :
            virtual ~IGameModule() = default;
            // @brief Start the game and load an asset manager with a conf file
            // @param the asset manager that it made
            virtual void init(std::shared_ptr<core::IAssetLoader>) = 0;
            // @brief Updates the game given the actions that happened
            // @param action The action
            // @return the state of the game
            virtual game::state update(std::map<core::action, bool> action) = 0;
            // @brief Getter of score
            // @return The score of the current player
            virtual const std::size_t &get_score() = 0;
    };

    // @brief The error from a game class
    class GameError : public std::exception {
        public:
            GameError(const std::string &str): _str(str) {}
            const char *what() const throw() {
                return _str.c_str();
            }
        private:
            const std::string _str;
    };
}

// extern "C" game::IGameModule* entryPoint();

#endif /* !GAME_HPP_ */
