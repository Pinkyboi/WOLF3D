/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 12:05:34 by abenaiss          #+#    #+#             */
/*   Updated: 2018/10/07 14:05:25 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (needle[j] == '\0')
		return ((char*)haystack);
	while (haystack[i])
	{
		j = 0;
		while (needle[j] && (needle[j] == haystack[i + j]))
			j++;
		if (ft_strlen(needle) == j)
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}
