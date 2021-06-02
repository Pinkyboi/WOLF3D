/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 21:33:20 by abenaiss          #+#    #+#             */
/*   Updated: 2018/10/09 23:04:24 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len_dest;
	size_t	k;

	k = 0;
	i = 0;
	len_dest = ft_strlen(dst);
	if (size > len_dest)
		k = size - len_dest - 1;
	while (i < k && src[i])
	{
		dst[len_dest + i] = src[i];
		i++;
	}
	dst[len_dest + i] = '\0';
	if (size > len_dest)
		return (len_dest + ft_strlen(src));
	else
		return (size + ft_strlen(src));
}
