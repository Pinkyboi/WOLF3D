/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:52:05 by abenaiss          #+#    #+#             */
/*   Updated: 2021/04/25 21:22:11 by abenaiss         ###   ########.fr       */
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
#define NUM_FILTER "1234567890"
#define HEX_FILTER "0123456789abcdef"
#define WHITE_SPACES " \n\t\r\v\f"
#define MAX_COLOR_VALUE 16777215
#define LEGAL_BRACKETS "()"
#define METHA_TAG "<metadata>::="
#define RENDER_TAG "<render>::="
#define WINDOW_TAG "<window>::="
#define PLAYER_TAG "<player>::="
#define MONSTER_TAG "<monster>::="
#define ENV_TAG "<env>::="
#define MAP_TAG "<map>::="
#define	FILLER_ICON '@'
#define FILLER_COLOR 0x444444

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

typedef struct			s_block_list
{
	char				type;
	char				block_icon;
	t_render			render_data;		
	void				*render_function;
	struct s_block_list	*next;
}				t_block_list;

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

typedef	struct			s_wolf
{
	t_block_list		*block_list;
	t_tile				*map;
	t_mlx_img			mlx;
}						t_wolf;

int				isdigit(int c);
int				row_len(char **array);
int				row_len(char **array);
int				hex_to_int(char *number);
int 			hex_to_color(char *color);
int				stock_hex(char *color, int *color_stock);
int				mini_brackets(char *string, char *bracket);
char			*trim(char *string, char *filter);
char			**parse_block_tuple(char *tuple);
char			**parse_resolution(char *resolution_expression);
char			**parse_argument_blocks(char *block_infos);
char    		*read_file(int fd);
void    		error_print(char *error, char *position);
void    		check_if_alpha(char *string);
void    		check_if_number(char *string);
void			free_array(char **array);
void 			insert_argument_block_infos(t_tile *map_tile, t_block_list *block_list, char *argument);
void			insert_tuple_block_infos(t_tile *map_tile, t_block_list *block_list, char **args);
void			load_env_block_data(char **data, t_block_list *block_list);

t_coor			map_max_dimentions(char **map);

t_block_list	*create_block_node(char type, char icon, t_render render_data, void *function);
t_block_list	*push_block(t_block_list *block_list, t_block_list *new_element);
t_block_list	*search_for_block_node(t_block_list *block_list, char icon);

t_tile			**create_raw_map(t_tile **map,t_block_list *block_list, t_coor dimentions);
t_tile 			**create_map(char **map, t_block_list *block_list);
