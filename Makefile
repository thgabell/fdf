CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -g
NAME	= fdf

SRC_PATH = srcs/
OBJ_PATH = objs/

SRCS	= main.c init.c
OBJS	= $(addprefix $(OBJ_PATH), $(SRCS:.c=.o))

INC_ARG = -I./includes
LIBFT_INC = -I./libft/includes
LIBFT_FLAGS = -L./libft -lft
LIBFT = libft/libft.a
MLX = minilibx-linux/libmlx.a
MLX_INC = -I./minilibx-linux
MLX_FLAGS = -L./minilibx-linux -lmlx -lXext -lX11

all: $(OBJ_PATH) $(NAME)

$(LIBFT):
	@make -C libft

$(MLX):
	@make -C minilibx-linux

$(OBJ_PATH):
	@mkdir $@

$(NAME): $(OBJ_PATH) $(OBJS) $(LIBFT) $(MLX)
	@$(CC) -g $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT_FLAGS) $(MLX_FLAGS)
	@echo "Creating $@..."

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(INC_ARG) $(LIBFT_INC) $(MLX_INC) -o $@ -c $<
	@echo "Creating $@... "

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all