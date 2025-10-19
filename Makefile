# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsilva <tsilva@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/07 10:08:14 by tsilva            #+#    #+#              #
#    Updated: 2025/09/25 15:10:37 by tsilva           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
LIBFT_NAME = libft.a
MLX_NAME = libmlx_Linux.a

SRC_DIR = ./src
INC_DIR = ./inc
OBJ_DIR = ./obj

LIB_DIR = ./lib/libft
MLX_DIR = ./lib/mlx

CC = cc
CFLAGS = -Wall -Wextra -Werror -I $(INC_DIR) -MMD -MP -g
MLX_FLAGS = -L $(MLX_DIR) -lmlx -lXext -lX11 -lm

DARK_GRAY = \033[1;90m
NO_COLOR = \033[0m
MSG_SYS = \033[1;94m[${NAME}]${NO_COLOR}

# ---------- SOURCES ----------
SRC =	cub3d.c \
		cub3d_utils.c \
		cub3d_init.c \
		free.c \
		game_core/core_init.c \
		game_core/game.c \
		game_core/event_handlers.c \
		game_core/player.c \
		game_core/game_aux.c \
		game_core/door.c \
		game_core/mouse.c \
		parser_and_validation/parser_map.c \
		parser_and_validation/parser_scene.c \
		parser_and_validation/parser_utils.c \
		parser_and_validation/validate_map.c \
		parser_and_validation/validate_scene.c \
		parser_and_validation/validate_aux.c \
		parser_and_validation/ft_split_whitespace.c \
		rendering/3d_render.c \
		rendering/raycaster.c \
		rendering/3d_render_aux.c \
		rendering/3d_render_aux_FC.c \
		rendering/minimap.c \
		rendering/transparent.c \
		rendering/banner.c \
		gnl/get_next_line.c \
		gnl/get_next_line_utils.c

OBJS = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

LIBFT = $(LIB_DIR)/$(LIBFT_NAME)
MLX = $(MLX_DIR)/$(MLX_NAME)

DEPS = $(OBJS:.o=.d)

# ---------- TARGETS ----------
all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@echo "${MSG_SYS} Linking objects..."
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(NAME)
	@echo "${MSG_SYS} Build complete !"


# ---------- RULES ----------
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@echo "${DARK_GRAY}[${NAME}] Compiling $<${NO_COLOR}"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@echo "${MSG_SYS} Building libft..."
	@make -s -C $(LIB_DIR)

$(MLX):
	@echo "${MSG_SYS} Building MiniLibX..."
	@make -s -C $(MLX_DIR)

clean:
	@echo "${MSG_SYS} Cleaning up..."
	@rm -rf $(OBJ_DIR)
	@make -s -C $(LIB_DIR) clean
	@make -s -C $(MLX_DIR) clean
	@echo "${MSG_SYS} Objects removed."

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIB_DIR)/$(LIBFT_NAME)
	@echo "${MSG_SYS} Binaries and libraries have been removed."

re: fclean all

check_norm:
	@echo "${MSG_SYS} Checking the LIBFT library...${DARK_GRAY}"
	@norminette ${LIB_DIR}/src
	@echo "${MSG_SYS} Checking headers...${DARK_GRAY}"
	@norminette ${INC_DIR}
	@echo "${MSG_SYS} Checking sources...${DARK_GRAY}"
	@norminette ${SRC_DIR}
	@echo "${NO_COLOR}"

.PHONY: all clean fclean re check_norm

# ---------- DEPENDENCES ----------
-include $(DEPS)