/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 21:51:36 by abenaiss          #+#    #+#             */
/*   Updated: 2020/07/02 15:47:17 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static	char	*ft_total_join(const int fd, int *a)
{
	char	buf[1000001];
	int		ret;
	char	*str;
	int		i;

	i = 0;
	str = ft_strnew(0);
	while ((ret = read(fd, buf, 1000000)))
	{
		if (ret == 0)
			break ;
		buf[ret] = '\0';
		str = ft_strjoin(str, buf);
	}
	while (str[i])
	{
		if (str[i] == '\n')
			(*a)++;
		i++;
	}
	return (str);
}

static	t_map	*ft_lineup(char *str, t_map *tab, int *b, int y)
{
	char	**t;
	int		i;

	t = ft_strsplit(str, ' ');
	if (!(*b))
	{
		while (t[*b])
			(*b)++;
		(*b)--;
	}
	if (!(tab = (t_map *)malloc(sizeof(t_map) * (*b + 1))))
		return (0);
	i = -1;
	while (t[++i])
	{
		tab[i].type = t[i][0];
		free(t[i]);
	}
	return (tab);
}

t_map			**ft_read_matrice(const int fd, int *a, int *b)
{
	char	*str;
	char	**tab;
	int		i;
	t_map	**t;

	*a = 0;
	*b = 0;
	str = ft_total_join(fd, a);
	tab = ft_strsplit(str, '\n');
	t = (t_map **)malloc(sizeof(t_map *) * (*a + 1));
	i = -1;
	while (tab[++i])
	{
		t[i] = ft_lineup(tab[i], t[i], b, i);
		free(tab[i]);
	}
	free(str);
	return (t);
}