/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:43:53 by abenaiss          #+#    #+#             */
/*   Updated: 2021/04/22 15:43:54 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

char	**parse_block_tuple(char *tuple)
{
	int		i;
	int		argument_number;
	char	**splited_tuple;

	if (mini_brackets(tuple, LEGAL_BRACKETS) != 1)
		error_print("wrong tuple format in:", tuple);
	splited_tuple = ft_strsplit(tuple, ',');
	argument_number = row_len(splited_tuple);
	if (argument_number != 2 && argument_number != 3)
		error_print("wrong tuple format in:", tuple);
	i = -1;
	while (splited_tuple[++i])
		splited_tuple[i] = trim(splited_tuple[i],
				ft_strjoin(WHITE_SPACES, LEGAL_BRACKETS));
	return (splited_tuple);
}

char	**parse_resolution(char *resolution_expression)
{
	char	**resolution;
	int		argument_number;
	int		i;

	resolution = ft_strsplit(resolution_expression, 'x');
	argument_number = row_len(resolution);
	if (argument_number != 2)
		error_print("wrong resolution format in:", resolution_expression);
	i = -1;
	while (resolution[++i])
	{
		resolution[i] = trim(resolution[i], WHITE_SPACES);
		check_if_number(resolution[i]);
	}
	return (resolution);
}

char	**parse_argument_blocks(char *block_infos)
{
	char	**block_terms;
	int		argument_number;

	block_terms = ft_strsplit(block_infos, ':');
	argument_number = row_len(block_terms);
	if (argument_number != 2)
		error_print("wrong argument format in:", block_infos);
	return (block_terms);
}
