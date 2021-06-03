/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:52:05 by abenaiss          #+#    #+#             */
/*   Updated: 2021/04/15 02:59:30 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

char	*ft_read_file(int fd)
{
	int		read_index;
	char	buffer[42069 + 1];
	char	*content;

	content = malloc(1);
	if (content == NULL)
		exit(-1);
	*content = '\0';
	while (1)
	{
		read_index = read(fd, buffer, 42069);
		if (read_index == -1)
			exit(-1);
		if (!read_index)
			break ;
		content = ft_strjoin(content, buffer);
	}
	close(fd);
	return (content);
}
