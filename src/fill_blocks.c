/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_blocks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:52:05 by abenaiss          #+#    #+#             */
/*   Updated: 2021/04/14 19:34:56 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

char	**parse_block_tuple(char *tuple)
{
	int		i;
	int		argument_number;
	char	**splited_tuple;

	if(mini_brackets(tuple, LEGAL_BRACKETS) != 1)
		error_print("wrong tuple format in:", tuple);
	splited_tuple = ft_strsplit(tuple, ',');
	argument_number = row_len(splited_tuple);
	if (argument_number != 2 && argument_number != 3)
		error_print("wrong tuple format in:", tuple);
	i = -1;
	while (splited_tuple[++i])
		splited_tuple[i] = trim(splited_tuple[i],
			ft_strjoin(WHITE_SPACES, LEGAL_BRACKETS));
	return (splited_tuple);
}

t_block_list	*create_block_node(char type, char icon, t_render render_data, void *function)
{
	t_block_list *node;

	node = malloc(sizeof(t_block_list));
	if(!node)
		error_print("internal error during :", "memory allocation");
	node->type = type;
	node->block_icon = icon;
	node->render_data = render_data;
	node->render_function = function;
	node->next = NULL;
	return (node);
}

t_block_list	*push_block(t_block_list *block_list, t_block_list *new_element)
{
	t_block_list *head_save;

	head_save = block_list;
	if(!head_save)
		head_save = new_element;
	else
	{
		while(block_list)
		{
			if(block_list->block_icon == new_element->block_icon)
			{
				block_list->type = new_element->type;
				block_list->render_data = new_element->render_data;
				block_list->render_function = new_element->render_function;
				return (head_save);
			}
			if(!block_list->next)
				break;
			block_list = block_list->next;
		}
		block_list->next = new_element;
	}
	return (head_save);
}