/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 14:21:08 by abenaiss          #+#    #+#             */
/*   Updated: 2018/10/20 14:18:40 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	char			*d;
	unsigned char	*sr;
	unsigned char	cr;

	d = (char*)dst;
	sr = (unsigned char*)src;
	cr = (char)c;
	i = 0;
	while (i < n)
	{
		d[i] = sr[i];
		if (sr[i] == cr)
			return ((void*)(d + i + 1));
		i++;
	}
	return (NULL);
}
