/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_methadata.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 14:33:51 by abenaiss          #+#    #+#             */
/*   Updated: 2021/04/25 21:50:19 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	load_texture(char *path, t_texture *texture_data)
{
	t_mlx_img	mlx;

	mlx.mlx_ptr = mlx_init();
	mlx.mlx_img = mlx_xpm_file_to_image (mlx.mlx_ptr,
			"./textures/wood.xpm", &(texture_data->texture_width),
			&(texture_data->texture_height));
	if (!mlx.mlx_img)
		error_print("error in texture path: ", path);
	texture_data->texture_data = (int *)mlx_get_data_addr(mlx.mlx_img,
			&mlx.bpp, &mlx.size_l, &mlx.endian);
	return (1);
}

void	parse_block(char **data, t_block_list *block_list)
{
	char		block_type;
	char		block_icon;
	char		**tuple;
	void		*render_function;
	t_render	render;

	int i = -1;
	while(data[++i])
		printf("2--%s- \n", data[i]);
	printf("\n");
	tuple = parse_block_tuple(data[0]);
	if (ft_strlen(tuple[0]) == 1 && ft_isalnum(*tuple[0]))
	{
		if (!ft_strcmp(tuple[1], "wall") || !ft_strcmp(tuple[1], "floor")
			|| !ft_strcmp(tuple[1], "ceiling"))
			block_type = *tuple[1];
		else
			error_print("unknown block type in: ", tuple[1]);
	}
	else
		error_print("block symbole should be alphanumeric: ", tuple[1]);
	if (stock_hex(data[1], &render.color))
		render_function = NULL;
	else if (load_texture(data[1], &render.texture))
		render_function = NULL;
	block_list = push_block(block_list, create_block_node(block_type, *tuple[0],
				render, render_function));
	
}

void	load_env_block_data(char **data, t_block_list *block_list)
{
	int		i;
	int		j;
	char	**current_argument;

	i = -1;
	while (data[++i])
	{
		j = -1;
		printf("1--%s\n", data[i]);
		current_argument = parse_argument_blocks(data[i]);
		parse_block(current_argument, block_list);
		free_array(current_argument);
		free(data[i]);
	}
}
