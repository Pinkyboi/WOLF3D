/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 12:15:27 by abenaiss          #+#    #+#             */
/*   Updated: 2018/10/10 12:15:30 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	size_t	len_s;
	char	*n_str;

	if (s == NULL || f == NULL)
		return (NULL);
	i = 0;
	len_s = ft_strlen(s);
	n_str = (char*)malloc(sizeof(char) * (len_s + 1));
	if (n_str == NULL)
		return (NULL);
	while (s[i])
	{
		n_str[i] = (*f)(s[i]);
		i++;
	}
	n_str[i] = '\0';
	return (n_str);
}
