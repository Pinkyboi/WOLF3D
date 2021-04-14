/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 17:06:44 by abenaiss          #+#    #+#             */
/*   Updated: 2018/10/10 17:06:47 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	int		j;
	char	*s2;

	j = 0;
	if (!s)
		return (NULL);
	s2 = (char*)malloc(sizeof(char) * (len + 1));
	if (s2 == NULL)
		return (NULL);
	while (0 < len && s[start])
	{
		s2[j] = s[start];
		j++;
		start++;
		len--;
	}
	s2[j] = '\0';
	return (s2);
}
