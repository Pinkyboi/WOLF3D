/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 14:28:33 by abenaiss          #+#    #+#             */
/*   Updated: 2021/04/26 14:28:44 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_block_list	*search_for_block_node(t_block_list *block_list, char icon)
{
	t_block_list	*head_save;

	head_save = block_list;
	while (head_save)
	{
		if (head_save->block_icon == icon)
			return (head_save);
		head_save = head_save->next;
	}
	return (NULL);
}

int	load_texture(char *path, t_texture *texture_data)
{
	t_mlx_img	mlx;

	mlx.mlx_ptr = mlx_init();
	mlx.mlx_img = mlx_xpm_file_to_image (mlx.mlx_ptr,
			path, &(texture_data->texture_width),
			&(texture_data->texture_height));
	if (!mlx.mlx_img)
		error_print("error in texture path: ", path);
	texture_data->texture_data = (int *)mlx_get_data_addr(mlx.mlx_img,
			&mlx.bpp, &mlx.size_l, &mlx.endian);
	return (1);
}

t_render_tools	parse_render(char *render_argument)
{
	t_render_tools	render_tools;

	if (stock_hex(render_argument, &render_tools.render_data.color))
		render_tools.render_function = NULL;
	else if (load_texture(render_argument, &render_tools.render_data.texture))
		render_tools.render_function = NULL;
	return (render_tools);
}

void	parse_block(char **data, t_block_list *block_list)
{
	char			block_type;
	char			block_icon;
	char			**tuple;
	t_render_tools	render_tools;

	tuple = parse_block_tuple(data[0]);
	block_icon = '1';
	block_type = 'w';
	if (ft_strlen(tuple[0]) == 1 && ft_isalnum(*tuple[0]))
	{
		if (*tuple[0] == '0')
			error_print("This block symbol is reserved for void : ", tuple[1]);
		block_icon = *tuple[0];
		if (!ft_strcmp(tuple[1], "wall") || !ft_strcmp(tuple[1], "floor")
			|| !ft_strcmp(tuple[1], "ceiling"))
			block_type = *tuple[1];
		else
			error_print("unknown block type in: ", tuple[1]);
	}
	else
		error_print("block symbole should be alphanumeric: ", tuple[0]);
	render_tools = parse_render(data[1]);
	block_list = push_block(block_list, create_block_node(block_type,
				block_icon, render_tools.render_data,
				render_tools.render_function));
}

void	load_env_block_data(t_game_object *game_object, char *agrument_block)
{
	int		i;
	char	**current_argument;
	char	**arguments_data;

	i = -1;
	arguments_data = ft_strsplit(agrument_block, ARGUMENT_DELIMITER);
	while (arguments_data[++i])
	{
		current_argument = parse_argument_blocks(arguments_data[i], "<env>");
		parse_block(current_argument, game_object->block_list);
		free_array(current_argument);
		free(arguments_data[i]);
	}
}
