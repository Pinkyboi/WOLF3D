/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 12:34:10 by abenaiss          #+#    #+#             */
/*   Updated: 2018/10/10 12:34:13 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	size_t			len_s;
	char			*n_str;

	if (s == NULL || f == NULL)
		return (NULL);
	i = 0;
	len_s = ft_strlen(s);
	if (!(n_str = (char*)malloc(sizeof(char) * (len_s + 1))))
		return (NULL);
	while (s[i])
	{
		n_str[i] = (*f)(i, s[i]);
		i++;
	}
	n_str[i] = '\0';
	return (n_str);
}
