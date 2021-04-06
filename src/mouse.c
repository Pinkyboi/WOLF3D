/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 17:56:24 by abenaiss          #+#    #+#             */
/*   Updated: 2021/04/05 17:56:25 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			ft_mouse_tracking(int x, int y, t_wolf *wolf){
    
    double angle  = atan(fabs(x - wolf->old_x) / WIN_HEIGHT/2);
        ft_clear_mlx(&wolf->mlx, wolf);
        if(x - wolf->old_x > 0){
            wolf->old_x = x;
            wolf->player.view_angle += angle;
        }
            
        else{
            wolf->player.view_angle -= angle;
            wolf->old_x = x;
        }
        if(WIN_WIDTH  - x < 50)
            wolf->player.view_angle += 0.05;
        if(x < 50)
            wolf->player.view_angle -= 0.05;
        wolf->old_x = x;
        wolf->player.view_angle = ft_check_angle(wolf->player.view_angle);
        wolf->player.movement = ft_scale_vector2D(
            ft_angleToVector2D(wolf->player.view_angle), wolf->player.step);
        ft_ray_shooter(wolf);
        ft_minimap(wolf);
        mlx_put_image_to_window(wolf->mlx.mlx_ptr,
            wolf->mlx.win, wolf->mlx.img.img_ptr, 0, 0);
    return(0);
}