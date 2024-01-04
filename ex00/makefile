NAME = btc

CC = C++

CFLAGS = -Wall -Wextra -Werror -std=c++98

RM = rm -rf

SRC = main.cpp BitcoinExchange.cpp
HFILE = BitcoinExchange.hpp

OBJ = $(SRC:%.cpp=%.o)

%.o:%cpp $(HFILE)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: re clean fclean all