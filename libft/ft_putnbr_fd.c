/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 15:18:04 by abenaiss          #+#    #+#             */
/*   Updated: 2018/10/11 15:18:08 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int nb;

	if (n < 0)
	{
		nb = -1 * n;
		ft_putchar_fd('-', fd);
	}
	else
		nb = n;
	if (nb < 10)
		ft_putchar_fd((nb + '0'), fd);
	else
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putchar_fd(((nb % 10) + '0'), fd);
	}
}
