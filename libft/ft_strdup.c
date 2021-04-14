/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 17:51:28 by abenaiss          #+#    #+#             */
/*   Updated: 2018/10/06 17:51:31 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (src[i] != '\0')
		i++;
	if (!(str = (char*)malloc(sizeof(const char) * (i + 1))))
		return (NULL);
	while (j < i)
	{
		str[j] = src[j];
		j++;
	}
	str[i] = '\0';
	return (str);
}
