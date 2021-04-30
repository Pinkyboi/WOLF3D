/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 14:25:01 by abenaiss          #+#    #+#             */
/*   Updated: 2021/04/29 14:25:40 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	error_print(char *error, char *position)
{
	ft_putstr_fd(ft_strjoin(error, position), 1);
	exit(-1);
}

char	*trim(char *string, char *filter)
{
	int		head;
	int		end;
	int		string_size;
	char	*trimmed_string;

	head = 0;
	while (string[head])
	{
		if (!ft_strchr(filter, string[head]))
			break ;
		head++;
	}
	end = ft_strlen(string) - 1;
	while (end > head)
	{
		if (!ft_strchr(filter, string[end]))
			break ;
		end--;
	}
	string_size = end - head + 1;
	trimmed_string = ft_strnclone(&string[head], string_size);
	free(string);
	return (trimmed_string);
}

int	mini_brackets(char *string, char *bracket)
{
	int	open_braket;
	int	pair_number;
	int	i;

	i = -1;
	open_braket = 0;
	pair_number = 0;
	while (string[++i])
	{
		if (string[i] == bracket[0])
			open_braket += 1;
		if (!open_braket && string[i] == bracket[1])
			return (-1);
		if (string[i] == bracket[1] && ++pair_number)
			open_braket -= 1;
	}
	if (open_braket == 0)
		return (pair_number);
	return (-1);
}
