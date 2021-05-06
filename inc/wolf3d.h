/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 14:49:07 by abenaiss          #+#    #+#             */
/*   Updated: 2021/05/03 14:49:08 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d_parser.h"

# define FT_SQR(X) ((X) * (X))
# define FT_RAD(X) (((X) * M_PI) / 180)

# define MAX_DIST 100

# define PI_2 6.2831853072
# define PLAYER_FOV FT_RAD(45)


# define EXIT 53
# define FOREWORD 13
# define BACKWARD 1
# define UP 12
# define LEFT 0
# define RIGHT 2
# define DOWN 14
# define KEY_R 15
# define KEY_T 17
# define SAVE 36

#define RENDER game_object->render_data
#define	BLOCK_SIZE 64
#define FOV 1

typedef struct			s_color
{
	int r;
	int g;
	int b;
}						t_color;

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

double	ft_clip_min(int min, double value);
double	ft_clip_max(int max, double value);
double	ft_clip_min_max(int min, int max, double value);

int		t_rgb_to_int(t_color color);
int		ft_scale_color_int(int color, double scalar);

t_color	ft_scale_color(t_color color, double scalar);
t_color		ft_int_to_rgb(int color);


double  	ft_ray_size(t_game_object *gamet_game_object, t_d_coor ray_intersection, double angle);
t_d_coor    ft_add_vector2D(t_d_coor vector2D, t_d_coor second_vector2D);
t_d_coor    ft_sub_vector2D(t_d_coor vector2D, t_d_coor second_vector2D);
t_d_coor    ft_scale_vector2D(t_d_coor vector2D, double scale);
t_d_coor    ft_normalise_vector2D(t_d_coor vector);

t_coor		ft_get_sign(t_d_coor coor);
void		ft_get_right_step(t_d_coor ray, t_d_coor *rayStep);
short		is_block_solid(t_game_object *game_object, t_coor grid_position);

double		ft_check_angle(double angle);
t_d_coor	ft_angleToVector2D(double alpha);


void	ft_define_check_step(t_game_object *game_object);
void	ft_dda(t_game_object *game_object, t_d_coor *rayStep,
	t_d_coor *rayDistance, t_coor *gridStep);
void	ft_setup_dda(t_game_object *game_object, t_d_coor *rayStep,
	t_d_coor *rayDistance, t_coor *gridStep);
t_coor	ft_get_sign(t_d_coor coor);
void	ft_get_right_step(t_d_coor ray, t_d_coor *rayStep);
short	is_block_solid(t_game_object *game_object, t_coor grid_position);


int			ft_key_stroke(int key, t_game_object *game_object);
int			ft_exit(t_game_object *game_object);

void		ft_ray_shooter(t_game_object *game_object);
void 		ft_movement(int key, t_game_object *game_object);

int 		ft_check_walls(t_game_object *game_object, int key);

void		ft_draw_hard_line(int start, int end, int color, t_game_object *game_object);

void		color_wall(t_game_object *game_object, t_render data);
void		texture_wall(t_game_object *game_object, t_render data);