/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_tests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:52:05 by abenaiss          #+#    #+#             */
/*   Updated: 2021/11/08 21:28:41 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

const t_render_recognition	g_render_dico[] = {
	{"Basic", &ft_basic_render},
	{"Textured", &ft_textured_render},
	{"Wireframe", &ft_wireframe_render},
	{NULL, NULL}
};

t_game_rendering	*ft_parse_render_type(char *render_type)
{
	int	i;

	i = -1;
	while (g_render_dico[++i].render_type)
	{	
		if (!strcmp(render_type, g_render_dico[i].render_type))
			return (g_render_dico[i].rendering_function);
	}
	ft_err_print("The only valid renders types are : ",
		"(Basic, Textured, Wireframe)");
	return (NULL);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	ft_check_number(char *string)
{
	int	i;

	i = -1;
	if (!string)
		ft_err_print("ERROR: ", "empty argument");
	while (string[++i])
		if (!ft_ft_isdigit(string[i]))
			ft_err_print("Wrong argument for number in: ", string);
}

t_coor	ft_parse_coordinate(char *tuple)
{
	char	**tuple_values;
	t_coor	coordinate;
	short	i;

	tuple_values = ft_parse_block_tuple(tuple);
	i = -1;
	while (tuple_values[++i])
		ft_check_number(tuple_values[i]);
	coordinate.x = ft_clip_min(0, ft_atoi(tuple_values[0]));
	coordinate.y = ft_clip_min(0, ft_atoi(tuple_values[1]));
	ft_free_array(tuple_values);
	return (coordinate);
}

int	ft_parse_counters(char *counter, int min, int max)
{
	ft_check_number(counter);
	return (ft_clip_min_max(min, max, ft_atoi(counter)));
}
