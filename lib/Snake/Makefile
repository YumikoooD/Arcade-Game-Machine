##
## EPITECH PROJECT, 2024
## NAME
## File description:
## makefile
##

CC ?= g++

SRC = snake.cpp	\
	  movement.cpp 	\
	  entry.cpp	\

CXFLAGS += -Wall -Wextra -std=c++20 -Werror -g3

INCLUDE_DIR += . ../../include ../../

CPPFLAGS += $(foreach inc, $(INCLUDE_DIR), -iquote$(inc)) -std=c++20 -fPIC -g3

OBJ = $(SRC:.cpp=.o)

NAME = arcade_snake.so

DESTINATION_FOLDER = ..

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) --shared $(OBJ) -o $(NAME) $(CXFLAGS) $(CPPFLAGS) \
	-lstdc++
	cp $(NAME) $(DESTINATION_FOLDER)/$(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST_NAME)
	rm -f $(DESTINATION_FOLDER)/$(NAME)

re: fclean all

.PHONY	: clean fclean re all
