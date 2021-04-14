/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 19:54:21 by abenaiss          #+#    #+#             */
/*   Updated: 2018/10/14 20:13:35 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *p;

	if (!(p = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (content != NULL)
	{
		p->content = malloc(content_size);
		ft_memcpy(p->content, content, content_size);
		p->content_size = content_size;
	}
	else
	{
		p->content = NULL;
		p->content_size = 0;
	}
	p->next = NULL;
	return (p);
}
