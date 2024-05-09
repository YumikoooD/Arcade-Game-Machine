/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-guillaume.deplaine
** File description:
** AssetLoader
*/

#ifndef ASSETLOADER_HPP_
    #define ASSETLOADER_HPP_

class AssetLoader;

#include <ostream>
#include "Core.hpp"

class AssetLoader: public core::IAssetLoader {
    public:
        AssetLoader();
        ~AssetLoader();
        // @brief Load the conf file
        // @param conf_file The path to the conf file
        void init(const std::string &conf_file) override;
        // @brief Get the texture for a lib
        // @param id the id to get the texture of
        // @param type the type of lib
        const std::string &get_textual(int id, enum type type)
            const override;
        // @brief Set an element to a pos on the map
        // @param id The id of the elem
        // @param x The x position on the map
        // @param y The y position on the map
        void set_elem(int id, int x, int y) override;
        // @brief Get the map of ids to show
        // @return a 2d array of element to show
        const std::vector<std::vector<int>> &get_map() const override;
        // @brief Get the rules from the config file
        // @return the rules as a string
        const std::string &get_rules() const override;
        // @brief Get the name from the config file
        // @return the name as a string
        const std::string &get_names() const override;
        // @brief Get the high_score from the config file
        // @return the rules as a map of player_name as string and values
        // @note MIGHT NOT include the current player high-score
        const std::map<std::string, std::size_t> &get_high_score()
            const override;
        // @brief Get the high_score from the config file
        // @return the rules as a map of player_name as string and values
        // @note MIGHT NOT include the current player high-score
        const std::map<std::string, std::size_t> &get_high_score();
        // @brief Saves the high_score in the config_file
        // @param the high_scores to save
        void save_high_score(std::map<std::string, std::size_t>) const;
        // @brief Saves the high_score in the config_file and reload them
        // @param the high_scores to save
        void save_high_score(std::map<std::string, std::size_t>);
    protected:
        std::map<std::string, std::size_t> _high_scores;
        std::vector<std::vector<int>> _sprite_map;
        std::string _rules;
        std::string _name;
        std::map<int, std::map<enum type, std::string>> _sprites;
        std::string _file;
    private:
        // @brief Reloads high scores
        void _reload_high_scores();
        // @brief Reloads textures
        void _reload_textures();
        // @brief Reloads map to initial state
        void _reload_map();
        // @brief Reloads rules and name
        void _reload_rules();
        // @brief Load high score from a file
        // @param filepath The path to the file to load
        // @return the high_score_map
        static std::map<std::string, std::size_t> _get_high_score_from_file(
            const std::string &filepath);
        // @brief Load the textures from a file
        // @param filepath The path to the file to load
        // @return the texture map
        static std::map<int, std::map<enum type, std::string>>
            _get_textures_from_file(const std::string &filepath);
        // @brief Load the initial game map from a file
        // @param filepath The path to the file to load
        // @return the initial map
        static std::vector<std::vector<int>> _get_map_from_file(
            const std::string &filepath);
        // @brief Load rules from a file
        // @param filepath The path to the file to load
        // @return the string of rules
        static std::string _get_rules_from_file(const std::string &filepath);
        // @brief Load name from a file
        // @param filepath The path to the file to load
        // @return the string of name
        static std::string _get_name_from_file(const std::string &filepath);
        // @brief Saves the high_score in the config_file
        // @param the high_scores to save
        static void _save_high_score(const std::string &filepath,
            std::map<std::string, std::size_t> hs);
};

#define NAME_OFFSET 0
#define RULES_OFFSET 1
#define HIGH_SCORE_OFFSET 2
#define TEXTURES_OFFSET 3
#define MAP_OFFSET 4

// Generated commented because interface or abstract class could implement it
// std::ostream &operator<<(std::ostream &str, const AssetLoader &assetloader);

#endif /* !ASSETLOADER_HPP_ */
