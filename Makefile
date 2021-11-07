# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/10 12:52:05 by abenaiss          #+#    #+#              #
#    Updated: 2021/11/07 18:32:52 by abenaiss         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

CC =gcc
CFLAGS = -g -Wall -Wextra -Werror

SRC_DIR =./src/
OBJ_DIR =./obj/
LIBFT_DIR =./libft
LIBFT_H = $(LIBFT_DIR)/inc
INC_DIR =./inc/

FILES_NAME =main.c\
			fill_blocks.c\
			parse_colors.c\
			read_file.c\
			array_utils.c\
			type_tests.c\
			map_creation.c\
			parse_argment.c\
			parse_methadata.c\
			parse_env_data.c\
			parse_tuple.c\
			parsing_utils.c\
			gameobject_constructor.c\
			argument_list.c\
			clip_values.c\
			colors.c\
			dda.c\
			dda_helper.c\
			vector2D.c\
			angles.c\
			manage_mlx.c\
			movement.c\
			texture_walls.c\
			color_walls.c\
			ray_caster.c\
			texture_tiles.c\
			key_state.c\
			mini_map.c\
			sky_render.c\
			ui_constructor.c\
			mini_map_tools.c\
			bresenham.c\
			wireframe_render.c\
			wireframe_tiles.c\
			render_constructor.c\
			ray_shooter.c\
			game_loop.c\

OBJS = $(addprefix $(OBJ_DIR), $(FILES_NAME:.c=.o))
SRCS = $(addprefix $(SRC_DIR),$(FILES_NAME))
HEADER_FILE = wolf3d.h

INCLUDES = -I $(INC_DIR) -I $(LIBFT_H) -I ./mlx
LIBRARIES = -L $(LIBFT_DIR) -lft -L./mlx -lmlx -framework OpenGL -framework AppKit

all: $(NAME)
$(NAME) : $(OBJS)
	@make -sC $(LIBFT_DIR)
	@$(CC) $(INCLUDES) $(LIBRARIES) $(OBJS) -o $@
$(OBJS) : $(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR) $(INCLUDES)
$(OBJ_DIR) :
	@mkdir $(OBJ_DIR)
clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -rf $(NAME)

re: fclean all
