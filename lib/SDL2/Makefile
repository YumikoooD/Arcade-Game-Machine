##
## EPITECH PROJECT, 2024
## NAME
## File description:
## makefile
##

CC ?= g++

SRC = Sdl.cpp\
      entry.cpp

CXXFLAGS += -Wall -Wextra -std=c++20 -Werror -g3

INCLUDE_DIR += . ../../include /usr/include/SDL2

CPPFLAGS += $(foreach inc, $(INCLUDE_DIR), -iquote$(inc)) -std=c++20 -fPIC \
	-g3 `sdl2-config --cflags`

OBJ = $(SRC:.cpp=.o)

LIB += SDL2 SDL2_image SDL2_ttf

LIB_DIR += /usr/lib

LIB_TO_MAKE +=

LDFLAGS += $(foreach lib, $(LIB_DIR), -L$(lib)) `sdl2-config --libs`
LDLIBS += $(foreach lib, $(LIB), -l$(lib))

TEST_DIR = tests

TEST_SRC =

TEST_FILES += $(foreach file, $(TEST_SRC), $(TEST_DIR)/$(file))

TEST_FLAGS += --coverage -lcriterion

TEST_NAME = unit_tests

NAME = arcade_sdl2.so

DESTINATION_FOLDER = ..

all: make_lib $(NAME)

make_lib:
	$(foreach lib, $(LIB_TO_MAKE), make -i -C $(lib);)

$(NAME): $(OBJ)
	$(CC) --shared $(OBJ) -o $(NAME) $(CXXFLAGS) $(CPPFLAGS)\
	$(LDFLAGS) $(LDLIBS) -lstdc++ -Wl,-rpath,$(LIB_DIR)
	cp $(NAME) $(DESTINATION_FOLDER)/$(NAME)

clean:
	$(foreach lib, $(LIB_TO_MAKE), make clean -i -C $(lib);)
	rm -f $(OBJ)

fclean: clean
	$(foreach lib, $(LIB_TO_MAKE), make fclean -i -C $(lib);)
	rm -f $(NAME)
	rm -f $(TEST_NAME)
	rm -f $(DESTINATION_FOLDER)/$(NAME)

re: fclean all

tests: make_lib $(OBJ)
	$(CC) $(OBJ) $(TEST_FILES) -o $(TEST_NAME) $(CXXFLAGS) $(CPPFLAGS)\
	$(LDFLAGS) $(LDLIBS) $(TEST_FLAGS)

tests_run: tests
	./$(TEST_NAME)
	gcovr --exclude tests/
	gcovr --exclude tests/ -b

.PHONY: clean fclean re all make_lib tests tests_run
