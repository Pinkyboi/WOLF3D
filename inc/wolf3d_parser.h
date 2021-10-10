/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_parser.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:52:05 by abenaiss          #+#    #+#             */
/*   Updated: 2021/05/20 20:25:40 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_PARSER_H
# define WOLF3D_PARSER_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <limits.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <pthread.h>

# define ALPHA "qwertyuiopasdfghjklzxcvbnm"
# define ALPHA_NUM "0123456789qwertyuiopasdfghjklzxcvbnm"
# define NUM_FILTER "1234567890"
# define HEX_FILTER "0123456789abcdef"
# define WHITE_SPACES " \n\t\r\v\f"
# define MAX_COLOR_VALUE 16777215
# define LEGAL_BRACKETS "()"
# define WHITE_SPACE_AND_LEGAL_BRACKETS " \n\t\r\v\f()"
# define CURLY_BRACKETS "{}"
# define WHITE_SPACE_AND_CURLY_BRACKETS " \n\t\r\v\f{}"
# define ARGUMENT_DELIMITER ';'

# define RENDER_TAG "<render>"
# define WINDOW_TAG "<window>"
# define PLAYER_TAG "<player>"
# define MONSTER_TAG "<monster>"
# define ENV_TAG "<env>"
# define MAP_TAG "<map>"
# define SPITE_TAG "<sprite>"
# define END_TOKEN "endl"

# define NORTH_COLOR "#72147E"
# define SOUTH_COLOR "#F21170"
# define EAST_COLOR "#FA9905"
# define WEST_COLOR "#FF5200"
# define SKY_COLOR "#87CEEB"

# define MAX_HP 100
# define MIN_HP 1
# define MAX_STAMINA 100
# define MIN_STAMINA 1

# define FILLER_COLOR 0x444444
# define FILLER_ICON '@'

# define WIRE_EDGE_COLOR "#fb9300"
# define WIRE_INNER_COLOR "#343f56"
# define WIRE_MAIN_COLOR "#000000"

# define NUM_THREAD 4

typedef struct s_coor
{
	int					x;
	int					y;
}						t_coor;

typedef struct s_d_coor
{
	double				x;
	double				y;
}						t_d_coor;

typedef struct s_tag_element
{
	char				*tag_name;
	void				*function;	
}						t_tag_element;

typedef struct s_texture
{
	t_d_coor			coordinates;
	int					*texture_data;
	int					texture_width;
	int					texture_height;
}						t_texture;

typedef union u_render
{
	t_texture			texture;
	int					color;
}						t_render;

typedef struct s_mlx_img
{
	void				*img_ptr;
	int					*img_data;
	int					size_l;
	int					bpp;
	int					endian;
}						t_mlx_img;

typedef struct s_mlx
{
	void				*mlx_ptr;
	void				*mlx_win;
	t_mlx_img			mlx_img;
}						t_mlx;

typedef struct s_game_object	t_game_object;
typedef void					t_block_render_function(
									t_game_object *game_object,
									t_render data);

typedef struct s_render_tools
{
	t_render				render_data;		
	t_block_render_function	*render_function;
}							t_render_tools;

typedef struct s_block_list
{
	char				type;
	char				block_icon;
	t_render_tools		render;
	struct s_block_list	*next;
}						t_block_list;

typedef struct s_argument_list
{
	char					*argument_name;
	char					*argument_value;
	struct s_argument_list	*next;
}							t_argument_list;

typedef struct s_tile
{
	t_block_list		*wall;
	t_block_list		*floor;
	t_block_list		*ceiling;
}						t_tile;

typedef struct s_map
{
	t_coor				map_dimentions;
	t_tile				**map_grid;
}						t_map;

typedef struct s_player
{
	t_coor				grid_position;
	t_d_coor			world_position;
	t_d_coor			movement;
	short				hp;
	short				stamina;
	short				is_running;
	int					*player_appearance;
	double				step;
	double				height;
	double				view_distance;
	double				orientation;
}						t_player;

typedef void					t_game_rendering(t_game_object *game_object);

typedef struct s_render_recognition
{
	char				*render_type;
	t_game_rendering	*rendering_function;
}						t_render_recognition;

typedef struct s_view
{
	double				vertical_tilt;
	int					view_plane_distance;
	int					view_shift;
	int					half_view_plane;
	int					half_view_plane_save;
	int					horizontal_step;
}						t_view;

typedef struct s_skybox
{
	t_render_tools		sky;
	double				texture_step;
	double				win_per_rad;
	double				tex_per_rad;
}						t_skybox;

typedef struct s_basic_render
{
	t_render_tools		north_wall;
	t_render_tools		south_wall;
	t_render_tools		east_wall;
	t_render_tools		west_wall;
}						t_basic_render;

typedef struct s_wire_render
{
	int					edge_color;
	int					inner_color;
	int					void_color;
}						t_wire_render;

typedef struct s_render_data
{
	t_game_rendering	*render_function;
	t_view				view_data;
	t_coor				window_resolution;
	t_basic_render		basic_render;
	t_wire_render		wire_render;
	t_skybox			skybox;
	t_mlx				mlx;
}						t_render_data;

typedef struct s_wolf3d_parser
{
	t_block_list		*block_list;
	t_argument_list		*current_arguments;
}						t_wolf3d_parser;

typedef struct s_ray_data
{
	double				hit_distance;
	double				straight_distance;
	double				angle;
	char				hit_type;
	t_d_coor			current_ray;
}						t_ray_data;

typedef struct s_mini_map
{
	t_d_coor			center_position;
	int					total_radius;
	int					ring_size;
	int					radius;
	int					block_size;
	int					player_size;
}						t_mini_map;

typedef struct s_sprite_list
{
	short					side_number;
	t_texture				texture;
	t_coor					position;
	struct s_sprite_list	*next;
}							t_sprite_list;

struct s_game_object
{
	t_wolf3d_parser		parser;
	t_render_data		render_data;
	t_map				map;
	t_sprite_list		*sprite_list;
	t_player			player;
	t_ray_data			ray_data;
	t_mini_map			min_map;
	t_coor				drawing_index;
	int					drawing_width_end;
	t_block_list		*current_block;
};

typedef void					t_block_parsing_function(
									t_game_object *game_object,
									char *argument_block);

typedef struct s_tag_recognition
{
	char						*tag_name;
	t_block_parsing_function	*parsing_function;
}								t_tag_recognition;

int					ft_isdigit(int c);
int					ft_row_len(char **array);
int					ft_hex_to_int(char *number);
int					ft_hex_to_color(char *color);
int					ft_stock_hex(char *color, int *color_stock);
int					ft_mini_brackets(char *string, char *bracket);
int					ft_parse_counters(char *counter, int min, int max);
int					ft_load_texture(char *path, t_texture *texture_data);

char				*ft_trim(char *string, char *filter);
char				*ft_strnclone(char *string, int size);
char				*ft_read_file(int fd);
char				*ft_get_argument(char *argument_name, char *default_value,
						t_argument_list *argument_list);
char				**ft_parse_block_tuple(char *tuple);
char				**ft_parse_block_arg(char *block_infos, char *tag);

void				ft_err_print(char *error, char *position);
void				ft_check_number(char *string);
void				ft_free_array(char **array);
void				ft_insert_argument_block_infos(t_tile *map_tile,
						t_block_list *block_list, char *argument);
void				ft_insert_tuple_block_infos(t_tile *map_tile,
						t_block_list *block_list, char **args);
void				ft_load_env_block_data(t_game_object *game_object,
						char *argument_block);
void				ft_load_game_elements(char *string,
						t_game_object *game_object);
void				ft_load_map_data(t_game_object *game_object,
						char *argument_block);
void				ft_load_player_data(t_game_object *game_object,
						char *argument_block);
void				ft_load_render_data(t_game_object *game_object,
						char *argument_block);
void				ft_load_sprite_data(t_game_object *game_object,
						char *argument_block);
void				ft_calculate_map_props(t_game_object *game_object);
void				ft_free_argument_list(t_argument_list *argument_list);
void				ft_safe_trim(char *line, char *filter);
void				*ft_safe_malloc(size_t size);

t_game_rendering	*ft_parse_render_type(char *render_type);

t_coor				ft_parse_resolution(char *resolution_expression);
t_coor				ft_parse_coordinate(char *tuple);
t_coor				ft_map_max_dim(char **map);

t_render_tools		ft_parse_render(char *render_argument);
t_render_tools		ft_parse_sky_render(char *render_argument,
						t_game_object *game_object);

t_block_list		*ft_create_block_node(char type, char icon,
						t_render render_data, void *function);
t_block_list		*ft_push_block(t_block_list *block_list,
						t_block_list *new_element);
t_block_list		*ft_find_block_node(t_block_list *block_list, char icon);

t_tile				**ft_create_raw_map(t_tile **map, t_block_list *block_list,
						t_coor dimentions);
t_tile				**ft_create_map(char **map, t_block_list *block_list);

t_argument_list		*ft_create_agument_node(char *argument_name,
						char *argument_value);
t_argument_list		*ft_create_argument_list(char *argument_block,
						t_argument_list *argument_list, char *tag);
t_argument_list		*ft_find_argument_node(t_argument_list *argument_list,
						char *argument_name);
t_argument_list		*ft_push_argument(t_argument_list *argument_list,
						t_argument_list *new_element);
#endif