/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 15:28:38 by abenaiss          #+#    #+#             */
/*   Updated: 2018/10/15 15:36:19 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list *temp;

	while (*alst != NULL)
	{
		temp = *alst;
		(*del)((temp)->content, (temp)->content_size);
		*alst = (*alst)->next;
		free(temp);
	}
}
