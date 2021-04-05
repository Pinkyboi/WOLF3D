/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 14:26:35 by abenaiss          #+#    #+#             */
/*   Updated: 2021/04/05 14:26:36 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			ft_get_textureX_coor(t_wolf *wolf)
{
	double wall_index;

	t_d_coor end = ft_add_vector2D(wolf->player.position,
		ft_scale_vector2D(wolf->player.current_ray, wolf->player.hit_infos.distance));
	wall_index = (wolf->player.hit_infos.wall_type == 'V') ? end.y : end.x;
	wall_index -= (int)wall_index;
	int texture_index = wall_index * (double)wolf->texture_dimention.y;
	return(texture_index);
}