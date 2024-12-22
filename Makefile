NAME = libft-tests

CC = clang

FLAGS = -Wall -Wextra -Werror -I./../ -g

SRC = main.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) -L./../ -l:libft.a

clean:
	rm -f $(OBJ)

fclean: clean
	rm -r $(NAME)

re: fclean all
