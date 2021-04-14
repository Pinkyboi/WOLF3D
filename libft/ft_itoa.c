/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 15:57:09 by abenaiss          #+#    #+#             */
/*   Updated: 2018/10/11 17:48:55 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static	unsigned int	len_nb(unsigned int temp)
{
	unsigned int len;

	len = 0;
	while (temp)
	{
		temp /= 10;
		len++;
	}
	return (len);
}

static	char			*fill_tab(char *t, unsigned int signe,
		unsigned int len, unsigned int nb)
{
	int n;

	n = 0;
	if (signe != 0)
	{
		t[0] = '-';
		t[len + 1] = '\0';
		n = len + 1;
		while (--n)
		{
			t[n] = (nb % 10) + '0';
			nb /= 10;
		}
	}
	else
	{
		t[len] = '\0';
		while (len--)
		{
			t[len] = (nb % 10) + '0';
			nb /= 10;
		}
	}
	return (t);
}

char					*ft_itoa(int n)
{
	unsigned int	nb;
	int				signe;
	unsigned int	len;
	char			*t;
	unsigned int	temp;

	nb = 0;
	signe = 0;
	len = 0;
	if (n < 0)
	{
		nb = -n;
		signe = 1;
	}
	else
		nb = n;
	temp = nb;
	if (nb == 0)
		len = 1;
	else
		len = len_nb(temp);
	if (!(t = (char*)malloc(sizeof(char) * (len + signe + 1))))
		return (NULL);
	return (fill_tab(t, signe, len, nb));
}
