NAME = pipex
NAME_BONUS = .pipex_bonus

CC := cc
CFLAGS := -Wall -Wextra -Werror -g3
REMOVE := rm -f

SRCS_NORMAL = src/pipex/main.c \
              src/pipex/pipex.c \
              src/pipex/pipex_utils.c

SRCS_BONUS = src/pipex_bonus/main_bonus.c \
             src/pipex_bonus/pipex_bonus.c \
             src/pipex_bonus/pipex_bonus_utils.c \
             src/pipex_bonus/heredoc.c \
             src/pipex_bonus/get_next_line/get_next_line.c \
             src/pipex_bonus/get_next_line/get_next_line_utils.c

OBJECTS_NORMAL = $(SRCS_NORMAL:.c=.o)
OBJECTS_BONUS = $(SRCS_BONUS:.c=.o)

# Objetivo por defecto
all: $(NAME)

# Pipex normal
$(NAME): $(OBJECTS_NORMAL) libft/libft.a
	$(CC) $(CFLAGS) $(OBJECTS_NORMAL) libft/libft.a -o $(NAME)

# Pipex bonus
bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJECTS_BONUS) libft/libft.a
	@$(CC) $(CFLAGS) $(OBJECTS_BONUS) libft/libft.a -o $(NAME)
	@touch $(NAME_BONUS)

# Librería libft
libft/libft.a:
	@make -sC libft/
	@echo "Make libft"

# Regla genérica para compilación de objetos
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpieza
clean:
	@$(REMOVE) $(OBJECTS_NORMAL) $(OBJECTS_BONUS)
	@make -sC libft/ clean
	@rm -f $(NAME_BONUS)

fclean: clean
	@$(REMOVE) $(NAME) $(NAME_BONUS)
	@make -sC libft/ fclean

re: fclean all

# Atajos y utilidades
run: re clear
	./$(NAME) Makefile ls ls /dev/stdout

clear:
	clear

n: clear
	norminette

.PHONY: all bonus clean fclean re run clear n