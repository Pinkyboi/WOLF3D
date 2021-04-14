/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 19:09:30 by abenaiss          #+#    #+#             */
/*   Updated: 2018/10/08 19:09:32 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*dest;
	char	*src1;
	char	*t;

	dest = (char*)dst;
	src1 = (char*)src;
	if (!(t = (char*)malloc(sizeof(char*) * (n))))
		return (NULL);
	i = 0;
	while (i < n)
	{
		t[i] = src1[i];
		i++;
	}
	i = 0;
	while (i < n)
	{
		dest[i] = t[i];
		i++;
	}
	free(t);
	return ((void*)dest);
}
