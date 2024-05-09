/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** core
*/

#ifndef CORE_HPP_
    #define CORE_HPP_

    #include <string>
    #include <map>
    #include <vector>

    #define FRAMERATE 60
    #define MENU_HAS_PSEUDO_CHANGE false
    #define MENU_HAS_QUIT_BUTTTON true
    #define MENU_HAS_SHOW_HIGH_SCORE_BUTTON true

namespace core {
    // @brief The possible actions
    enum action {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        ACTION,
        MENU,
        NEXT_LIB,
        NEXT_GAME,
        RESET,
        QUIT
    };

    // @brief The error from an asset class
    class AssetError: public std::exception {
        public:
            AssetError(const std::string &str): _str(str) {};
            const char *what() const throw() {return _str.c_str();};
        private:
            const std::string _str;
    };

    class IAssetLoader {
        public:
            enum type {
                TEXTUAL,
                SPRITE_2D,
                SPRITE_3D
            };
            virtual ~IAssetLoader() = default;
            // @brief Load the conf file
            // @param conf_file The path to the conf file
            virtual void init(const std::string &conf_file) = 0;
            // @brief Get the texture for a lib
            // @param id the id to get the texture of
            // @param type the type of lib
            virtual const std::string &get_textual(int id, enum type type)
                const = 0;
            // @brief Set an element to a pos on the map
            // @param id The id of the elem
            // @param x The x position on the map
            // @param y The y position on the map
            virtual void set_elem(int id, int x, int y) = 0;
            // @brief Get the map of ids to show
            // @return a 2d array of element to show
            virtual const std::vector<std::vector<int>> &get_map() const = 0;
            // @brief Get the rules from the config file
            // @return the rules as a string
            virtual const std::string &get_rules() const = 0;
            // @brief Get the name from the config file
            // @return the name as a string
            virtual const std::string &get_names() const = 0;
            // @brief Get the high_score from the config file
            // @return the rules as a map of player_name as string and values
            // @note MIGHT NOT include the current player high-score
            virtual const std::map<std::string, std::size_t> &get_high_score()
                const = 0;
            // @brief Saves the high_score in the config_file
            // @param the high_scores to save
            virtual void save_high_score(std::map<std::string, std::size_t>)
                const = 0;
    };
}

#endif /* !CORE_HPP_ */
