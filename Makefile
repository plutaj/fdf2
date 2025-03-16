LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
MINILIBX_LINUX_DIR = minilibx-linux
MINILIBX_LINUX = $(MINILIBX_LINUX_DIR)/libmlx.a
MINILIBX_LINUX = $(MINILIBX_LINUX_DIR)/libmlx_Linux.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBS = -lmlx -lX11 -lXext -lm
INCLUDES = -I. -I$(LIBFT_DIR) -I$(MINILIBX_LINUX_DIR)

MAIN_SRC = 	main.c \
			process_map.c \
			bersen_alg.c \
			main_utils.c \
			process_map_utils.c \
			free_functions.c \
			bersen_alg_utils.c

MAIN_OBJ = $(MAIN_SRC:.c=.o)

MAIN_EXEC = fdf

all: $(MAIN_EXEC)

$(MAIN_EXEC): $(MAIN_OBJ) $(LIBFT) $(MINILIBX_LINUX)
	$(CC) $(MAIN_OBJ) $(LIBFT) -L$(MINILIBX_LINUX_DIR) $(LIBS) -o $(MAIN_EXEC)


%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(MINILIBX_LINUX):
	make -C $(MINILIBX_LINUX_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	make clean -C $(MINILIBX_LINUX_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(MAIN_EXEC) $(MAIN_OBJ)
	rm -f $(MINILIBX_LINUX) $(LIBFT)

re: fclean all

e: clean fclean

.PHONY: all clean fclean re
