/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_tests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:52:05 by abenaiss          #+#    #+#             */
/*   Updated: 2021/05/14 18:31:51 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

const t_render_recognition	g_render_dico[] = {
	{"Basic", &ft_basic_render},
	{"Textured", &ft_textured_render},
	{"Neon", &ft_neon_render},
	{NULL, NULL}
};

t_game_rendering	*parse_render_type(char *render_type)
{
	int	i;

	i = -1;
	while (g_render_dico[++i].render_type)
	{	
		if (!strcmp(render_type, g_render_dico[i].render_type))
			return (g_render_dico[i].rendering_function);
	}
	error_print("The only valide renders types are : ",
		"(Basic, Textured, Dim, Neon)");
	return (NULL);
}

int	isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	check_if_number(char *string)
{
	int	i;

	i = -1;
	while (string[++i])
		if (!ft_isdigit(string[i]))
			error_print("wrong argument for number in: ", string);
}

t_coor	parse_coordinate(char *tuple)
{
	char	**tuple_values;
	t_coor	coordinate;
	short	i;

	tuple_values = parse_block_tuple(tuple);
	i = -1;
	while (tuple_values[++i])
		check_if_number(tuple_values[i]);
	coordinate.x = ft_clip_min(0, ft_atoi(tuple_values[0]));
	coordinate.y = ft_clip_min(0, ft_atoi(tuple_values[1]));
	return (coordinate);
}

int	parse_counters(char *counter, int min, int max)
{
	check_if_number(counter);
	return (ft_clip_min_max(min, max, ft_atoi(counter)));
}
