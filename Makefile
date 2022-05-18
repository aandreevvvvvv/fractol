NAME=fractol
CC=clang
CFLAGS=-Wall -Wextra -Werror -g -MMD

SRC_FILES=main.c \
		parse.c \
		utils.c \
		formulas.c \
		draw.c \
		mlx.c \
		complex.c
SRC_DIR=src
SRC=$(addprefix $(SRC_DIR)/,$(SRC_FILES))

OBJ_DIR=obj
OBJ=$(addprefix $(OBJ_DIR)/,$(SRC_FILES:.c=.o))

DEP=$(addprefix $(OBJ_DIR)/,$(SRC_FILES:.c=.d))

INC_FILES=fractol.h
INC_DIR=include
CFLAGS+=-I $(INC_DIR)

MLX_OBJ_FLAGS=-Imlx
MLX_NAME_FLAGS=-Lmlx -lmlx -framework OpenGL -framework AppKit

LIBFT_DIR=libft/
LIBFT_NAME=ft
LIBFT=libft/libft.a

CFLAGS+= -I $(LIBFT_DIR)

all: mlx libft $(NAME)

bonus: all

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(MLX_NAME_FLAGS) -L $(LIBFT_DIR) -l $(LIBFT_NAME) -o $(NAME)

-include $(DEP)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(MLX_OBJ_FLAGS) -c $< -o $@

mlx:
	make -C mlx

libft:
	make -C libft

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)
	make -C libft clean

fclean: clean
	rm -rf $(NAME)
	make -C libft fclean

re: fclean all

.PHONY : all clean fclean re bonus mlx libft
