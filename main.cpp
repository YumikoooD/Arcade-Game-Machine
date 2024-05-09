/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-guillaume.deplaine
** File description:
** main
*/

#include <istream>
#include <fstream>
#include "time.hpp"
#include "Game.hpp"
#include "Graphical.hpp"
#include "DLLoader.hpp"
#include "AssetLoader.hpp"

static int get_lib(const char *str)
{
    std::string wanted(str);
    std::string lib;
    std::vector<std::string> game_libs;
    std::vector<std::string> graph_libs;
    std::ifstream file("./lib_list.yaml");
    int __lib_i = 0;
    if (not file.is_open())
        std::__throw_system_error(2);
    std::getline(file, lib);
    while (not file.eof() and lib != "Graphical libs:") {
        std::getline(file, lib);
    }
    if (file.eof())
        std::__throw_system_error(61);
    std::getline(file, lib);
    while (not file.eof() and lib != "Game libs:") {
        __lib_i++;
        graph_libs.push_back(lib.erase(0, 4));
        std::getline(file, lib);
        if ("./lib/" + lib.erase(0, 4) == str)
            return __lib_i;
    }
    return -1;
}

static void _validate_menu_selection(int &menu_selection,
    const std::vector<std::string> game_libs,
    const std::vector<std::string> graph_libs)
{
    std::size_t menu_size = 0;

    menu_size += graph_libs.size();
    menu_size += game_libs.size();
    menu_size += MENU_HAS_SHOW_HIGH_SCORE_BUTTON;
    menu_size += MENU_HAS_PSEUDO_CHANGE;
    menu_size += MENU_HAS_QUIT_BUTTTON;

    while (menu_selection < 0)
        menu_selection += menu_size;
    while (menu_selection >= menu_size)
        menu_selection -= menu_size;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "please put graphical lib path" << std::endl;
        return 84;
    }
    try {
        std::string pseudo("---");
        int menu_selection = 0;
        std::unique_ptr<DLLoader<game::IGameModule>> game_lib = nullptr;
        std::unique_ptr<DLLoader<graphical::IDisplayModule>> graph_lib;
        graph_lib.reset(new DLLoader<graphical::IDisplayModule>(argv[1]));
        graphical::IDisplayModule *graph = graph_lib->getInstance("entryPoint");
        std::shared_ptr<core::IAssetLoader> assets = nullptr;
        std::map<core::action, bool> actions;
        Time timer;
        actions[core::QUIT] = false;
        actions[core::MENU] = true;
        assets.reset(new AssetLoader);
        int curr_game = -1;
        int curr_lib = get_lib(argv[1]);
        if (graph == nullptr)
            std::__throw_system_error(2);
        while (true) {
            graph->init(assets);
            if (actions[core::QUIT])
                break;
            if (actions[core::MENU]) {
                actions[core::MENU] = false;
                while (true) {
                    timer.framerate(FRAMERATE);
                    std::string lib;
                    std::vector<std::string> game_libs;
                    std::vector<std::string> graph_libs;
                    std::ifstream file("./lib_list.yaml");
                    if (not file.is_open())
                        std::__throw_system_error(2);
                    std::getline(file, lib);
                    while (not file.eof() and lib != "Graphical libs:") {
                        std::getline(file, lib);
                    }
                    if (file.eof())
                        std::__throw_system_error(61);
                    std::getline(file, lib);
                    while (not file.eof() and lib != "Game libs:") {
                        if (lib.length() < 1) {
                            std::getline(file, lib);
                            continue;
                        }
                        graph_libs.push_back(lib.erase(0, 4));
                        std::getline(file, lib);
                    }
                    if (file.eof())
                        std::__throw_system_error(61);
                    std::getline(file, lib);
                    while (not file.eof()) {
                        if (lib.length() < 1) {
                            std::getline(file, lib);
                            continue;
                        }
                        game_libs.push_back(lib.erase(0, 4));
                        std::getline(file, lib);
                    }
                    lib.erase();
                    unsigned int selected = menu_selection;
                    lib.append("Graphical libs: \n");
                    for (auto str: graph_libs) {
                        if (selected == 0)
                            lib.append(" -> " + str + "\n");
                        else
                            lib.append("    " + str + "\n");
                        selected--;
                    }
                    lib.append("\nGame libs: \n");
                    for (auto str: game_libs) {
                        if (selected == 0)
                            lib.append(" -> " + str + "\n");
                        else
                            lib.append("    " + str + "\n");
                        selected--;
                    }
                    lib.append("\nPseudo: " + pseudo + "\n");
                    if (MENU_HAS_PSEUDO_CHANGE and selected == 0)
                        lib.append(" -> Change\n");
                    else
                        lib.append("    Change\n");
                    selected -= MENU_HAS_PSEUDO_CHANGE;
                    if (MENU_HAS_SHOW_HIGH_SCORE_BUTTON and selected == 0)
                        lib.append("\n -> High-Scores\n");
                    else
                        lib.append("\nHigh-Scores\n");
                    selected -= MENU_HAS_SHOW_HIGH_SCORE_BUTTON;
                    if (MENU_HAS_QUIT_BUTTTON and selected == 0)
                        lib.append("\n -> Quit\n");
                    else
                        lib.append("\nQuit\n");
                    actions = graph->print_text(lib);
                    if (actions[core::QUIT])
                        break;
                    if (actions[core::DOWN])
                        menu_selection++;
                    if (actions[core::UP])
                        menu_selection--;
                    _validate_menu_selection(menu_selection, game_libs, graph_libs);
                    if (actions[core::ACTION]) {
                        unsigned int selection = menu_selection;
                        if (selection < graph_libs.size()){
                            graph_lib.reset(new DLLoader<graphical::IDisplayModule>("./lib/" + graph_libs[selection]));
                            graph = graph_lib->getInstance("entryPoint");
                            graph->init(assets);
                        }
                        selection -= graph_libs.size();
                        if (selection < game_libs.size()) {
                            game_lib.reset(new DLLoader<game::IGameModule>("./lib/" + game_libs[selection]));
                            break;
                        }
                        selection -= game_libs.size();
                        // TODO Add PSEUDO CHANGE, HIGH-SCORE and maybe QUIT
                        if (selection == 0) {
                            std::map<std::string, std::size_t> high_score = assets->get_high_score();
                            std::string hs("High-Scores: \n");
                            for (auto i : high_score) {
                                hs.append("   " + i.first + ": " + std::to_string(i.second) + "\n");
                            }
                            graph->print_text(hs);
                            char key = graph->get_key();
                            while (not (key == 27 or key == ' ' or key == 'q'))
                                key = graph->get_key();
                            if (key == 'q' or key == 27) {
                                actions[core::QUIT] = true;
                                break;
                            }
                        }
                        selection--;
                        if (selection == 0) {
                            actions[core::QUIT] = true;
                            break;
                        }
                        selection--;
                    }
                }
            } // MENU
            if (actions[core::QUIT])
                break;
            game::IGameModule *my_game = game_lib->getInstance("entryPoint");
            my_game->init(assets);
            game::state state = game::DEFAULT;
            while (state == game::DEFAULT) {
                timer.framerate(FRAMERATE);
                actions = graph->update();
                std::map<std::string, std::size_t> high_score = assets->get_high_score();
                if (not (high_score.contains(pseudo) and high_score[pseudo] >= my_game->get_score()))
                    high_score[pseudo] = my_game->get_score();
                assets->save_high_score(high_score);
                if (actions[core::QUIT])
                    break;
                if (actions[core::MENU])
                    break;
                if (actions[core::NEXT_GAME]) {
                    curr_game++;
                    std::string lib;
                    std::vector<std::string> game_libs;
                    std::ifstream file("./lib_list.yaml");
                    int __lib_i = 0;
                    if (not file.is_open())
                        std::__throw_system_error(2);
                    std::getline(file, lib);
                    while (not file.eof() and lib != "Game libs:") {
                        std::getline(file, lib);
                    }
                    if (file.eof())
                        std::__throw_system_error(61);
                    std::getline(file, lib);
                    while (not file.eof()) {
                        if (lib.length() < 1) {
                            std::getline(file, lib);
                            continue;
                        }
                        __lib_i++;
                        game_libs.push_back(lib.erase(0, 4));
                        std::getline(file, lib);
                        if (__lib_i == curr_game) {
                            game_lib.reset(new DLLoader<game::IGameModule>("./lib/" + lib.erase(0, 4)));
                            break;
                        }
                    }
                    if (__lib_i < curr_game) {
                        curr_game = 0;
                        game_lib.reset(new DLLoader<game::IGameModule>("./lib/" + game_libs[0]));
                    }
                    my_game = game_lib->getInstance("entryPoint");
                    break;
                }
                if (actions[core::NEXT_LIB]) {
                    curr_lib++;
                    std::string lib;
                    std::vector<std::string> graph_libs;
                    std::ifstream file("./lib_list.yaml");
                    int __lib_i = 0;
                    if (not file.is_open())
                        std::__throw_system_error(2);
                    std::getline(file, lib);
                    while (not file.eof() and lib != "Graphical libs:") {
                        std::getline(file, lib);
                    }
                    if (file.eof())
                        std::__throw_system_error(61);
                    std::getline(file, lib);
                    while (not file.eof() and lib != "Game libs:") {
                        if (lib.length() < 1) {
                            std::getline(file, lib);
                            continue;
                        }
                        __lib_i++;
                        graph_libs.push_back(lib.erase(0, 4));
                        std::getline(file, lib);
                        if (__lib_i == curr_lib) {
                            graph_lib.reset(new DLLoader<graphical::IDisplayModule>("./lib/" + lib.erase(0, 4)));
                            break;
                        }
                    }
                    if (__lib_i < curr_lib) {
                        curr_lib = 0;
                        graph_lib.reset(new DLLoader<graphical::IDisplayModule>("./lib/" + graph_libs[0]));
                    }
                    graph = graph_lib->getInstance("entryPoint");
                    break;
                }
                if (actions[core::RESET]) {
                    my_game->init(assets);
                    continue;
                }
                state = my_game->update(actions);
            } // LOOP GAME
            if (actions[core::QUIT])
                break;
            if (state == game::WIN) {
                graph->print_text("YOU WIN !!!");
                char key = graph->get_key();
                while (not (key == 27 or key == ' ' or key == 'q'))
                    key = graph->get_key();
                if (key == 'q' or key == 27) {
                    actions[core::QUIT] = true;
                    break;
                }
            }
            if (state == game::LOSE) {
                graph->print_text("GAME OVER !!!");
                char key = graph->get_key();
                while (not (key == 27 or key == ' ' or key == 'q'))
                    key = graph->get_key();
                if (key == 'q' or key == 27) {
                    actions[core::QUIT] = true;
                    break;
                }
            }
            if (actions[core::QUIT])
                break;
        }
    } catch (const game::GameError &e) {
        std::cerr << "Error with the game library : " << e.what() << std::endl;
        return 84;
    } catch (const graphical::GraphicalError &e) {
        std::cerr << "Error with the graphical library : " << e.what() << std::endl;
        return 84;
    } catch (const std::system_error &e) {
        std::cerr << "Error " << e.code() << " : " << e.what() << std::endl;
        return 84;
    } catch (const std::exception &e) {
        std::cerr << "Error : " << e.what() << std::endl;
        return 84;
    }
    return 0;
}
