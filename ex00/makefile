NAME = btc

CC = C++

CPPFLAGS = -Wall -Wextra -Werror -std=c++98 -fsanitize=address -g

RM = rm -rf

SRC = main.cpp BitcoinExchange.cpp
HFILE = BitcoinExchange.hpp

OBJ = $(SRC:%.cpp=%.o)

%.o:%cpp $(HFILE)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CPPFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: re clean fclean all