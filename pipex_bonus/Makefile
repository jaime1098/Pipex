NAME = pipex_bonus	

SRCS =	main.c pipex_bonus.c pipex_bonus_utils.c heredoc.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

OBJECTS = $(SRCS:.c=.o)

CFLAGS := -Wall -Wextra -Werror -g3
REMOVE = rm -f
CC := cc

all: $(NAME)

$(NAME): $(OBJECTS) libft/libft.a
	$(CC) -g3 $(OBJECTS) libft/libft.a -o $(NAME)

libft/libft.a:
	make -C libft/
	@echo "Make libft"

.c.o:
		$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean:
	$(REMOVE) $(OBJECTS)
	make -C libft/ fclean

fclean: clean
	$(REMOVE) $(NAME)
	clear

clear:
	clear

run: re clear
	./$(NAME) Makefile ls ls /dev/stdout

n: clear
	norminette

re: fclean all
	clear