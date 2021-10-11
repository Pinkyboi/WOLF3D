/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 14:28:33 by abenaiss          #+#    #+#             */
/*   Updated: 2021/05/07 21:13:13 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_block_list	*ft_find_block_node(t_block_list *block_list, char icon)
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

int	ft_load_texture(char *path, t_texture *texture_data)
{
	t_mlx	mlx;

	mlx.mlx_ptr = mlx_init();
	mlx.mlx_img.img_ptr = mlx_xpm_file_to_image (mlx.mlx_ptr,
			path, &(texture_data->texture_width),
			&(texture_data->texture_height));
	if (!mlx.mlx_img.img_ptr)
		ft_err_print("error in texture path: ", path);
	texture_data->texture_data = (int *)mlx_get_data_addr(mlx.mlx_img.img_ptr,
			&mlx.mlx_img.bpp, &mlx.mlx_img.size_l, &mlx.mlx_img.endian);
	free(mlx.mlx_ptr);
	free(mlx.mlx_img.img_ptr);
	return (1);
}

t_render_tools	ft_parse_render(char *render_argument)
{
	t_render_tools	render_tools;

	if (ft_stock_hex(render_argument, &render_tools.render_data.color))
		render_tools.render_function = &ft_color_wall;
	else if (ft_load_texture(render_argument,
			&render_tools.render_data.texture))
		render_tools.render_function = &ft_texture_wall;
	return (render_tools);
}

void	parse_block(char **data, t_block_list *block_list)
{
	char			block_info[2];
	char			**tuple;
	t_render_tools	render_tools;

	tuple = ft_parse_block_tuple(data[0]);
	block_info[0] = '1';
	block_info[1] = 'w';
	if (ft_strlen(tuple[0]) == 1 && ft_isalnum(*tuple[0]))
	{
		if (*tuple[0] == '0')
			ft_err_print("This block symbol is reserved for void : ", tuple[1]);
		block_info[0] = *tuple[0];
		if (!ft_strcmp(tuple[1], "wall") || !ft_strcmp(tuple[1], "floor")
			|| !ft_strcmp(tuple[1], "ceiling"))
			block_info[1] = *tuple[1];
		else
			ft_err_print("unknown block type in: ", tuple[1]);
	}
	else
		ft_err_print("block symbole should be alphanumeric: ", tuple[0]);
	render_tools = ft_parse_render(data[1]);
	block_list = ft_push_block(block_list, ft_create_block_node(block_info[1],
				block_info[0], render_tools.render_data,
				render_tools.render_function));
	ft_free_array(tuple);
}

void	ft_load_env_block_data(t_game_object *game_object, char *argument_block)
{
	int		i;
	char	**current_argument;
	char	**arguments_data;

	i = -1;
	arguments_data = ft_strsplit(argument_block, ARGUMENT_DELIMITER);
	while (arguments_data[++i])
	{
		current_argument = ft_parse_block_arg(arguments_data[i], "<env>");
		parse_block(current_argument, game_object->parser.block_list);
		ft_free_array(current_argument);
	}
	ft_free_array(arguments_data);
	free(argument_block);
}
