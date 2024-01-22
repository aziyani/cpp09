NAME =  RPN

CC = C++

RM = rm -f

FLAGS = -Wall -Wextra -Werror -std=c++98

SRC = main.cpp RPN.cpp
HFILE = RPN.hpp

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