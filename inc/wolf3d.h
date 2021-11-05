/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 14:49:07 by abenaiss          #+#    #+#             */
/*   Updated: 2021/11/04 15:02:22 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "wolf3d_parser.h"

# define MAX_DIST 600
# define PI_2 6.2831853072
# define PLAYER_FOV 1.0472
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
# define BLOCK_SIZE 32
# define MAP_RING_COLOR 0x202020
# define MAP_VOID_COLOR 0
# define MAP_BLOCK_COLOR 0xFFFFFF
# define MAP_PLAYER_COLOR 0xFF0000

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}						t_color;

typedef struct s_is_pressed
{
	int					key;
	short				state;
}						t_is_pressed;

double		ft_clip_min(int min, double value);
double		ft_clip_max(int max, double value);
double		ft_clip_min_max(int min, int max, double value);
double		ft_check_angle(double angle);
double		ft_ray_size(t_game_object *gamet_game_object,
				t_d_coor ray_intersection, double angle);
double		ft_size_vector_2d(t_d_coor vector2D);
double		ft_sqr(double number);

int			ft_rgb_to_int(t_color color);
int			ft_scale_color_int(int color, double scalar);
int			ft_key_release(int key);
int			ft_key_stroke(int key, t_game_object *game_object);
int			ft_exit(t_game_object *game_object);
int			ft_frame_loop(void *arg);
int			ft_get_wire_color(t_d_coor hit_index, t_game_object *game_object);
int			ft_wire_x_color(t_game_object *game_object, double y_index);

t_color		ft_scale_color(t_color color, double scalar);
t_color		ft_int_to_rgb(int color);
t_color		ft_add_colors(t_color first, t_color second);

t_d_coor	ft_add_vector_2d(t_d_coor vector2D, t_d_coor second_vector2D);
t_d_coor	ft_sub_vector_2d(t_d_coor vector2D, t_d_coor second_vector2D);
t_d_coor	ft_scale_vector_2d(t_d_coor vector2D, double scale);
t_d_coor	ft_normalise_vector_2d(t_d_coor vector);
t_d_coor	ft_angle_to_2d_vector(double alpha);

t_coor		ft_get_sign(t_d_coor coor);

short		ft_is_block_solid(t_game_object *game_object, t_coor grid_position);
short		ft_is_position_valid(t_game_object *game_object,
				t_coor grid_position);
short		ft_any_key_pressed(void);
short		ft_get_movement_key(int key);

void		ft_define_check_step(t_game_object *game_object);
void		ft_dda(t_game_object *game_object, t_d_coor *ray_step,
				t_d_coor *rayDistance, t_coor *gridStep);
void		ft_setup_dda(t_game_object *game_object, t_d_coor *ray_step,
				t_d_coor *rayDistance, t_coor *gridStep);
void		ft_get_right_step(t_d_coor ray, t_d_coor *ray_step);
void		ft_ray_shooter(t_game_object *game_object);
void		ft_movement(t_game_object *game_object);
void		ft_run(t_game_object *game_object);
void		ft_check_walls(t_game_object *game_object);
void		ft_draw_hard_line(t_coor edge, int color,
				t_game_object *game_object, double shade);
void		ft_color_wall(t_game_object *game_object, t_render data);
void		ft_texture_wall(t_game_object *game_object, t_render data);
void		ft_put_pixel(t_game_object *game_object,
				t_coor position, int color);
void		ft_ray_shooter(t_game_object *game_object);
void		ft_textured_render(t_game_object *game_object);
void		ft_basic_render(t_game_object *game_object);
void		ft_wireframe_render(t_game_object *game_object);
void		ft_wireframe_draw(t_game_object *game_object);
void		ft_tile_render(t_game_object *game_object, t_coor range, char type);
void		ft_clear_mlx(t_game_object *game_object);
void		ft_head_tilt(t_game_object *game_object);
void		ft_change_key_state(int key, short state);
void		ft_draw_disk(t_game_object *game_object, int radius,
				int color, t_d_coor center);
void		ft_print_mini_map(t_game_object *game_object, t_d_coor center);
void		ft_bresenham(t_game_object *game_object, int color,
				t_coor start, t_coor end);
void		ft_print_fov(t_game_object *game_object, t_d_coor center,
				int ray_number, int size);
void		ft_draw_wire_line(t_coor edges,
				t_game_object *game_object, double shade);
void		ft_wire_tile(t_game_object *game_object, t_coor range);

#endif