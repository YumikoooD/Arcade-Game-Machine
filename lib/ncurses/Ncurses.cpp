/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-guillaume.deplaine
** File description:
** Ncurses
*/

#include <algorithm>
#include <curses.h>
#include "Ncurses.hpp"

Ncurses::Ncurses()
{
}

Ncurses::~Ncurses()
{
    endwin();
}

void Ncurses::init(std::shared_ptr<core::IAssetLoader> assets)
{
    __win = initscr();
    if (__win == nullptr)
        throw graphical::GraphicalError("Cannot open window");
    _assets = assets;
    cbreak();
    raw();
    set_name(assets->get_names());
    keypad(__win, TRUE);
    noecho();
    nodelay(__win, TRUE);
}

std::map<core::action, bool> Ncurses::update(void)
{
    clear();
    std::size_t char_len = _assets->get_textual(0, core::IAssetLoader::TEXTUAL).length();
    for (unsigned int line = 0; line < _assets->get_map().size(); line++) {
        for (unsigned int col = 0; col < _assets->get_map()[line].size(); col++) {
            mvwaddstr(__win, line, col * char_len,
                _assets->get_textual(_assets->get_map()[line][col], core::IAssetLoader::TEXTUAL).c_str());
        }
    }
    refresh();
    std::map<core::action, bool> map;
    int c = wgetch(__win);
    while (c and c != -1) {
        if (event(c).key != INVALID_ID)
            _set_map(map, event(c));
        c = wgetch(__win);
    }
    return map;
}

void Ncurses::_set_map(std::map<core::action, bool> &map, const event_t &e) const
{
    switch (e.key)
    {
        case core::ACTION:
            map[core::ACTION] = e.status;
            break;
        case core::UP:
            map[core::UP] = e.status;
            break;
        case core::DOWN:
            map[core::DOWN] = e.status;
            break;
        case core::RIGHT:
            map[core::RIGHT] = e.status;
            break;
        case core::LEFT:
            map[core::LEFT] = e.status;
            break;
        case core::NEXT_GAME:
            map[core::NEXT_GAME] = e.status;
            break;
        case core::NEXT_LIB:
            map[core::NEXT_LIB] = e.status;
            break;
        case core::RESET:
            map[core::RESET] = e.status;
            break;
        case core::QUIT:
            map[core::QUIT] = e.status;
            break;
        case core::MENU:
            map[core::MENU] = e.status;
            break;
        default:
            break;
    }
}

std::map<core::action, bool> Ncurses::print_text(const std::string &text)
{
    clear();
    waddstr(__win, text.c_str());
    refresh();
    std::map<core::action, bool> map;
    int c = wgetch(__win);
    while (c and c != -1) {
        if (event(c).key != INVALID_ID)
            _set_map(map, event(c));
        c = wgetch(__win);
    }
    return map;
}

event_t Ncurses::event(int c) const
{
    event_t e;

    switch (c) {
        case '1':
            e.key = 1;
            e.status = true;
            break;
        case '2':
            e.key = 2;
            e.status = true;
            break;
        case '3':
            e.key = 3;
            e.status = true;
            break;
        case '4':
            e.key = 4;
            e.status = true;
            break;
        case '5':
            e.key = 5;
            e.status = true;
            break;
        case '6':
            e.key = 6;
            e.status = true;
            break;
        case '7':
            e.key = 7;
            e.status = true;
            break;
        case '8':
            e.key = 8;
            e.status = true;
            break;
        case '9':
            e.key = 9;
            e.status = true;
            break;
        case KEY_NEXT:
        case KEY_NPAGE:
            e.key = NEXT_PAGE;
            e.status = true;
            break;
        case KEY_PREVIOUS:
        case KEY_PPAGE:
            e.key = PREV_PAGE;
            e.status = true;
            break;
        case KEY_RIGHT:
            e.key = core::RIGHT;
            e.status = true;
            break;
        case KEY_LEFT:
            e.key = core::LEFT;
            e.status = true;
            break;
        case KEY_UP:
            e.key = core::UP;
            e.status = true;
            break;
        case KEY_DOWN:
            e.key = core::DOWN;
            e.status = true;
            break;
        case 'q':
            e.key = core::QUIT;
            e.status = true;
            break;
        case KEY_F(1):
        case KEY_ESC:
            e.key = core::MENU;
            e.status = true;
            break;
        case ' ':
        case KEY_ENTER:
            e.key = core::ACTION;
            e.status = true;
            break;
        case 'r':
            e.key = core::RESET;
            e.status = true;
            break;
        case KEY_F(12):
            e.key = core::NEXT_GAME;
            e.status = true;
            break;
        case KEY_F(13):
            e.key = core::NEXT_LIB;
            e.status = true;
            break;
        default:
            break;
    }
    return e;
}

// Not sure it'll work but better than nothing
void Ncurses::set_name(const std::string &name)
{
    std::string print = "\x1b]2;" + name +"\x07";

    putp(print.c_str());
}

char Ncurses::get_key(void)
{
    char c = 0;
    while (not c or c == -1)
        c = wgetch(__win);
    return c;
}

// Not in the Ncurses class but in the ostream class
// If friend (autorise fonction to access private members) was present
// it would look better but be less secure
// Generated commented because interface or abstract class could implement it
std::ostream &operator<<(std::ostream &str, const Ncurses &ncurses)
{
    str << "<Ncurses (" << &ncurses << ")>";
    return str;
}
