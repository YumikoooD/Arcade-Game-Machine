/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-guillaume.deplaine
** File description:
** AssetLoader
*/

#include <sstream>
#include <fstream>
#include <istream>
#include <ostream>
#include <iostream>
#include <string>
#include "AssetLoader.hpp"
#include "Core.hpp"

AssetLoader::AssetLoader()
{
}

AssetLoader::~AssetLoader()
{
}


void AssetLoader::init(const std::string &conf_file)
{
    _file = conf_file;
    _reload_rules();
    _reload_textures();
    _reload_map();
    _reload_high_scores();
}

const std::string &AssetLoader::get_textual(int id, enum type type) const
{
    return _sprites.at(id).at(type);
}

void AssetLoader::set_elem(int id, int x, int y)
{
    _sprite_map[x][y] = id;
    _reload_high_scores();
}

const std::vector<std::vector<int>> &AssetLoader::get_map() const
{
    return _sprite_map;
}

const std::string &AssetLoader::get_rules() const
{
    return _rules;
}

const std::string &AssetLoader::get_names() const
{
    return _name;
}

const std::map<std::string, std::size_t> &AssetLoader::get_high_score() const
{
    return _high_scores;
}

const std::map<std::string, std::size_t> &AssetLoader::get_high_score()
{
    _reload_high_scores();
    return _high_scores;
}

void AssetLoader::_reload_high_scores() {
    try {
        _high_scores = _get_high_score_from_file(_file);
    } catch (const std::exception &e) {;};
}

void AssetLoader::_reload_map()
{
    try {
        _sprite_map = _get_map_from_file(_file);
    } catch (const std::exception &) {;};
}

void AssetLoader::_reload_textures()
{
    try {
        _sprites = _get_textures_from_file(_file);
    } catch (const std::exception &) {;};
}

void AssetLoader::_reload_rules()
{
    try {
        _rules = _get_rules_from_file(_file);
    } catch (const std::exception &) {;};
    try {
        _name = _get_name_from_file(_file);
    } catch (const std::exception &) {;};
}

std::map<std::string, std::size_t> AssetLoader::_get_high_score_from_file(
    const std::string &filepath)
{
    std::map<std::string, std::size_t>scores;
    std::ifstream file(filepath);
    std::string line;

    for (unsigned int i = 0; not file.eof() and i < HIGH_SCORE_OFFSET;) {
        std::getline(file, line);
        if (line == "--")
            i++;
    }
    std::getline(file, line);
    while (not file.eof() and line != "--") {
        std::stringstream str;
        std::string name;
        std::string score_txt;
        std::size_t score;
        str << line;
        std::getline(str, name, ',');
        std::getline(str, score_txt, ',');
        score = std::stoul(score_txt);
        scores[name] = score;
        std::getline(file, line);
    }
    return scores;
}

std::map<int, std::map<core::IAssetLoader::type, std::string>>
    AssetLoader::_get_textures_from_file(const std::string &filepath)
{
    std::map<int, std::map<enum type, std::string>>textures;
    std::ifstream file(filepath);
    std::string line;

    for (unsigned int i = 0; not file.eof() and i < TEXTURES_OFFSET;) {
        std::getline(file, line);
        if (line == "--")
            i++;
    }
    std::getline(file, line);
    while (not file.eof() and line != "--") {
        int id;
        std::stringstream str;
        std::string id_txt;
        std::string text;
        std::string file_2d;
        std::string file_3d;
        str << line;
        std::getline(str, id_txt, ',');
        id = std::stoi(id_txt);
        std::getline(str, text, ',');
        std::getline(str, file_2d, ',');
        std::getline(str, file_3d, ',');
        textures[id][TEXTUAL] = text;
        textures[id][SPRITE_2D] = file_2d;
        textures[id][SPRITE_3D] = file_3d;
        std::getline(file, line);
    }
    return textures;
}

std::vector<std::vector<int>> AssetLoader::_get_map_from_file(
    const std::string &filepath)
{
    std::ifstream file(filepath);
    std::string line;
    std::vector<std::vector<int>> map;
    std::string number_txt;
    int number;

    for (unsigned int i = 0; not file.eof() and i < MAP_OFFSET;) {
        std::getline(file, line);
        if (line == "--")
            i++;
    }
    std::getline(file, line);
    while (not file.eof() and line != "--") {
        std::stringstream str;
        std::vector<int> row;
        str << line;
        while (std::getline(str, number_txt, ',')) {
            number = std::stoi(number_txt);
            row.push_back(number);
        }
        map.push_back(row);
        std::getline(file, line);
    }
    return map;
}

std::string AssetLoader::_get_name_from_file(const std::string &filepath)
{
    std::ifstream file(filepath);
    std::string line;
    std::string name;

    for (unsigned int i = 0; not file.eof() and i < NAME_OFFSET;) {
        std::getline(file, line);
        if (line == "--")
            i++;
    }
    std::getline(file, line);
    while (not file.eof() and line != "--") {
        name = name.append(line);
        std::getline(file, line);
    }
    return name;
}

std::string AssetLoader::_get_rules_from_file(const std::string &filepath)
{
    std::ifstream file(filepath);
    std::string line;
    std::string rules;

    for (unsigned int i = 0; not file.eof() and i < RULES_OFFSET;) {
        std::getline(file, line);
        if (line == "--")
            i++;
    }
    std::getline(file, line);
    while (not file.eof() and line != "--") {
        rules = rules.append(line);
        std::getline(file, line);
    }
    return rules;
}

void AssetLoader::save_high_score(std::map<std::string, std::size_t> hs) const
{
    _save_high_score(_file, hs);
};

void AssetLoader::save_high_score(std::map<std::string, std::size_t> hs)
{
    _save_high_score(_file, hs);
    _reload_high_scores();
};

void AssetLoader::_save_high_score(const std::string &filepath,
    std::map<std::string, std::size_t> high_score)
{
    std::ifstream infile(filepath);
    std::ofstream outfile(filepath + "_");
    std::string line;
    std::string rules;

    for (unsigned int i = 0; not infile.eof() and i < HIGH_SCORE_OFFSET;) {
        std::getline(infile, line);
        if (line == "--")
            i++;
        outfile << line << "\n";
    }
    for (auto i : high_score) {
        std::string str(i.first);
        str.append("," + std::to_string(i.second) + "\n");
        outfile << str;
    }
    std::getline(infile, line);
    while (not infile.eof() and line != "--")
        std::getline(infile, line);
    while (not infile.eof()) {
        outfile << line << "\n";
        std::getline(infile, line);
    }
    if (line.length())
        outfile << line << "\n";

    if (std::remove(filepath.c_str()) != 0)
        throw core::AssetError("Remove original file");
    if (std::rename((filepath + "_").c_str(), filepath.c_str()) != 0)
        throw core::AssetError("Rename new file");
}
