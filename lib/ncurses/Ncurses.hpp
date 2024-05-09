/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-guillaume.deplaine
** File description:
** Ncurses
*/

#ifndef NCURSES_HPP_
    #define NCURSES_HPP_

#include <ostream>
#include <map>
#include <curses.h>
#include "Graphical.hpp"

#ifndef INVALID_ID
    #define INVALID_ID -1
#endif

#ifndef PREV_PAGE
    #define PREV_PAGE INVALID_ID
#endif

#ifndef NEXT_PAGE
    #define NEXT_PAGE INVALID_ID
#endif

#ifndef KEY_ESC
    #define KEY_ESC 27
#endif

class event_t {
    public:
        int key = INVALID_ID; // Return type of getch
        bool status = false; // Return type of get_action
};

class Ncurses : public graphical::IDisplayModule {
    public:
        Ncurses();
        ~Ncurses();
        void init(std::shared_ptr<core::IAssetLoader> assets) override;
        std::map<core::action, bool> update(void) override;
        void set_name(const std::string&) override;
        std::map<core::action, bool> print_text(const std::string &text) override;
        char get_key(void) override;
    protected:
        std::shared_ptr<core::IAssetLoader> _assets;
        WINDOW *__win;
        event_t event(int c) const;
        void _set_map(std::map<core::action, bool> &map, const event_t &e) const;
};

// Generated commented because interface or abstract class could implement it
std::ostream &operator<<(std::ostream &str, const Ncurses &ncurses);

#endif /* !NCURSES_HPP_ */
