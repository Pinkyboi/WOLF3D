/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 17:35:06 by abenaiss          #+#    #+#             */
/*   Updated: 2018/10/09 19:40:18 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	char			*dest;
	const char		*src1;

	dest = (char*)dst;
	src1 = (char*)src;
	i = 0;
	if (n == 0)
		return ((void*)dest);
	while (i < n)
	{
		dest[i] = src1[i];
		i++;
	}
	return ((void*)dest);
}
