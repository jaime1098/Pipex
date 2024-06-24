NAME = pipex

SRCS =	main.c pipex.c pipex_utils.c

OBJECTS = $(SRCS:.c=.o)

CFLAGS := -Wall -Wextra -Werror
REMOVE = rm -f
CC := cc

all: $(NAME)

$(NAME): $(OBJECTS) libft/libft.a
	$(CC) $(OBJECTS) libft/libft.a -o $(NAME)

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
	./$(NAME) Makefile ls grep -e outfile.txt

n: clear
	norminette

re: fclean all
	clear