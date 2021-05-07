/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:52:05 by abenaiss          #+#    #+#             */
/*   Updated: 2021/05/07 00:04:38 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_init_win(t_game_object *game_object)
{
	t_mlx	mlx;
	t_coor	resolution;

	resolution = game_object->render_data.window_resolution;
	mlx.mlx_ptr = mlx_init();
	mlx.mlx_img.img_ptr = mlx_new_image(mlx.mlx_ptr,
			resolution.x, resolution.x);
	mlx.mlx_img.img_data = (int *)mlx_get_data_addr(mlx.mlx_img.img_ptr,
			&mlx.mlx_img.bpp, &mlx.mlx_img.size_l, &mlx.mlx_img.endian);
	mlx.mlx_win = mlx_new_window(mlx.mlx_ptr, resolution.x,
			resolution.y, "WOLF3D");
	game_object->render_data.mlx = mlx;
	ft_ray_shooter(game_object);
	mlx_put_image_to_window(mlx.mlx_ptr,
		mlx.mlx_win, mlx.mlx_img.img_ptr, 0, 0);
	mlx_hook(mlx.mlx_win, 2, 0, &ft_key_stroke, game_object);
	mlx_hook(mlx.mlx_win, 17, 1, (*ft_exit), game_object);
	mlx_loop(game_object->render_data.mlx.mlx_ptr);
}

int	main(int argc, char **argv)
{
	int				fd;
	t_game_object	*game_object;
	char			*data;

	game_object = malloc(sizeof(t_game_object));
	game_object->parser.block_list = push_block(NULL,
			create_block_node('w', FILLER_ICON,
				(t_render){.color = FILLER_COLOR}, &color_wall));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0 || argc != 2)
		error_print("FATAL ERROR : ", "invalid save file argument");
	data = read_file(fd);

	load_game_elements(data, game_object);
	printf("(%d, %d)\n", game_object->player.grid_position.x, game_object->player.grid_position.y);
	if (is_position_valid(game_object, game_object->player.grid_position))
		error_print("FATAL ERROR : ",
			"the player is on a block or out of the map boundaries");
	ft_init_win(game_object);
	return (0);
}
