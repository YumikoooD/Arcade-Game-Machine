/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** graphical lib
*/

#ifndef GRAPHICAL_HPP_
    #define GRAPHICAL_HPP_

    #include <string>
    #include <map>
    #include <memory>
    #include "Core.hpp"

namespace graphical {

    class IDisplayModule {
        public :
            virtual ~IDisplayModule() = default;
            // @brief Sets the asset loader and start the lib
            // @param assets The asset loader created by the core and loaded by the game
            virtual void init(std::shared_ptr<core::IAssetLoader> assets) = 0;
            // @brief Updates the screen and return the states of the keys
            // @return A map of actions and if it's pressed or not
            virtual std::map<core::action, bool> update(void) = 0;
            // @brief Sets the name of the window
            // @param name The new name of the window
            virtual void set_name(const std::string &name) = 0;
            // @brief Print a text on screen
            // @param Text to print
            // @return A map of actions and if it's pressed or not
            virtual std::map<core::action, bool> print_text(const std::string &text) = 0;
            // @brief Returns key as soon as they are pressed
            // @return The key pressed
            virtual char get_key(void) = 0;
    };

    // @brief The error from a graphical class
    class GraphicalError : public std::exception {
        public:
            GraphicalError(const std::string &str): _str(str) {}
            const char *what() const throw() {
                return _str.c_str();
            }
        private:
            const std::string _str;
    };
}

// extern "C" graphical::IDisplayModule* entryPoint();

#endif /* !GRAPHICAL_HPP_ */
