/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 18:56:00 by abenaiss          #+#    #+#             */
/*   Updated: 2018/10/10 18:56:05 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*t;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	t = (char*)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (t == NULL)
		return (NULL);
	ft_strcpy(t, s1);
	ft_strcat(t, s2);
	return (t);
}
