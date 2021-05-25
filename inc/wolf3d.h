/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 14:49:07 by abenaiss          #+#    #+#             */
/*   Updated: 2021/05/14 19:11:23 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d_parser.h"

# define FT_SQR(X) ((X) * (X))
# define FT_RAD(X) (((X) * M_PI) / 180)

# define MAX_DIST 100

# define PI_2 6.2831853072
# define PLAYER_FOV FT_RAD(60)


# define EXIT 53
# define FOREWORD 13
# define BACKWARD 1
# define UP 14
# define LEFT 0
# define RIGHT 2
# define DOWN 12
# define KEY_R 15
# define KEY_T 17
# define SAVE 36
# define SHIFT 257

#define RENDER game_object->render_data
#define	BLOCK_SIZE 32
#define FOV 1

typedef struct			s_color
{
	int r;
	int g;
	int b;
}						t_color;

typedef struct			s_is_pressed
{
	int					key;
	short				state;
}						t_is_pressed;

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
short	is_position_valid(t_game_object *game_object, t_coor grid_position);

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


int			ft_key_stroke(int key,t_game_object *game_object);
int			ft_exit(t_game_object *game_object);

void		ft_ray_shooter(t_game_object *game_object);
void 		ft_movement(t_game_object *game_object);
void		ft_run(t_game_object *game_object);

void 		ft_check_walls(t_game_object *game_object);

void	ft_draw_hard_line(int start, int end, int color,
	t_game_object *game_object, double shade);

void		color_wall(t_game_object *game_object, t_render data);
void		texture_wall(t_game_object *game_object, t_render data);

void		ft_put_pixel(t_game_object *game_object, t_coor position, int color);

void		ft_ray_shooter(t_game_object *game_object);

void		ft_textured_render(t_game_object *game_object);
void		ft_basic_render(t_game_object *game_object);
void	tile_render(t_game_object *game_object, t_coor range, char type);

void	ft_clear_mlx(t_game_object *game_object);
int		ft_exit(t_game_object *game_object);
void		ft_head_tilt(t_game_object *game_object);

short	any_key_pressed(void);
int	key_release(int key);
short	get_movement_key(int key);
void	change_key_state(int key, short state);

int	frame_loop(void *arg);
void draw_disk(t_game_object *game_object, int radius, int color, t_d_coor center);
void print_mini_map(t_game_object *game_object, int radius, int block_size, t_d_coor center);