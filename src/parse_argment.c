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

t_coor	parse_resolution(char *resolution_expression)
{
	char	**arguments;
	int		argument_number;
	t_coor	resolution;
	int		i;

	arguments = ft_strsplit(resolution_expression, 'x');
	argument_number = row_len(arguments);
	if (argument_number != 2)
		error_print("wrong resolution format in:", resolution_expression);
	i = -1;
	while (arguments[++i])
	{
		safe_trim(arguments[i], WHITE_SPACES);
		check_if_number(arguments[i]);
	}
	resolution.x = ft_clip_min(0, ft_atoi(arguments[0]));
	resolution.y = ft_clip_min(0, ft_atoi(arguments[1]));
	return (resolution);
}

void	safe_trim(char *line, char *filter)
{
	char	*trimmed_line;

	trimmed_line = ft_strdup(line);
	trimmed_line = trim(trimmed_line, filter);
	line = ft_strcpy(line, trimmed_line);
	free(trimmed_line);
}

char	**parse_argument_blocks(char *block_infos, char *tag)
{
	char	**block_terms;
	int		arg_num;

	arg_num = -1;
	block_terms = ft_strsplit(block_infos, ':');
	while (block_terms[++arg_num])
		safe_trim(block_terms[arg_num], WHITE_SPACES);
	if (arg_num != 2)
		error_print("Wrong argument format in: ", tag);
	return (block_terms);
}
