/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 21:51:36 by abenaiss          #+#    #+#             */
/*   Updated: 2020/06/30 19:33:25 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_clear_mlx(t_mlx *mlx, t_wolf *wolf)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
	mlx_clear_window(mlx->mlx_ptr, mlx->win);
	mlx->img.img_ptr =
		mlx_new_image(mlx->mlx_ptr, wolf->width, wolf->height);
	mlx->img.data =
	(int*)mlx_get_data_addr(mlx->img.img_ptr, &mlx->img.bpp,
			&mlx->img.size_l, &mlx->img.endian);
}

void		ft_put_pixel(t_wolf *wolf,t_coor position,int color)
{
	if (position.x >= 0 && position.x < wolf->width &&
		position.y >= 0 && position.y < wolf->height)
		wolf->mlx.img.data[
			(int)(position.y * wolf->width + position.x)] = color;
}

int			ft_exit(t_wolf *wolf)
{
	(void)wolf;
	exit(0);
}

void plot_line(t_wolf *wolf, int color, t_coor p1, t_coor p2)
{
  int dx =  abs (p2.x - p1.x), sx = p1.x < p2.x ? 1 : -1;
  int dy = -abs (p2.y - p1.y), sy = p1.y < p2.y ? 1 : -1; 
  int err = dx + dy, e2;
 
  while (1){
	ft_put_pixel(wolf, p1, color);
    if (p1.x == p2.x && p1.y == p2.y) break;
    	e2 = 2 * err;
    if (e2 >= dy) { err += dy; p1.x += sx; }
    if (e2 <= dx) { err += dx; p1.y += sy; }
  }
}