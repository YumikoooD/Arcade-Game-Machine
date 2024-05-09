##
## EPITECH PROJECT, 2024
## NAME
## File description:
## makefile
##

CC ?= g++

SRC = AssetLoader.cpp

MAIN = main.cpp

CFLAGS += -Wall -Wextra -std=c++20 -Werror -g3 -fno-gnu-unique

INCLUDE_DIR += . include

CPPFLAGS += $(foreach inc, $(INCLUDE_DIR), -iquote$(inc)) -std=c++20 -g3

OBJ = $(SRC:.cpp=.o)

LIB += dl

LIB_DIR +=

GRAPHICAL_LIB_TO_MAKE += lib/ncurses		\
						 lib/SFML			\
						 lib/SDL2			\

GAME_LIB_TO_MAKE += lib/Snake lib/Nibbleur

LIB_TO_MAKE += $(GAME_LIB_TO_MAKE) $(GRAPHICAL_LIB_TO_MAKE)

LDFLAGS += $(foreach lib, $(LIB_DIR), -L$(lib))
LDLIBS += $(foreach lib, $(LIB), -l$(lib))

TEST_DIR = tests

TEST_SRC =

TEST_FILES += $(foreach file, $(TEST_SRC), $(TEST_DIR)/$(file))

TEST_FLAGS += --coverage -lcriterion

TEST_NAME = unit_tests

NAME = arcade

all: make_lib $(NAME)

make_lib:
	$(foreach lib, $(LIB_TO_MAKE), make -i -C $(lib);)

games:
	$(foreach lib, $(GAME_LIB_TO_MAKE), make -i -C $(lib);)

graphicals:
	$(foreach lib, $(GRAPHICAL_LIB_TO_MAKE), make -i -C $(lib);)

core: $(OBJ) $(MAIN:.cpp=.o)
	$(CC) $(OBJ) $(MAIN:.cpp=.o) -o $(NAME) $(CXFLAGS) $(CPPFLAGS)\
	$(LDFLAGS) $(LDLIBS) -lstdc++

$(NAME): $(OBJ) $(MAIN:.cpp=.o)
	$(CC) $(OBJ) $(MAIN:.cpp=.o) -o $(NAME) $(CXFLAGS) $(CPPFLAGS)\
	$(LDFLAGS) $(LDLIBS) -lstdc++

clean:
	$(foreach lib, $(LIB_TO_MAKE), make clean -i -C $(lib);)
	rm -f $(OBJ)
	rm -f $(MAIN:.cpp=.o)

fclean: clean
	$(foreach lib, $(LIB_TO_MAKE), make fclean -i -C $(lib);)
	rm -f $(NAME)
	rm -f $(TEST_NAME)

re: fclean all

tests: make_lib $(OBJ)
	$(CC) $(OBJ) $(TEST_FILES) -o $(TEST_NAME) $(CXFLAGS) $(CPPFLAGS)\
	$(LDFLAGS) $(LDLIBS) $(TEST_FLAGS)

tests_run: tests
	./$(TEST_NAME)
	gcovr --exclude tests/
	gcovr --exclude tests/ -b

.PHONY	: clean fclean re all make_lib tests tests_run core games graphicals
