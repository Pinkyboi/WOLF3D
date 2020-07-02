/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:52:05 by abenaiss          #+#    #+#             */
/*   Updated: 2021/04/25 22:23:13 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	print_map(t_game_object game_object)
{
	int				i;
	int				j;

	i = -1;
	while (++i < game_object.map.map_dimentions.y + 2)
	{
		j = -1;
		while (++j < game_object.map.map_dimentions.x + 2)
		{
			if (game_object.map.map_grid[i][j].wall)
				printf("%c ", game_object.map.map_grid[i][j].wall->block_icon);
			else
				printf("%c ", '0');
		}
		printf("\n");
	}
}
int	main(int argc, char **argv)
{
	int				fd;
	t_game_object	game_object;
	char			*data;

	game_object.block_list = push_block(NULL,
			create_block_node('w', FILLER_ICON,
				(t_render){.color = FILLER_COLOR}, NULL));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0 || argc != 2)
		exit(-1);
	data = read_file(fd);
	load_game_elements(data, &game_object);
	print_map(game_object);
	return (0);
}
