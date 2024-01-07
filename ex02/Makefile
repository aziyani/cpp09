NAME =  pmergeme

CC = C++

FLAGS = -Wall -Wextra -Werror -std=c++98

RM = rm -rf

SRC = main.cpp Pmergeme.cpp
HFILE = Pmergeme.hpp

OBJ = $(SRC:%.cpp=%.o)

%.o:%.cpp $(HFILE)
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: re clean fclean all