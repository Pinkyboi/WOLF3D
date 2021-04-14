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
	int len;

	len = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		k;

	if (!s)
		return (NULL);
	k = 0;
	i = 0;
	if (!(tab = (char **)malloc(sizeof(char*) * (nb_word(s, c) + 1))))
		return (NULL);
	while (k < nb_word(s, c))
	{
		while (s[i] == c)
			i++;
		if (!(tab[k] = (char*)malloc(sizeof(char) * (len_word(s, c, i) + 1))))
			return (NULL);
		j = 0;
		while (s[i] != c && s[i])
			tab[k][j++] = s[i++];
		tab[k][j] = '\0';
		k++;
	}
	tab[k] = NULL;
	return (tab);
}
