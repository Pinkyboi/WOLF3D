/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:52:05 by abenaiss          #+#    #+#             */
/*   Updated: 2021/11/08 18:51:45 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_free_array(char **array)
{
	int	i;

	i = -1;
	while (array && array[++i])
		free(array[i]);
	free(array);
}

int	ft_row_len(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
		i++;
	return (i);
}
