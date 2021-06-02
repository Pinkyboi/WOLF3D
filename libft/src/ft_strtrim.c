/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 18:33:55 by abenaiss          #+#    #+#             */
/*   Updated: 2021/06/02 18:34:00 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strft_trim(char const *s)
{
	size_t	i;
	size_t	len_s;
	char	*t;
	size_t	j;

	if (!s)
		return (NULL);
	j = 0;
	i = 0;
	len_s = ft_strlen(s);
	while (*s && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i++;
	while (len_s - 1 != 0 && (s[len_s - 1] == ' '
			|| s[len_s - 1] == '\n' || s[len_s - 1] == '\t'))
		len_s--;
	if ((len_s - 1 == 0 || i == len_s))
	{
		t = (char *)malloc(sizeof(char));
		*t = '\0';
		return (t);
	}
	t = ft_strsub(s, i, len_s - i);
	return (t);
}
