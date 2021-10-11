/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tuple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 11:54:23 by abenaiss          #+#    #+#             */
/*   Updated: 2021/04/29 11:54:26 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

char	**ft_parse_block_tuple(char *tuple)
{
	int		argument_number;
	char	**splited_tuple;

	if (ft_mini_brackets(tuple, LEGAL_BRACKETS) != 1)
		ft_err_print("wrong tuple format in:", tuple);
	splited_tuple = ft_strsplit(tuple, ',');
	argument_number = -1;
	while (splited_tuple[++argument_number])
		ft_safe_trim(splited_tuple[argument_number],
			WHITE_SPACE_AND_LEGAL_BRACKETS);
	if (argument_number != 2)
		ft_err_print("Wrong tuple format in:", tuple);
	return (splited_tuple);
}

void	ft_insert_tuple_block_infos(t_tile *map_tile,
	t_block_list *block_list, char **args)
{
	int	i;

	i = -1;
	while (args[++i])
		ft_insert_argument_block_infos(map_tile,
			block_list, args[i]);
	ft_free_array(args);
}
