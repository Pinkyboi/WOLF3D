/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_constructor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 18:14:04 by abenaiss          #+#    #+#             */
/*   Updated: 2021/06/03 18:14:05 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_sprite_list	*ft_push_sprite(t_sprite_list *argument_list,
				t_sprite_list *new_element)
{
	if (!argument_list)
		return (new_element);
	else
		new_element->next = argument_list;
	return (new_element);
}

t_sprite_list	*ft_create_sprite_node(t_game_object *game_object)
{
	t_sprite_list	*node;

	node = ft_safe_malloc(sizeof(t_sprite_list));
	node->position = ft_parse_coordinate(ft_get_argument("Position", "(0,0)",
				game_object->parser.current_arguments));
	node->side_number = ft_parse_counters(ft_get_argument("Side_number",
				"1", game_object->parser.current_arguments), 0, 10);
	if (node->side_number != 1 && node->side_number != 4
		&& node->side_number != 4)
		ft_err_print("The only valid face number are : :",
			"(1, 4, 8)");
	ft_load_texture(ft_get_argument("Sprite_texture", "",
			game_object->parser.current_arguments), &node->texture);
	node->next = NULL;
	return (node);
}

void	ft_load_sprite_data(t_game_object *game_object, char *agrument_block)
{
	game_object->parser.current_arguments = ft_create_argument_list(
			agrument_block, NULL, PLAYER_TAG);
	ft_push_sprite(game_object->sprite_list,
		ft_create_sprite_node(game_object));
	ft_free_argument_list(game_object->parser.current_arguments);
}
