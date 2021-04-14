/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 18:55:24 by abenaiss          #+#    #+#             */
/*   Updated: 2018/10/07 19:15:35 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	nb;

	nb = (unsigned char)c;
	s1 = (unsigned char*)s;
	i = 0;
	while (i < n)
	{
		if (s1[i] != nb)
			++i;
		else
			return (s1 + i);
	}
	return (NULL);
}
