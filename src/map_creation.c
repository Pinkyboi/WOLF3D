/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:50:27 by abenaiss          #+#    #+#             */
/*   Updated: 2021/05/10 11:15:10 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	select_tile(t_tile *map_tile, t_block_list *block_list, char *line)
{
	if (*line == '(')
		ft_insert_tuple_block_infos(map_tile, block_list,
			ft_parse_block_tuple(line));
	else
		ft_insert_argument_block_infos(map_tile, block_list, line);
}

t_coor	ft_map_max_dim(char **map)
{
	int		height;
	int		width;
	int		biggest_width;
	char	**line;

	height = -1;
	biggest_width = 0;
	while (map[++height])
	{
		line = ft_strsplit(map[height], ' ');
		width = ft_row_len(line);
		if (width > biggest_width)
			biggest_width = width;
		ft_free_array(line);
	}
	return ((t_coor){biggest_width + 2, height + 2});
}

t_tile	**ft_create_raw_map(t_tile **map, t_block_list *block_list,
	t_coor dimentions)
{
	int				i;
	int				j;
	t_block_list	*filler_block;

	i = -1;
	map = ft_safe_malloc(sizeof(t_tile *) * dimentions.y);
	filler_block = ft_find_block_node(block_list, FILLER_ICON);
	while (++i < dimentions.y)
	{
		j = -1;
		map[i] = (t_tile *)malloc(sizeof(t_tile) * dimentions.x);
		if (!map[i])
			ft_err_print("internal error during :", "memory allocation");
		while (++j < dimentions.x)
		{
			map[i][j] = (t_tile){NULL, NULL, NULL};
			if (i == 0 || i + 1 == dimentions.y
				|| j == 0 || j + 1 == dimentions.x)
				map[i][j].wall = filler_block;
		}
	}
	return (map);
}

t_tile 	**ft_create_map(char **map, t_block_list *block_list)
{
	t_coor	max_dimentions;
	t_coor	index;
	t_tile	**final_map;
	char	**line;

	final_map = NULL;
	max_dimentions = ft_map_max_dim(map);
	final_map = ft_create_raw_map(final_map, block_list,
			max_dimentions);
	index.y = -1;
	while (++index.y < max_dimentions.y - 2)
	{
		index.x = -1;
		line = ft_strsplit(map[index.y], ' ');
		while (line[++index.x])
			select_tile(&final_map[index.y + 1][index.x + 1],
				block_list, line[index.x]);
		ft_free_array(line);
	}
	return (final_map);
}

void	ft_load_map_data(t_game_object *game_object, char *agrument_block)
{
	char	**raw_map;

	raw_map = ft_strsplit(agrument_block, '\n');
	game_object->map.map_dimentions = ft_map_max_dim(raw_map);
	game_object->map.map_grid = ft_create_map(raw_map,
			game_object->parser.block_list);
	ft_free_array(raw_map);
}
