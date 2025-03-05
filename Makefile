LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
MINILIBX_MACOS_DIR = minilibx_macos
MINILIBX_MACOS = $(MINILIBX_MACOS_DIR)/libmlx.a
GET_NEXT_LINE_DIR = get_next_line
GET_NEXT_LINE_SRC = $(GET_NEXT_LINE_DIR)/get_next_line.c $(GET_NEXT_LINE_DIR)/get_next_line_utils.c

CC = cc
# CFLAGS = -Wall -Wextra -Werror
LIBS = -lmlx -framework OpenGL -framework AppKit
INCLUDES = -I. -I$(LIBFT_DIR) -I$(MINILIBX_MACOS_DIR) -I$(GET_NEXT_LINE_DIR)

MAIN_SRC = main.c process_map.c
MAIN_OBJ = $(MAIN_SRC:.c=.o)
GET_NEXT_LINE_OBJ = $(GET_NEXT_LINE_SRC:.c=.o)

MAIN_EXEC = fdf

all: $(MAIN_EXEC)

$(MAIN_EXEC): $(MAIN_OBJ) $(LIBFT) $(MINILIBX_MACOS) $(GET_NEXT_LINE_OBJ)
	$(CC) $(MAIN_OBJ) $(GET_NEXT_LINE_OBJ) $(LIBFT) -L$(MINILIBX_MACOS_DIR) $(LIBS) -o $(MAIN_EXEC)


%.o: %.c # $(CFLAGS) after CC
	$(CC) $(INCLUDES) -c $< -o $@

$(MINILIBX_MACOS):
	make -C $(MINILIBX_MACOS_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(GET_NEXT_LINE_OBJ): $(GET_NEXT_LINE_SRC)
	$(CC) $(INCLUDES) $(CFLAGS) -c $(GET_NEXT_LINE_DIR)/get_next_line.c -o $(GET_NEXT_LINE_DIR)/get_next_line.o
	$(CC) $(INCLUDES) $(CFLAGS) -c $(GET_NEXT_LINE_DIR)/get_next_line_utils.c -o $(GET_NEXT_LINE_DIR)/get_next_line_utils.o

clean:
	rm -f $(MAIN_OBJ) $(GET_NEXT_LINE_OBJ)
	make clean -C $(MINILIBX_MACOS_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(MAIN_EXEC)
	rm -f $(MINILIBX_MACOS) $(LIBFT)

re: fclean all

e: clean fclean

.PHONY: all clean fclean re
