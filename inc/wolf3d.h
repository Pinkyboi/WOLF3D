/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:52:05 by abenaiss          #+#    #+#             */
/*   Updated: 2021/04/30 23:10:11 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"
#include "mlx.h"
#include <math.h>
#include <limits.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ALPHA "qwertyuiopasdfghjklzxcvbnm"
#define ALPHA_NUM "0123456789qwertyuiopasdfghjklzxcvbnm"
#define NUM_FILTER "1234567890"
#define HEX_FILTER "0123456789abcdef"
#define WHITE_SPACES " \n\t\r\v\f"
#define MAX_COLOR_VALUE 16777215
#define LEGAL_BRACKETS "()"
#define WHITE_SPACE_AND_LEGAL_BRACKETS " \n\t\r\v\f()"
#define CURLY_BRACKETS "{}"
#define WHITE_SPACE_AND_CURLY_BRACKETS " \n\t\r\v\f{}"
#define ARGUMENT_DELIMITER ';'

#define RENDER_TAG "<render>"
#define WINDOW_TAG "<window>"
#define PLAYER_TAG "<player>"
#define MONSTER_TAG "<monster>"
#define ENV_TAG "<env>"
#define MAP_TAG "<map>"
#define END_TOKEN "endl"

#define NORTH_COLOR "#72147E"
#define SOUTH_COLOR "#F21170"
#define EAST_COLOR "#FA9905"
#define WEST_COLOR "#FF5200"

#define	MAX_HP 100
#define MIN_HP 1
#define MAX_STAMINA 100
#define MIN_STAMINA 1

#define FILLER_COLOR 0x444444
#define	FILLER_ICON '@'

typedef struct			s_coor
{
	int					x;
	int 				y;
}						t_coor;

typedef struct			s_tag_element
{
	char				*tag_name;
	void				*function;	
}						t_tag_element;

typedef struct			s_texture
{
	int 				*texture_data;
	int					texture_width;
	int					texture_height;
}						t_texture;

typedef	union			u_render
{
	t_texture			texture;
	int					color;
}						t_render;

typedef struct			s_render_tools
{
	t_render			render_data;		
	void				*render_function;
}						t_render_tools;

typedef struct			s_block_list
{
	char				type;
	char				block_icon;
	t_render_tools		render;
	struct s_block_list	*next;
}				t_block_list;

typedef struct			s_argument_list
{
	char				*argument_name;
	char				*argument_value;
	struct s_argument_list	*next;
}				t_argument_list;

typedef struct 			s_tile
{
	t_block_list    	*wall;
	t_block_list    	*floor;
	t_block_list    	*ceiling;
}               		t_tile;


typedef struct			s_mlx_img
{
	void				*mlx_ptr;
	void				*mlx_img;
	void				*img_ptr;
	int					size_l;
	int					bpp;
	int					endian;
}						t_mlx_img;

typedef struct			s_map
{
	t_coor				map_dimentions;
	t_tile				**map_grid;
}						t_map;

typedef	struct			s_player
{
	t_coor				grid_postion;
	t_coor				world_postion;
	short				hp;
	short				stamina;
	char				*player_appearance;
	
}						t_player;

typedef void			t_game_rendering(void);

typedef struct			s_render_recognition
{
	char				*render_type;
	t_game_rendering	*rendering_function;
}						t_render_recognition;

typedef	struct			s_render_data
{
	t_game_rendering	*render_function;
	char				*widnow_name;
	t_coor				window_resolution;
	t_render_tools		north_wall;
	t_render_tools		south_wall;
	t_render_tools		east_wall;
	t_render_tools		west_wall;
	t_mlx_img			mlx;
}						t_render_data;

typedef	struct			s_game_object
{
	t_block_list		*block_list;
	t_argument_list		*current_arguments;
	t_render_data		render_data;
	t_map				map;
	t_player			player;
}						t_game_object;

typedef void			t_block_parsing_function(t_game_object *game_object, char *agrument_block);

typedef struct			s_tag_recognition
{
	char						*tag_name;
	t_block_parsing_function	*parsing_function;
}						t_tag_recognition;


int				isdigit(int c);
int				row_len(char **array);
int				row_len(char **array);
int				hex_to_int(char *number);
int 			hex_to_color(char *color);
int				stock_hex(char *color, int *color_stock);
int				mini_brackets(char *string, char *bracket);
int  			parse_counters(char *counter, int min, int max);

char			*trim(char *string, char *filter);
char			*ft_strnclone(char *string, int size);
char    		*read_file(int fd);

char			**parse_block_tuple(char *tuple);
t_coor			parse_resolution(char *resolution_expression);
char			**parse_argument_blocks(char *block_infos, char *tag);

void    		error_print(char *error, char *position);
void    		check_if_alpha(char *string);
void    		check_if_number(char *string);
void			free_array(char **array);
void 			insert_argument_block_infos(t_tile *map_tile, t_block_list *block_list, char *argument);
void			insert_tuple_block_infos(t_tile *map_tile, t_block_list *block_list, char **args);

void			load_env_block_data(t_game_object *game_object, char *agrument_block);
void			load_game_elements(char *string, t_game_object *game_object);
void			load_map_data(t_game_object *game_object, char *agrument_block);
void			load_player_data(t_game_object *game_object, char *agrument_block);
void			load_render_data(t_game_object *game_object, char *agrument_block);

void			safe_trim(char *line, char *filter);

t_coor			map_max_dimentions(char **map);
t_coor			parse_coordinate(char *tuple);

t_render_tools	parse_render(char *render_argument);

t_block_list	*create_block_node(char type, char icon, t_render render_data, void *function);
t_block_list	*push_block(t_block_list *block_list, t_block_list *new_element);
t_block_list	*search_for_block_node(t_block_list *block_list, char icon);

t_argument_list	*create_agument_node(char *argument_name, char *argument_value);
t_argument_list *create_argument_list(char *argument_block, t_argument_list *argument_list, char *tag);
t_argument_list *search_for_argument_node(t_argument_list *argument_list, char *argument_name);
t_argument_list	*push_argument(t_argument_list *argument_list, t_argument_list *new_element);
void	free_argument_list(t_argument_list *argument_list);

t_tile			**create_raw_map(t_tile **map,t_block_list *block_list, t_coor dimentions);
t_tile 			**create_map(char **map, t_block_list *block_list);

double		ft_clip_min(int min, double value);
double		ft_clip_max(int max, double value);
double		ft_clip_min_max(int min, int max, double value);