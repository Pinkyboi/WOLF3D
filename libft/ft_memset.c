/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 17:30:41 by abenaiss          #+#    #+#             */
/*   Updated: 2018/10/06 17:37:36 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t n)
{
	size_t			i;
	unsigned char	*b2;

	b2 = (unsigned char*)b;
	i = 0;
	while (i < n)
	{
		b2[i] = c;
		i++;
	}
	return ((void*)b2);
}
