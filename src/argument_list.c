/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 13:52:51 by abenaiss          #+#    #+#             */
/*   Updated: 2021/05/02 13:52:52 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_argument_list	*ft_create_agument_node(char *argument_name,
	char *argument_value)
{
	t_argument_list	*node;

	node = ft_safe_malloc(sizeof(t_argument_list));
	node->argument_name = argument_name;
	node->argument_value = argument_value;
	node->next = NULL;
	return (node);
}

void	ft_free_argument_list(t_argument_list *argument_list)
{
	t_argument_list	*current_arugment;

	while (argument_list)
	{
		current_arugment = argument_list;
		argument_list = argument_list->next;
		free(current_arugment);
	}
}

t_argument_list	*ft_create_argument_list(char *argument_block,
	t_argument_list *argument_list, char *tag)
{
	char			**argument_lines;
	char			**line;
	int				i;

	argument_lines = ft_strsplit(argument_block, ARGUMENT_DELIMITER);
	i = -1;
	while (argument_lines[++i])
	{
		line = ft_parse_block_arg(argument_lines[i], tag);
		argument_list = ft_push_argument(argument_list,
				ft_create_agument_node(ft_strdup(line[0]), ft_strdup(line[1])));
		ft_free_array(line);
	}
	return (argument_list);
}

t_argument_list	*ft_find_argument_node(t_argument_list *argument_list,
		char *argument_name)
{
	t_argument_list	*list_clone;

	list_clone = argument_list;
	while (list_clone)
	{
		if (!ft_strcmp(list_clone->argument_name, argument_name))
			return (list_clone);
		list_clone = list_clone->next;
	}
	return (NULL);
}

t_argument_list	*ft_push_argument(t_argument_list *argument_list,
				t_argument_list *new_element)
{
	t_argument_list	*head_save;

	head_save = argument_list;
	if (!head_save)
		head_save = new_element;
	else
	{
		while (argument_list)
		{
			if (argument_list->argument_name == new_element->argument_name)
			{
				free(argument_list->argument_value);
				argument_list->argument_value = new_element->argument_value;
				return (head_save);
			}
			if (!argument_list->next)
				break ;
			argument_list = argument_list->next;
		}
		argument_list->next = new_element;
	}
	return (head_save);
}
