/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_blocks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:52:05 by abenaiss          #+#    #+#             */
/*   Updated: 2021/04/25 21:36:54 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_block_list	*ft_create_block_node(char type, char icon,
	t_render render_data, void *function)
{
	t_block_list	*node;

	node = ft_safe_malloc(sizeof(t_block_list));
	node->type = type;
	node->block_icon = icon;
	node->render.render_data = render_data;
	node->render.render_function = function;
	node->next = NULL;
	return (node);
}

t_block_list	*ft_push_block(t_block_list *block_list,
	t_block_list *new_element)
{
	t_block_list	*head_save;

	head_save = block_list;
	if (!head_save)
		head_save = new_element;
	else
	{
		while (block_list)
		{
			if (block_list->block_icon == new_element->block_icon)
			{
				block_list->type = new_element->type;
				block_list->render = new_element->render;
				return (head_save);
			}
			if (!block_list->next)
				break ;
			block_list = block_list->next;
		}
		block_list->next = new_element;
	}
	return (head_save);
}

void	ft_insert_argument_block_infos(t_tile *map_tile,
	t_block_list *block_list, char *argument)
{
	t_block_list	*test_node;

	if (ft_strlen(argument) != 1)
		ft_err_print("wrong argument for block icon in: ", argument);
	if (*argument == '0')
		return ;
	test_node = ft_find_block_node(block_list, *argument);
	if (!test_node)
		ft_err_print("wrong argument for block icon in: ", argument);
	if (test_node->type == 'w')
		map_tile->wall = test_node;
	if (test_node->type == 'f')
		map_tile->floor = test_node;
	if (test_node->type == 'c')
		map_tile->ceiling = test_node;
}
