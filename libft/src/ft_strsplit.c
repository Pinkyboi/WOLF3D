/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 15:28:15 by abenaiss          #+#    #+#             */
/*   Updated: 2018/10/12 15:28:17 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	nb_word(char const *s, char c)
{
	int	nb_word;
	int	i;

	i = 0;
	nb_word = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			nb_word++;
		i++;
	}
	return (nb_word);
}

static int	len_word(char const *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

char	**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		i[3];

	if (!s)
		return (NULL);
	i[0] = 0;
	i[1] = -1;
	tab = (char **)malloc(sizeof(char *) * (nb_word(s, c) + 1));
	if (!tab)
		return (NULL);
	while (++i[1] < nb_word(s, c))
	{
		while (s[i[0]] == c)
			i[0]++;
		tab[i[1]] = (char *)malloc(sizeof(char) * (len_word(s, c, i[0]) + 1));
		if (!(tab[i[1]]))
			return (NULL);
		i[2] = 0;
		while (s[i[0]] && s[i[0]] != c)
			tab[i[1]][i[2]++] = s[i[0]++];
		tab[i[1]][i[2]] = '\0';
	}
	tab[i[1]] = NULL;
	return (tab);
}
