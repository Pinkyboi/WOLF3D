/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:43:53 by abenaiss          #+#    #+#             */
/*   Updated: 2021/11/07 18:38:38 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_coor	ft_parse_resolution(char *resolution_expression)
{
	char	**arguments;
	int		argument_number;
	t_coor	resolution;
	int		i;

	arguments = ft_strsplit(resolution_expression, 'x');
	argument_number = ft_row_len(arguments);
	if (argument_number != 2)
		ft_err_print("Wrong resolution format in:", resolution_expression);
	i = -1;
	while (arguments[++i])
	{
		ft_safe_trim(arguments[i], WHITE_SPACES);
		ft_check_number(arguments[i]);
	}
	resolution.x = ft_clip_min(0, ft_atoi(arguments[0]));
	resolution.y = ft_clip_min(0, ft_atoi(arguments[1]));
	ft_free_array(arguments);
	return (resolution);
}

void	ft_safe_trim(char *line, char *filter)
{
	char	*ft_trimmed_line;

	ft_trimmed_line = ft_strdup(line);
	ft_trimmed_line = ft_trim(ft_trimmed_line, filter);
	line = ft_strcpy(line, ft_trimmed_line);
	free(ft_trimmed_line);
}

char	**ft_parse_block_arg(char *block_infos, char *tag)
{
	char	**block_terms;
	int		arg_num;

	arg_num = -1;
	block_terms = ft_strsplit(block_infos, ':');
	while (block_terms[++arg_num])
		ft_safe_trim(block_terms[arg_num], WHITE_SPACES);
	if (arg_num != 2)
		ft_err_print("Wrong argument format in: ", tag);
	return (block_terms);
}
