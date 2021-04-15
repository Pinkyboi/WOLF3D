/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_blocks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:52:05 by abenaiss          #+#    #+#             */
/*   Updated: 2021/04/14 19:34:56 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

char	**parse_block_tuple(char *tuple)
{
	int		i;
	int		argument_number;
	char	**splited_tuple;

	if(mini_brackets(tuple, LEGAL_BRACKETS) != 1)
		error_print("wrong tuple format in:", tuple);
	splited_tuple = ft_strsplit(tuple, ',');
	argument_number = row_len(splited_tuple);
	if (argument_number != 2)
		error_print("wrong tuple format in:", tuple);
	i = -1;
	while (splited_tuple[++i])
		splited_tuple[i] = trim(splited_tuple[i],
			ft_strjoin(WHITE_SPACES, LEGAL_BRACKETS));
	return (splited_tuple);
}