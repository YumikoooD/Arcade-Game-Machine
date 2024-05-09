# Arcade - A Retro Gaming Platform

![arcade](gif/pacman.gif)

Arcade is a retro gaming platform that allows users to choose and play classic arcade games while keeping track of player scores. It is designed to support various graphics libraries and game options, offering users a diverse selection of gaming experiences.

## Features

- **Dynamic Libraries**: Graphics libraries and games are implemented as dynamic libraries, loaded at runtime. Each GUI and game available is used as a shared library, providing flexibility and extensibility.
- **Multiple Graphics Libraries**: Supports popular graphics libraries such as nCurses, SDL2, and more, allowing users to choose their preferred graphical interface.
- **Variety of Games**: Offers a selection of classic arcade games including Snake, Nibbler, Pacman, Qix, Centipede, and Solarfox.
- **Customization**: Users can switch between different graphics libraries and games at runtime, providing a customizable gaming experience.
- **Scoring System**: Keeps track of player scores across different games, allowing users to compete for high scores.

## Usage

To start Arcade, run the following command:

```
./arcade <path_to_graphics_library.so>
```

Replace `<path_to_graphics_library.so>` with the path to the desired graphics library shared object file.

### Controls

- **Next Graphics Library**: Navigate to the next available graphics library.
- **Next Game**: Switch to the next available game.
- **Restart Game**: Restart the current game.
- **Go Back to Menu**: Return to the main menu.
- **Exit**: Quit the Arcade platform.

## Build

You can build the project using a Makefile. Ensure that you have the necessary dependencies installed for your chosen graphics libraries and games (SFML, SDL2 and ncurse).

### Makefile

- `make all`: Build the core of Arcade, graphics libraries, and game libraries.
- `make clean`: Remove generated object files.
- `make fclean`: Remove generated object files and executable.
- `make re`: Rebuild the project from scratch.
