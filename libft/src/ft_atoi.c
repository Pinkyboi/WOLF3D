/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 21:10:21 by abenaiss          #+#    #+#             */
/*   Updated: 2021/11/08 19:13:42 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define INT_MAX +2147483647
#define INT_MIN -2147483648

size_t	is_white(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	nb;

	i = 0;
	while (is_white(str[i]))
		i++;
	sign = 1;
	if ((str[i] == '-' || str[i] == '+')
		&& (!(str[i] == '+' && i++) || (str[i] == '-' && i++)))
		sign = -1;
	nb = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10 + (str[i] - '0'));
		if ((nb * 10 + (str[i] - '0') >= INT_MAX) && sign == -1)
			return (INT_MIN);
		if ((nb * 10 + (str[i] - '0') >= INT_MAX) && sign == 1)
			return (INT_MAX);
		i++;
	}
	return (nb * sign);
}
