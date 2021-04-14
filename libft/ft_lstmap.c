/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 20:35:10 by abenaiss          #+#    #+#             */
/*   Updated: 2018/10/15 20:35:13 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *tab;
	t_list *temp;

	if (lst == NULL)
		return (NULL);
	tab = (*f)(lst);
	temp = tab;
	while (lst->next != NULL)
	{
		temp->next = (*f)(lst->next);
		lst = lst->next;
		temp = temp->next;
	}
	return (tab);
}
