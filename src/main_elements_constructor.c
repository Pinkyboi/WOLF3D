/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_elements_constructor.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 13:35:15 by abenaiss          #+#    #+#             */
/*   Updated: 2021/04/29 13:35:23 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_coor  parse_coordinate(char *tuple)
{
	char	**tuple_values;
	t_coor	coordinate;
	short	i;

	tuple_values = parse_block_tuple(tuple);
	i = -1;
	while (tuple_values[++i])
		check_if_number(tuple_values[i]);
	coordinate.x = ft_clip_min(0, ft_atoi(tuple_values[0]));  
	coordinate.y = ft_clip_min(0, ft_atoi(tuple_values[1]));
	return (coordinate);
}

double		ft_clip_min(int min, double value)
{
	return ((value >= min) ? value : min);
}

double		ft_clip_max(int max, double value)
{
	return ((value <= max) ? value : max);
}


double		ft_clip_min_max(int min, int max, double value)
{
	return (ft_clip_max(max, ft_clip_min(min, value)));
}

int  parse_counters(char *counter, int min, int max)
{
	check_if_number(counter);
	return (ft_clip_min_max(min, max, ft_atoi(counter)));
}

t_argument_list	*push_argument(t_argument_list *argument_list,
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

t_argument_list	*create_agument_node(char *argument_name, char *argument_value)
{
	t_argument_list	*node;

	node = malloc(sizeof(t_argument_list));
	if (!node)
		error_print("Internal error during :", "memory allocation");
	node->argument_name = argument_name;
	node->argument_value = argument_value;
	node->next = NULL;
	return (node);
}

void	free_argument_list(t_argument_list *argument_list)
{
	t_argument_list *current_arugment;
	while(argument_list)
	{
		current_arugment = argument_list;
		argument_list = argument_list->next;
		free(current_arugment);
	}
}

t_argument_list *create_argument_list(char *argument_block, t_argument_list *argument_list, char *tag)
{
	char			**argument_lines;
	t_argument_list	*node;
	char			**line;
	int				i;

	argument_lines = ft_strsplit(argument_block, ARGUMENT_DELIMITER);
	i = -1;
	while(argument_lines[++i])
	{
		line = parse_argument_blocks(argument_lines[i], tag);
		argument_list = push_argument(argument_list,
			create_agument_node(ft_strdup(line[0]), ft_strdup(line[1])));
		free_array(line);
	}
	return (argument_list);
}

t_argument_list *search_for_argument_node(t_argument_list *argument_list, char *argument_name)
{
	t_argument_list *list_clone;

	list_clone = argument_list;
	while (list_clone)
	{
		if (!ft_strcmp(list_clone->argument_name, argument_name))
			return (list_clone);
		list_clone = list_clone->next;
	}
	return(NULL);
}

char	*get_argument(char *argument_name, char *default_value,
	t_argument_list *argument_list)
{
	t_argument_list *wanted_node;

	wanted_node = search_for_argument_node(argument_list, argument_name);
	if (wanted_node)
		return(wanted_node->argument_value);
	return(default_value);
}

void	load_player_data(t_game_object *game_object, char *agrument_block)
{
	game_object->current_arguments = create_argument_list(agrument_block, NULL, PLAYER_TAG);
	game_object->player.grid_postion = parse_coordinate(get_argument("position", "(0,0)",
		game_object->current_arguments));
	game_object->player.hp = parse_counters(get_argument("health", "100",
		game_object->current_arguments), MIN_HP, MAX_HP);
	game_object->player.stamina = parse_counters(get_argument("stamina", "100",
		game_object->current_arguments), MIN_STAMINA, MAX_STAMINA);
	free_argument_list(game_object->current_arguments);
}

const t_render_recognition	g_render_dico[] = {
	{"Basic", NULL},
	{"Textured", NULL},
	{"Dim", NULL},
	{"Bloody", NULL},
	{NULL, NULL}
};

t_game_rendering	*parse_render_type(char *render_type)
{
	int i;

	i = - 1;
	while(g_render_dico[++i].render_type)
	{	
		if(!strcmp(render_type, g_render_dico[i].render_type))
			return(g_render_dico[i].rendering_function);
	}
	error_print("The only valide renders types are : " , "(Basic, Textured, Dim, Bloody)");
	return(NULL);
}

void	load_render_data(t_game_object *game_object, char *agrument_block)
{
	game_object->current_arguments = create_argument_list(agrument_block, NULL, ENV_TAG);
	game_object->render_data.render_function = parse_render_type(get_argument("type",
			"Basic", game_object->current_arguments));
	game_object->render_data.window_resolution = parse_resolution(get_argument("resolution",
			"Basic", game_object->current_arguments));	
	game_object->render_data.north_wall  = parse_render(get_argument("N",
			NORTH_COLOR, game_object->current_arguments));
	game_object->render_data.south_wall  = parse_render(get_argument("S",
			NORTH_COLOR, game_object->current_arguments));
	game_object->render_data.south_wall  = parse_render(get_argument("E",
			EAST_COLOR, game_object->current_arguments));
	game_object->render_data.west_wall  = parse_render(get_argument("W",
			WEST_COLOR, game_object->current_arguments));
	free_argument_list(game_object->current_arguments);
}
