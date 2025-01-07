NAME = minishell

CC = cc -g -Wall -Wextra -Werror

RM = rm -f

SRC = main.c externs/externs.c externs/externs_utils.c

OBJ = ${SRC:.c=.o}

LIBFT_PATH = libft/
LIBFT = $(LIBFT_PATH)libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

%.o: %.c
	$(CC) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_PATH)

clean:
	$(RM) $(OBJ)
	make -C $(LIBFT_PATH) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re