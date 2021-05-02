/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:50:27 by abenaiss          #+#    #+#             */
/*   Updated: 2021/04/22 15:50:30 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	select_tile(t_tile *map_tile, t_block_list *block_list, char *line)
{
	if (*line == '(')
		insert_tuple_block_infos(map_tile, block_list, parse_block_tuple(line));
	else
		insert_argument_block_infos(map_tile, block_list, line);
}

t_coor	map_max_dimentions(char **map)
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
		width = row_len(line);
		if (width > biggest_width)
			biggest_width = width;
		free_array(line);
	}
	return ((t_coor){biggest_width, height});
}

t_tile	**create_raw_map(t_tile **map, t_block_list *block_list,
	t_coor dimentions)
{
	int				i;
	int				j;
	t_block_list	*filler_block;

	i = -1;
	map = (t_tile **)malloc(sizeof(t_tile *) * dimentions.y);
	if (!map)
		error_print("internal error during :", "memory allocation");
	filler_block = search_for_block_node(block_list, FILLER_ICON);
	while (++i < dimentions.y)
	{
		j = -1;
		map[i] = (t_tile *)malloc(sizeof(t_tile) * dimentions.x);
		if (!map[i])
			error_print("internal error during :", "memory allocation");
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

t_tile 	**create_map(char **map, t_block_list *block_list)
{
	t_coor	max_dimentions;
	t_coor	index;
	t_tile	**final_map;
	char	**line;

	final_map = NULL;
	max_dimentions = map_max_dimentions(map);
	final_map = create_raw_map(final_map, block_list,
			(t_coor){max_dimentions.x + 2, max_dimentions.y + 2});
	index.y = -1;
	while (++index.y < max_dimentions.y)
	{
		index.x = -1;
		line = ft_strsplit(map[index.y], ' ');
		while (line[++index.x])
			select_tile(&final_map[index.y + 1][index.x + 1],
				block_list, line[index.x]);
		free_array(line);
	}
	return (final_map);
}

void	load_map_data(t_game_object *game_object, char *agrument_block)
{
	char	**raw_map;

	raw_map = ft_strsplit(agrument_block, '\n');
	game_object->map.map_dimentions = map_max_dimentions(raw_map);
	game_object->map.map_grid = create_map(raw_map, game_object->block_list);
	free_array(raw_map);
}
