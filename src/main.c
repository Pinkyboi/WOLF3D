/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:52:05 by abenaiss          #+#    #+#             */
/*   Updated: 2021/04/15 03:08:32 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void    error_print(char *error, char *position)
{
	ft_putstr_fd(ft_strjoin(error, position), 1);
	exit(-1);
}

char    *trim(char *string, char *filter)
{
	int		head;
	int		end;
	int		string_size;
	char	*trimmed_string;

	head = -1;
	while (string[++head])
		if (!ft_strchr(filter, string[head]))
			break;
	end = ft_strlen(string);
	while (string[--end])
		if (!ft_strchr(filter, string[end]))
			break;
	string_size = end - head + 1;
	trimmed_string = malloc(sizeof(char) * (string_size) + 1);
	trimmed_string[string_size] = '\0';
	ft_strlcat(trimmed_string, &string[head], string_size + 1);
	free(string);
	return(trimmed_string);   
}

int		mini_brackets(char *string, char *bracket)
{
	int	open_braket;
	int	pair_number;
	int	i;

	i = -1;
	open_braket = 0;
	pair_number = 0;
	while(string[++i])
	{
		if (string[i] == bracket[0])
			open_braket += 1;
		if (!open_braket && string[i] == bracket[1])
			return (-1);
		if (string[i] == bracket[1] && ++pair_number)
			open_braket -= 1;
	}
	return (((open_braket == 0) ? pair_number : -1)); 
}

char	**parse_resolution(char *resolution_expression)
{
	char	**resolution;
	int		argument_number;
	int		i;

	resolution = ft_strsplit(resolution_expression, 'x');
	argument_number = row_len(resolution);
	if (argument_number != 2)
		error_print("wrong resolution format in:", resolution_expression);
	i = -1;
	while (resolution[++i])
	{
		resolution[i] = trim(resolution[i], WHITE_SPACES);
		check_if_number(resolution[i]);
	}
	return (resolution);
}


void parse_env_block(char *block_infos)
{
	char **block_terms;
	int argument_number;

	block_terms = ft_strsplit(block_infos, ':');
	argument_number = row_len(block_terms);
	if (argument_number != 2)
		error_print("wrong argument format in:", block_infos);
}

t_block_list	*search_for_block_node(t_block_list *block_list, char icon)
{
	t_block_list *head_save;

	head_save = block_list;
	while(head_save)
	{
		if(head_save->block_icon == icon)
			return (head_save);
		head_save = head_save->next;
	}
	return (NULL);
}

void	insert_block_infos(t_tile *map_tile, t_block_list *block_list, char **args)
{
	int i;
	char type;
	t_block_list *test_node;

	i = -1;
	*map_tile = (t_tile){NULL, NULL, NULL};
	while(args[++i])
	{
		
		if(ft_strlen(args[i]) != 1)
			error_print("wrong argument for block icon in: ", args[i]);
		test_node = search_for_block_node(block_list, *args[i]);
		if(!test_node)
			error_print("wrong argument for block icon in: ", args[i]);
		type = test_node->type;
		if (type == 'w')
			map_tile->wall = test_node;
		if (type == 'f')
			map_tile->floor = test_node;
		if (type == 'c')
			map_tile->ceiling = test_node;
	}
}

void	select_tile(t_tile *map_tile, t_block_list *block_list, char *line)
{
	line = trim(line, WHITE_SPACES);
	if (*line == '(')
		insert_block_infos(map_tile, block_list, parse_block_tuple(line));
	else
		insert_block_infos(map_tile, block_list, &line);
}

char **fix_map(char **map)
{
	int i;
	char **line;
	int bigest_row;
	int current_row;
	
	i = -1;
	while(map[++i])
	{
		line = ft_strsplit(map[i], ' ');
		int j = -1;
		while(line[++j])
			map[i][j] = line[j][0];
		map[i][j] = '\0'; 
		bigest_row = ((current_row = row_len(line)) 
			> bigest_row)? current_row : bigest_row;
		free_array(line);
	}
	return(map);
}
char **map_creator(char *data)
{
	char **map;
	
	data = trim(data, WHITE_SPACES);
		map = fix_map(ft_strsplit(data, '\n'));
	int i = -1; 
	while(map[++i]){
		int j = -1;
		while(map[i][++j])
			printf("%c ", map[i][j]);
		printf("%c", '\n');
	}
	return(NULL);
}

int     main(int argc, char **argv)
{
	int fd;
	char *data;
	t_tile map_tile;
	t_block_list *block_list = NULL;
	char *argument;

	
	fd = open(argv[1], O_RDONLY);
	if(fd < 0|| argc != 2)
		exit(-1);
	data = read_file(fd);

	block_list = push_block(block_list, create_block_node('w', 'A',(t_render){.color = 0xFF00},  NULL));
	block_list = push_block(block_list, create_block_node('c', 'K',(t_render){.color = 0xFF0000}, NULL));
	block_list = push_block(block_list, create_block_node('f', 'C',(t_render){.color = 0xFF0000}, NULL));

	argument = malloc(10);
	int i;
	i = -1;

	while("(A,B,C)"[++i])
		argument[i] = "(A,B,C)"[i];
	argument[i] = '\0';
	select_tile(&map_tile, block_list, argument);
	while(block_list){
		printf("type : %c, icon : %c\n", block_list->type, block_list->block_icon);
		block_list = block_list->next;
	}
	if(map_tile.wall)
		printf("---- icon :%c ----\n", map_tile.wall->block_icon);
	if(map_tile.floor)
		printf("---- icon :%c ----\n", map_tile.floor->block_icon);
	if(map_tile.ceiling)
		printf("---- icon :%c ----\n", map_tile.ceiling->block_icon);
	// map_creator(data);
}
