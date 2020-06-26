/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 21:51:36 by abenaiss          #+#    #+#             */
/*   Updated: 2020/06/25 23:46:03 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_clear_mlx(t_mlx *mlx, t_rtv *rtv)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
	mlx_clear_window(mlx->mlx_ptr, mlx->win);
	mlx->img.img_ptr =
		mlx_new_image(mlx->mlx_ptr, rtv->width, rtv->height);
	mlx->img.data =
	(int*)mlx_get_data_addr(mlx->img.img_ptr, &mlx->img.bpp,
			&mlx->img.size_l, &mlx->img.endian);
}

void		ft_put_pixel(t_rtv *rtv,t_coor position,int color)
{
	if (position.x >= 0 && position.x < rtv->width &&
		position.y >= 0 && position.y < rtv->height)
		rtv->mlx.img.data[
			(int)(position.y * rtv->width + position.x)] = color;
}

int			ft_exit(t_rtv *rtv)
{
	(void)rtv;
	exit(0);
}

void plot_line(t_rtv *rtv, int color, t_coor p1, t_coor p2)
{
  int dx =  abs (p2.x - p1.x), sx = p1.x < p2.x ? 1 : -1;
  int dy = -abs (p2.y - p1.y), sy = p1.y < p2.y ? 1 : -1; 
  int err = dx + dy, e2;
 
  while (1){
	ft_put_pixel(rtv, p1, color);
    if (p1.x == p2.x && p1.y == p2.y) break;
    	e2 = 2 * err;
    if (e2 >= dy) { err += dy; p1.x += sx; } /* e_xy+e_x > 0 */
    if (e2 <= dx) { err += dx; p1.y += sy; } /* e_xy+e_y < 0 */
  }
}